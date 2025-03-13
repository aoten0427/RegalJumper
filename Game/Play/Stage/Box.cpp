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

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
Box::Box(Scene* scene):Object(scene)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//モデル作成
	m_model = AddComponent<Model3D>(this, "Box");
	//判定作成
	OBB* collider = AddComponent<OBB>(this, CollisionType::FIXED, nullptr, false);
	collider->SetScale(Vector3(2, 2, 2));

	

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
	/*m_model->SetIsShadow(false);*/
	/*m_model->SetRender(std::bind(&Box::Render, this, std::placeholders::_1));*/


	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	m_set.vertexShader = ShaderManager::CreateVSShader(device, "ShadowDrawVS.cso");
	m_set.pixelShader = ShaderManager::CreatePSShader(device, "BoxPS.cso");
	m_set.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "ShadowDrawVS.cso");
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void Box::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	auto resorce = GetScene()->GetRenderManager()->GetShadowData();

	Matrix world = m_model->GetWorldMatrix();
	m_model->GetModel()->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&]
		{
			// 定数バッファを指定する
			ID3D11Buffer* cbuf[] = { m_set.cBuffer.Get() };
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// シェーダを設定する
			context->VSSetShader(m_set.vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_set.pixelShader.Get(), nullptr, 0);

			context->IASetInputLayout(m_set.inputLayout.Get());

			// サンプラーステートを指定する
			ID3D11SamplerState* sampler[] = { states->PointWrap(), resorce->m_sampler };
			context->PSSetSamplers(0, 2, sampler);

			// 作成した深度マップをシェーダリソースとして設定する
			context->PSSetShaderResources(1, 1, &resorce->m_shaderResourcesView);	// register(t1)に&srvをバインド

			context->VSSetConstantBuffers(1, 1, &resorce->m_cbuff);
			context->PSSetConstantBuffers(1, 1, &resorce->m_cbuff);
		}
	);
}
