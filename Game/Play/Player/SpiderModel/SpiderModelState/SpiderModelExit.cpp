// ================================================================ 
// �t�@�C���� : SpiderModelExit.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w偂���������Ƃ��̕`����
// ================================================================
#include"pch.h"
#include"SpiderModelExit.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Resource/GameResources.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Render/Model3D.h"
#include"Base/Event/Subject.h"
#include"Base/Tween/DoTween.h"
#include"Base/Sound/Sound.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�w偃��f���X�e�[�g�}�V��</param>
/// <param name="spidermodel">�w偃��f��</param>
SpiderModelExit::SpiderModelExit(SpiderModelStateMachine* machine, SpiderModels* spidermodel) :SpiderModelState(machine, spidermodel)
	,
	m_resources{ nullptr },
	m_spiderModel{ spidermodel },
	m_shaderSet{},
	m_mosaicTexture{ nullptr },
	m_tcBuff{ nullptr },
	m_blendState{ nullptr },
	m_timer{ 0.0 }
{
	m_resources = m_spiderModel->GetCommonResources();
	//�V�F�[�_���Z�b�g
	auto device = m_resources->GetDeviceResources()->GetD3DDevice();
	m_shaderSet.vertexShader = ShaderManager::CreateVSShader(device, "ModelVS.cso");
	m_shaderSet.pixelShader = ShaderManager::CreatePSShader(device, "ModelExitPS.cso");
	m_shaderSet.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "ModelVS.cso");
	m_shaderSet.cBuffer = ShaderManager::CreateConstantBuffer<SpiderModels::CBLight>(device);
	m_tcBuff = ShaderManager::CreateConstantBuffer<CBuff>(device);
	m_mosaicTexture = GameResources::GetInstance()->GetTexture("Mosaic");

	// �u�����h�X�e�[�g���쐬����
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

	//�T�u�W�F�N�g�쐬
	m_finishSubject = m_spiderModel->AddComponent<Subject<>>(m_spiderModel, "SpiderExit");
	//Tween�쐬
	m_tween = m_spiderModel->AddComponent<Tween>(m_spiderModel, true);
	//�T�E���h
	m_warpSound = m_spiderModel->AddComponent<Sound>(m_spiderModel, Sound::SoundType::SE, "Warp", false);
}

/// <summary>
/// ���O�X�V
/// </summary>
void SpiderModelExit::PreUpdate()
{
	m_warpSound->Play();

	m_tween->DoFloat(m_timer, 6.0f, 1.0f).SetCompleteFunction([&]() {
		m_finishSubject->Notify();
		});
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void SpiderModelExit::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// ����X�V
/// </summary>
void SpiderModelExit::PostUpdate()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void SpiderModelExit::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;

	auto context = m_resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_resources->GetCommonStates();
	//�e�p�[�c���擾
	auto modelparts = m_spiderModel->GetModelParts();
	//���C�g�萔�o�b�t�@���쐬
	context->UpdateSubresource(m_shaderSet.cBuffer.Get(), 0, NULL, &m_spiderModel->GetLightData(), 0, 0);
	ID3D11Buffer* lightcb[1] = { m_shaderSet.cBuffer.Get() };
	//�^�C�}�[�萔�o�b�t�@���쐬
	CBuff cb;
	cb.Time.x = m_timer;
	cb.Time.y = m_spiderModel->GetTransform()->GetWorldPosition().y;
	cb.CenterHeight.x = m_spiderModel->GetTransform()->GetWorldPosition().y;
	

	//�e�p�[�c��`��
	for (auto& parts : modelparts)
	{
		//���f���̍s��
		Matrix world = parts->GetModel()->GetWorldMatrix();
		parts->GetModel()->GetModel()->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&]() {
			
			/*cb.CenterHeight.x = parts->GetTransform()->GetWorldPosition().y - parts->GetTransform()->GetPosition().y;*/
			context->UpdateSubresource(m_tcBuff.Get(), 0, NULL, &cb, 0, 0);
			ID3D11Buffer* timecb[1] = { m_tcBuff.Get() };

			context->VSSetConstantBuffers(1, 1, lightcb);
			context->PSSetConstantBuffers(1, 1, lightcb);
			context->VSSetConstantBuffers(2, 1, timecb);
			context->PSSetConstantBuffers(2, 1, timecb);
			context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

			context->VSSetShader(m_shaderSet.vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_shaderSet.pixelShader.Get(), nullptr, 0);
			context->IASetInputLayout(m_shaderSet.inputLayout.Get());
			//�e�N�X�`���Z�b�g
			context->PSSetShaderResources(0, 1, parts->GetTexture());
			context->PSSetShaderResources(1, 1, m_mosaicTexture.GetAddressOf());
			//�T���v���[�Z�b�g
			ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
			context->PSSetSamplers(0, 1, sampler);
			});
	}
}
