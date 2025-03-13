// ================================================================ 
// ファイル名 : ThreadModel.h
// 作成者 : 景山碧天
// 説明 :  糸のモデル
// ================================================================
#include"pch.h"
#include"ThreadModel.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Particle.h"

//初期回転軸
constexpr DirectX::SimpleMath::Vector3 INITIAL_DIRECTION = DirectX::SimpleMath::Vector3(0, 0, 1);
//基本の長さ
constexpr float BASE_LENTH = 11.95;
//太さ
constexpr float THICKNESS = 2.5f;
//スプラインの次数
constexpr int DEGREE = 3;
//スプラインのポイント数
constexpr int SPLINE_POINTS = 60;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene"></param>
/// <param name="thread"></param>
ThreadModel::ThreadModel(Scene* scene, Thread* thread):Object(scene)
	,
	m_thread{thread}
{
	using namespace DirectX;
	//モデル読み込み
	m_model = AddComponent<Model3D>(this, "Thread");
	//真っ白にする
	m_model->GetModel()->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// 個別のライトをすべて無効化する
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(XMVECTOR{ 1.0f,1.0f,1.0f,1 });
			}
		}
	);
	m_model->SetRender(std::bind(&ThreadModel::Render, this, std::placeholders::_1));
	//クランプノットを計算
	m_knot = ClampedKnotVector(SPLINE_POINTS, DEGREE);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera"></param>
void ThreadModel::Render(const Camera& camera)
{
	if (m_thread->GetThreadParticles().empty())return;

	using namespace DirectX::SimpleMath;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();


	std::vector<Vector3> positions;
	RopeSolver* rope = m_thread->GetRopeSolver();

	//描画場所の位置を設定
	for (auto& particle : rope->GetParticles())
	{
		positions.push_back(particle->GetObject()->GetTransform()->GetPosition());
	}

	std::vector<Vector3> sprin = ComputeBSplineCurve(positions,3,1.0f / SPLINE_POINTS);
	sprin.push_back(positions.back());

	for (int i = 0; i <sprin.size() - 1; i++)
	{
		//距離を求める
		Vector3 distance = sprin[i + 1] - sprin[i];
		//長さを求める
		float lenth = distance.Length();
		//拡大値を求める
		float size = lenth / BASE_LENTH;

		distance.Normalize();
		//初期値からの角度を求める
		float dot = distance.Dot(INITIAL_DIRECTION);
		float angle = -acos(dot);
		//回転軸を求める
		Vector3 axis = distance.Cross(INITIAL_DIRECTION);
		if (axis.Length() == 0)continue;
		//クォータニオン計算
		Quaternion roteto = Quaternion::CreateFromAxisAngle(axis, angle);
		//matrix
		Matrix mat = Matrix::CreateScale(Vector3(THICKNESS, THICKNESS, size));
		mat *= Matrix::CreateFromQuaternion(roteto);
		mat *= Matrix::CreateTranslation(sprin[i]);

		//モデル描画
		m_model->GetModel()->Draw(context, *states, mat, camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
}

/// <summary>
/// ノットベクトルを計算
/// </summary>
/// <param name="p">ポイント数</param>
/// <param name="n">次数</param>
/// <returns></returns>
std::vector<float> ThreadModel::ClampedKnotVector(int p, int n)
{
	int m = p + n + 1;
	std::vector<float> u(m);

	// 最初の n+1 個のノットを 0 に固定（始点を固定）
	for (int i = 0; i <= n; ++i) {
		u[i] = 0.0f;
	}

	// 中間のノットを均等に配置（Bスプラインのスムーズな遷移を確保）
	for (int i = 1; i < p - n; ++i) {
		u[n + i] = (float)i / (p - n);
	}

	// 最後の n+1 個のノットを 1 に固定（終点を固定）
	for (int i = m - n - 1; i < m; ++i) {
		u[i] = 1.0f;
	}

	return u;
}


/// <summary>
/// Bスプラインの基底関数を計算
/// </summary>
/// <param name="u">ノットベクトル</param>
/// <param name="j">対象の制御点インデックス</param>
/// <param name="k">スプラインの次数</param>
/// <param name="t">パラメータ値（0.0 ～ 1.0）</param>
/// <returns>指定された制御点に対する基底関数の値</returns>
float ThreadModel::BasisFunction(const std::vector<float>& u, int j, int k, float t)
{
	// 0次基底関数の定義（該当区間なら1.0、それ以外は0.0）
	if (k == 0) {
		return (u[j] <= t && t < u[j + 1]) ? 1.0f : 0.0f;
	}

	float w1 = 0.0f, w2 = 0.0f;

	// 左側の基底関数の重み計算（tがノット間にある場合）
	if ((u[j + k] - u[j]) != 0.0f) {
		w1 = ((t - u[j]) / (u[j + k] - u[j])) * BasisFunction(u, j, k - 1, t);
	}

	// 右側の基底関数の重み計算
	if ((u[j + k + 1] - u[j + 1]) != 0.0f) {
		w2 = ((u[j + k + 1] - t) / (u[j + k + 1] - u[j + 1])) * BasisFunction(u, j + 1, k - 1, t);
	}

	return w1 + w2;
}


/// <summary>
/// Bスプライン曲線を計算
/// </summary>
/// <param name="P">制御点リスト</param>
/// <param name="n">スプラインの次数</param>
/// <param name="step">計算する間隔</param>
/// <returns>曲線リスト</returns>
std::vector<DirectX::SimpleMath::Vector3> ThreadModel::ComputeBSplineCurve(
	const std::vector<DirectX::SimpleMath::Vector3>& P, int n, float step)
{
	std::vector<DirectX::SimpleMath::Vector3> S;

	// スプラインの範囲（始点と終点）
	float t_start = m_knot[n];
	float t_end = m_knot[P.size()];

	// 指定した間隔で曲線上の点を計算
	for (float t = t_start; t <= t_end; t += step) {
		DirectX::SimpleMath::Vector3 point = { 0.0f, 0.0f, 0.0f };

		// 各制御点に対する基底関数の重み付けを計算し、最終的な座標を求める
		for (int j = 0; j < P.size(); ++j) {
			float b = BasisFunction(m_knot, j, n, t);
			point = point + P[j] * b;
		}

		S.push_back(point);
	}

	return S;
}
