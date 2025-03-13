// ================================================================ 
// ファイル名 : SpiderModelPlay.cpp
// 作成者 : 景山碧天
// 説明 :  Play画面での蜘蛛の描画状態
// ================================================================
#include"pch.h"
#include"SpiderModelPlay.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Render/Model3D.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">蜘蛛モデルステートマシン</param>
/// <param name="spidermodel">蜘蛛モデル</param>
SpiderModelPlay::SpiderModelPlay(SpiderModelStateMachine* machine, SpiderModels* spidermodel) :SpiderModelState(machine, spidermodel)
	,
	m_resources{ nullptr },
	m_spiderModel{ spidermodel },
	m_shaderSet{}
{
	m_resources = m_spiderModel->GetCommonResources();
	//シェーダをセット
	auto device = m_resources->GetDeviceResources()->GetD3DDevice();
	m_shaderSet.vertexShader = ShaderManager::CreateVSShader(device, "ModelVS.cso");
	m_shaderSet.pixelShader = ShaderManager::CreatePSShader(device, "ModelPlayPS.cso");
	m_shaderSet.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "ModelVS.cso");
	m_shaderSet.cBuffer = ShaderManager::CreateConstantBuffer<SpiderModels::CBLight>(device);
}

/// <summary>
/// 事前更新
/// </summary>
void SpiderModelPlay::PreUpdate()
{
	m_spiderModel->GetScene()->ChangeState(Scene::State::PLAY);
	Model3D* model = m_spiderModel->GetComponent<Model3D>();
	model->SetIsAfterDraw(false);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void SpiderModelPlay::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// 事後更新
/// </summary>
void SpiderModelPlay::PostUpdate()
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void SpiderModelPlay::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;

	auto context = m_resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_resources->GetCommonStates();
	//各パーツを取得
	auto modelparts = m_spiderModel->GetModelParts();
	//定数バッファを作成
	context->UpdateSubresource(m_shaderSet.cBuffer.Get(), 0, NULL, &m_spiderModel->GetLightData(), 0, 0);
	//	シェーダーにバッファを渡す
	ID3D11Buffer* lightcb[1] = { m_shaderSet.cBuffer.Get() };

	//各パーツを描画
	for (auto& parts : modelparts)
	{
		//モデルの行列
		Matrix world = parts->GetModel()->GetWorldMatrix();
		parts->GetModel()->GetModel()->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&]() {
			context->VSSetConstantBuffers(1, 1, lightcb);
			context->PSSetConstantBuffers(1, 1, lightcb);
			context->VSSetShader(m_shaderSet.vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_shaderSet.pixelShader.Get(), nullptr, 0);
			context->IASetInputLayout(m_shaderSet.inputLayout.Get());
			context->PSSetShaderResources(0, 1, parts->GetTexture());
			ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
			context->PSSetSamplers(0, 1, sampler);
			});
	}
}
