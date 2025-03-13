// ================================================================ 
// �t�@�C���� : SpiderModelPlay.cpp
// �쐬�� : �i�R�ɓV
// ���� :  Play��ʂł̒w偂̕`����
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
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�w偃��f���X�e�[�g�}�V��</param>
/// <param name="spidermodel">�w偃��f��</param>
SpiderModelPlay::SpiderModelPlay(SpiderModelStateMachine* machine, SpiderModels* spidermodel) :SpiderModelState(machine, spidermodel)
	,
	m_resources{ nullptr },
	m_spiderModel{ spidermodel },
	m_shaderSet{}
{
	m_resources = m_spiderModel->GetCommonResources();
	//�V�F�[�_���Z�b�g
	auto device = m_resources->GetDeviceResources()->GetD3DDevice();
	m_shaderSet.vertexShader = ShaderManager::CreateVSShader(device, "ModelVS.cso");
	m_shaderSet.pixelShader = ShaderManager::CreatePSShader(device, "ModelPlayPS.cso");
	m_shaderSet.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "ModelVS.cso");
	m_shaderSet.cBuffer = ShaderManager::CreateConstantBuffer<SpiderModels::CBLight>(device);
}

/// <summary>
/// ���O�X�V
/// </summary>
void SpiderModelPlay::PreUpdate()
{
	m_spiderModel->GetScene()->ChangeState(Scene::State::PLAY);
	Model3D* model = m_spiderModel->GetComponent<Model3D>();
	model->SetIsAfterDraw(false);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void SpiderModelPlay::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// ����X�V
/// </summary>
void SpiderModelPlay::PostUpdate()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void SpiderModelPlay::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;

	auto context = m_resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_resources->GetCommonStates();
	//�e�p�[�c���擾
	auto modelparts = m_spiderModel->GetModelParts();
	//�萔�o�b�t�@���쐬
	context->UpdateSubresource(m_shaderSet.cBuffer.Get(), 0, NULL, &m_spiderModel->GetLightData(), 0, 0);
	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* lightcb[1] = { m_shaderSet.cBuffer.Get() };

	//�e�p�[�c��`��
	for (auto& parts : modelparts)
	{
		//���f���̍s��
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
