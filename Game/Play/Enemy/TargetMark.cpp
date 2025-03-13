// ================================================================ 
// ファイル名 : TargetMark.cpp
// 作成者 : 景山碧天
// 説明 :  ターゲット表示マーク
// ================================================================
#include"pch.h"
#include"TargetMark.h"
#include"Base/Base.h"
#include"Base/Tween/DoTween.h"

constexpr float EXTENS = 1.5f;
constexpr float CHANGE_SPEED = 0.3f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="holder">所属オブジェクト</param>
TargetMark::TargetMark(Scene* scene, Object* holder):Object(scene)
	,
	m_size{0}
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	GetTransform()->SetParent(holder->GetTransform());

	m_renderer = AddComponent<PrimitiveRenderer>(this,"TargetMark");
	m_renderer->SetRender(std::bind(&TargetMark::Render, this, std::placeholders::_1, std::placeholders::_2));

	// ベーシックエフェクトを作成する
	m_basicEffect = std::make_unique<BasicEffect>(GetCommonResources()->GetDeviceResources()->GetD3DDevice());
	m_basicEffect->SetTextureEnabled(true);

	// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			GetCommonResources()->GetDeviceResources()->GetD3DDevice(),
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	m_tween = AddComponent<Tween>(this, true);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="primitiveBatch">プリミティブバッチ</param>
/// <param name="camera">カメラ</param>
void TargetMark::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//設置方向をカメラの位置から設定
	Vector3 pos = GetTransform()->GetWorldPosition() - camera.GetEyePosition();
	pos.Normalize();
	Matrix mat = Matrix::CreateTranslation(-pos * 5 * m_size);

	//表示場所を計算
	VertexPositionTexture vertexs[4]{
		{Vector3(-EXTENS * m_size,EXTENS * m_size,0),Vector2(0,0)},
		{Vector3(EXTENS * m_size,EXTENS * m_size,0),Vector2(1,0)},
		{Vector3(EXTENS * m_size,-EXTENS * m_size,0),Vector2(1,1)},
		{Vector3(-EXTENS * m_size,-EXTENS * m_size,0),Vector2(0,1)},
	};

	//ビルボード設定
	Matrix bill = camera.GetViewMatrix().Invert();
	bill._41 = 0;
	bill._42 = 0;
	bill._43 = 0;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, sampler);

	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);// ブレンドステート
	context->OMSetDepthStencilState(states->DepthDefault(), 0);		// 深度バッファ/ステンシルバッファ
	context->RSSetState(states->CullNone());			// カリング
	context->IASetInputLayout(m_inputLayout.Get());


	m_basicEffect->SetView(camera.GetViewMatrix());				// ビュー行列
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());	// 射影行列
	m_basicEffect->SetWorld(bill * mat * GetTransform()->GetWorldMatrix());
	m_basicEffect->SetTexture(m_renderer->GetImage());

	m_basicEffect->Apply(context);

	primitiveBatch->Begin();

	primitiveBatch->DrawQuad(vertexs[0], vertexs[1], vertexs[2], vertexs[3]);

	primitiveBatch->End();
}

/// <summary>
/// 開く
/// </summary>
void TargetMark::Open()
{
	m_size = 10;
	m_tween->DoFloat(m_size, 1, CHANGE_SPEED).SetEase(Easing::Ease::OutQuad);
}

/// <summary>
/// 閉じる
/// </summary>
void TargetMark::Close()
{
	m_tween->DoFloat(m_size, 0, CHANGE_SPEED).SetEase(Easing::Ease::InQuad);
}
