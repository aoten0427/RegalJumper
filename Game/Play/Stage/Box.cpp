// ================================================================ 
// ファイル名 : Box.cpp
// 作成者 : 景山碧天
// 説明 :  ステージに主に使われる箱
// ================================================================
#include"pch.h"	
#include"Box.h"
#include"Base/Base.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/CommonManager/ShadowMapManager.h"
#include"Base/Resource/GameResources.h"
#include"Game/Play/Player/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
Box::Box(Scene* scene, Player* player):Object(scene)
{
	m_player = player;
	Initialize();
}

Box::Box(Scene* scene) :Object(scene)
	,m_player{nullptr}
{
	Initialize();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void Box::Render(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	m_model->GetModel()->Draw(context, *states, m_model->GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&] {
		// 定数バッファを指定する
		PlayerPosition ppos;

		Vector3 pos = m_player->GetTransform()->GetPosition();
		ppos.Position = Vector4(pos.x, pos.y, pos.z, 0);
		context->UpdateSubresource(m_set.cBuffer.Get(), 0, NULL, &ppos, 0, 0);

		ID3D11Buffer* cbuf[] = { m_set.cBuffer.Get() };
		context->VSSetConstantBuffers(1, 1, cbuf);
		context->PSSetConstantBuffers(1, 1, cbuf);

		// シェーダを設定する
		context->VSSetShader(m_set.vertexShader.Get(), nullptr, 0);
		context->PSSetShader(m_set.pixelShader.Get(), nullptr, 0);

		context->IASetInputLayout(m_set.inputLayout.Get());

		// サンプラーステートを指定する
		ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
		context->PSSetSamplers(0, 1, sampler);

		context->PSSetShaderResources(0, 1, m_modelTexture.GetAddressOf());
		});
}

void Box::Initialize()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//モデル作成
	m_model = AddComponent<Model3D>(this, "Box");
	//判定作成
	OBB* collider = AddComponent<OBB>(this, CollisionType::FIXED, nullptr, false);
	collider->SetScale(Vector3(2, 2, 2));

	if (m_player)
	{
		auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();

		m_set.vertexShader = ShaderManager::CreateVSShader(device, "BoxVS.cso");
		m_set.pixelShader = ShaderManager::CreatePSShader(device, "BoxPS.cso");
		m_set.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "BoxVS.cso");
		m_set.cBuffer = ShaderManager::CreateConstantBuffer<PlayerPosition>(device);

		m_model->SetRender(std::bind(&Box::Render, this, std::placeholders::_1));

		m_modelTexture = GameResources::GetInstance()->GetTexture("Box");
	}
	else
	{
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
					basicEffect->SetEmissiveColor(XMVECTOR{ 0.8f,0.0f,0.8f,1 });
				}
			}
		);
	}
	

	
}
