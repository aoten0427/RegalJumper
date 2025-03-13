// ================================================================ 
// �t�@�C���� : Box.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�Ɏ�Ɏg���锠
// ================================================================
#include"pch.h"	
#include"Box.h"
#include"Base/Base.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/CommonManager/ShadowMapManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
Box::Box(Scene* scene):Object(scene)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//���f���쐬
	m_model = AddComponent<Model3D>(this, "Box");
	//����쐬
	OBB* collider = AddComponent<OBB>(this, CollisionType::FIXED, nullptr, false);
	collider->SetScale(Vector3(2, 2, 2));

	

	m_model->GetModel()->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �ʂ̃��C�g�����ׂĖ���������
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// ���f����������������
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
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
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
			// �萔�o�b�t�@���w�肷��
			ID3D11Buffer* cbuf[] = { m_set.cBuffer.Get() };
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// �V�F�[�_��ݒ肷��
			context->VSSetShader(m_set.vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_set.pixelShader.Get(), nullptr, 0);

			context->IASetInputLayout(m_set.inputLayout.Get());

			// �T���v���[�X�e�[�g���w�肷��
			ID3D11SamplerState* sampler[] = { states->PointWrap(), resorce->m_sampler };
			context->PSSetSamplers(0, 2, sampler);

			// �쐬�����[�x�}�b�v���V�F�[�_���\�[�X�Ƃ��Đݒ肷��
			context->PSSetShaderResources(1, 1, &resorce->m_shaderResourcesView);	// register(t1)��&srv���o�C���h

			context->VSSetConstantBuffers(1, 1, &resorce->m_cbuff);
			context->PSSetConstantBuffers(1, 1, &resorce->m_cbuff);
		}
	);
}
