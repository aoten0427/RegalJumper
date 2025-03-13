// ================================================================ 
// ファイル名 : Help.cpp
// 作成者 : 景山碧天
// 説明 :  ヘルプ情報
// ================================================================
#include"pch.h"
#include"Help.h"
#include"Base/Base.h"
#include"Base/Event/Observer.h"
#include"Game/Play/Stage/HelpInfomation.h"

constexpr float EXTENS = 4.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="infomationNum">インフォメーション番号</param>
Help::Help(Scene* scene, int infomationNum,bool begin) :Object(scene)
,
m_isContactActive{ true },
m_biginFinish{ false }
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//描画作成
	m_renderer = AddComponent<PrimitiveRenderer>(this, "Help");
	m_renderer->SetRender(std::bind(&Help::Render, this, std::placeholders::_1, std::placeholders::_2));
	//頂点情報設定
	m_vertexs[0] = VertexPositionTexture(Vector3(-EXTENS, EXTENS, 0), Vector2(0, 0));
	m_vertexs[1] = VertexPositionTexture(Vector3(-EXTENS, -EXTENS, 0), Vector2(0, 1));
	m_vertexs[2] = VertexPositionTexture(Vector3(EXTENS, -EXTENS, 0), Vector2(1, 1));
	m_vertexs[3] = VertexPositionTexture(Vector3(EXTENS, EXTENS, 0), Vector2(1, 0));

	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	// ベーシックエフェクトを作成する
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetTextureEnabled(true);
	// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	//コライダー生成
	AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr, false, 3.5f);
	//インフォメーション作成
	m_infomation = scene->AddObject<HelpInfomation>(scene->GetCanvas(), static_cast<HelpInfomation::INFOMATION>(infomationNum));

	if (begin)
	{
		auto* obs = AddComponent<Observer<Scene::State, Scene::State>>(this);
		obs->SetFunction(std::bind(&Help::BeginOpen, this, std::placeholders::_1, std::placeholders::_2));
		obs->RegistrationSubject("SceneStateChange");
	}
	
	
	
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Help::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//回転させる
	GetTransform()->TransRotate(DirectX::SimpleMath::Vector3::UnitY, 2);
	//スペースが押された場合インフォメーション終了処理
	if (GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::Space) && m_isContactActive) {
		m_infomation->Close();
		m_biginFinish = true;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="primitiveBatch">プリミティブバッチ</param>
/// <param name="camera">カメラ</param>
void Help::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	using namespace DirectX::SimpleMath;

	//オブジェクトのmatrix考慮の頂点を作成
	DirectX::VertexPositionTexture vertex[4];
	for (int i = 0; i < 4; i++)
	{
		vertex[i].position = Vector3::Transform(m_vertexs[i].position, GetTransform()->GetWorldMatrix());
		vertex[i].textureCoordinate = m_vertexs[i].textureCoordinate;
	}

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, sampler);

	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);// ブレンドステート
	context->OMSetDepthStencilState(states->DepthDefault(), 0);		// 深度バッファ/ステンシルバッファ
	context->RSSetState(states->CullNone());			// カリング
	context->IASetInputLayout(m_inputLayout.Get());

	m_basicEffect->SetView(camera.GetViewMatrix());
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());
	m_basicEffect->SetWorld(Matrix::Identity);
	m_basicEffect->SetTexture(m_renderer->GetImage());
	m_basicEffect->Apply(context);

	primitiveBatch->Begin();

	primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);

	primitiveBatch->End();
}

/// <summary>
/// Trigger実行有無 プレイヤーとのみ行う
/// </summary>
/// <param name="collider">判定</param>
/// <returns>実行有無</returns>
bool Help::IsTriggerAct(Collider* collider)
{
	using namespace DirectX::SimpleMath;
	if (collider->GetObject()->GetTag() != ObjectTag::Player)return false;
	if (!m_biginFinish)return false;
	//一定距離離れたらアクティブをオフにする
	if (Vector3::Distance(collider->GetObject()->GetTransform()->GetPosition(), GetTransform()->GetPosition()) > 10.0f)
	{
		m_isContactActive = false;
	}
	//アクティブ中は取らない
	if (m_isContactActive)return false;
	return true;
}

/// <summary>
/// Trigger処理 ヘルプを開く
/// </summary>
/// <param name="collider">判定</param>
void Help::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	//アクティブをオンに
	m_isContactActive = true;
	//ヘルプ内容を表示
	m_infomation->Open();
	//シーンをストップ状態に
	GetScene()->ChangeState(Scene::State::STOP);
}

/// <summary>
/// ゲーム開始時の開く処理
/// </summary>
/// <param name="current">現在のシーン状態</param>
/// <param name="old">前のシーン状態</param>
void Help::BeginOpen(Scene::State current, Scene::State old)
{
	if (current == Scene::State::PLAY && old == Scene::State::RESERVE)
	{
		//アクティブをオンに
		m_isContactActive = true;
		//ヘルプ内容を表示
		m_infomation->Open();
		//シーンをストップ状態に
		GetScene()->ChangeState(Scene::State::STOP);
	}
}
