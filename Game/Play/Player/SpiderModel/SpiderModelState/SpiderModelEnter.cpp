// ================================================================ 
// ファイル名 : SpiderModelEnter.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛が出現するときの描画状態
// ================================================================
#include"pch.h"
#include"SpiderModelEnter.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Resource/GameResources.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Render/Model3D.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"
#include"Base/Sound/Sound.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">蜘蛛モデルステートマシン</param>
/// <param name="spidermodel">蜘蛛モデル</param>
SpiderModelEnter::SpiderModelEnter(SpiderModelStateMachine* machine, SpiderModels* spidermodel) :SpiderModelState(machine, spidermodel)
	,
	m_resources{ nullptr },
	m_spiderModel{ spidermodel },
	m_shaderSet{},
	m_mosaicTexture{nullptr},
	m_tcBuff{nullptr},
	m_blendState{nullptr},
	m_timer{0.0}
{
	m_resources = m_spiderModel->GetCommonResources();
	//シェーダをセット
	auto device = m_resources->GetDeviceResources()->GetD3DDevice();
	m_shaderSet.vertexShader = ShaderManager::CreateVSShader(device, "ModelVS.cso");
	m_shaderSet.pixelShader = ShaderManager::CreatePSShader(device, "ModelEntryPS.cso");
	m_shaderSet.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "ModelVS.cso");
	m_shaderSet.cBuffer = ShaderManager::CreateConstantBuffer<SpiderModels::CBLight>(device);
	m_tcBuff = ShaderManager::CreateConstantBuffer<TCBuff>(device);

	// ブレンドステートを作成する
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DX::ThrowIfFailed(device->CreateBlendState(&blendDesc, m_blendState.ReleaseAndGetAddressOf()));
	m_mosaicTexture = GameResources::GetInstance()->GetTexture("Mosaic");

	m_playbackObserver = m_spiderModel->AddComponent<Observer<Scene::State>>(m_spiderModel);
	m_playbackObserver->RegistrationSubject("SceneStateChange");
	m_playbackObserver->SetFunction(std::bind(&SpiderModelEnter::CheckPlayBack, this, std::placeholders::_1));
	//Tween作成
	m_tween = m_spiderModel->AddComponent<Tween>(m_spiderModel, true);
	//サウンド作成
	m_warpSound = m_spiderModel->AddComponent<Sound>(m_spiderModel, Sound::SoundType::SE, "Warp", false);
}

/// <summary>
/// 事前更新
/// </summary>
void SpiderModelEnter::PreUpdate()
{
	m_warpSound->Play();
	m_tween->DoFloat(m_timer, 8.0f, 2.0f).SetCompleteFunction([&]() {
		ChangeState(RenderType::PLAY);
		});
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void SpiderModelEnter::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// 事後更新
/// </summary>
void SpiderModelEnter::PostUpdate()
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void SpiderModelEnter::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;

	auto context = m_resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_resources->GetCommonStates();
	//各パーツを取得
	auto modelparts = m_spiderModel->GetModelParts();
	//ライト定数バッファを作成
	context->UpdateSubresource(m_shaderSet.cBuffer.Get(), 0, NULL, &m_spiderModel->GetLightData(), 0, 0);
	ID3D11Buffer* lightcb[1] = { m_shaderSet.cBuffer.Get() };
	//タイマー定数バッファを作成
	TCBuff tc;
	tc.Time.x = m_timer;
	context->UpdateSubresource(m_tcBuff.Get(), 0, NULL, &tc, 0, 0);
	ID3D11Buffer* timecb[1] = { m_tcBuff.Get() };

	//各パーツを描画
	for (auto& parts : modelparts)
	{
		//モデルの行列
		Matrix world = parts->GetModel()->GetWorldMatrix();
		parts->GetModel()->GetModel()->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&]() {
			context->VSSetConstantBuffers(1, 1, lightcb);
			context->PSSetConstantBuffers(1, 1, lightcb);
			context->VSSetConstantBuffers(2, 1, timecb);
			context->PSSetConstantBuffers(2, 1, timecb);
			context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

			context->VSSetShader(m_shaderSet.vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_shaderSet.pixelShader.Get(), nullptr, 0);
			context->IASetInputLayout(m_shaderSet.inputLayout.Get());
			//テクスチャセット
			context->PSSetShaderResources(0, 1, parts->GetTexture());
			context->PSSetShaderResources(1, 1, m_mosaicTexture.GetAddressOf());
			//サンプラーセット
			ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
			context->PSSetSamplers(0, 1, sampler);
			});
	}
}

/// <summary>
/// 描画をシーンの状態によって変更する
/// </summary>
/// <param name="state">シーン状態</param>
void SpiderModelEnter::CheckPlayBack(Scene::State state)
{
	if (state == Scene::State::RESERVE)
	{
		m_tween->Play();
	}
	else
	{
		m_tween->Pause();
	}
}
