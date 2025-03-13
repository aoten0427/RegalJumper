// ================================================================ 
// �t�@�C���� : RenderManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �`����s��
// ================================================================

#include"pch.h"
#include"RenderManager.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Component/Render/Model3D.h"
#include"Base/Component/Render/PrimitiveRenderer.h"
#include"Base/CommonManager/ShadowMapManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="context">�R���e�N�X�g</param>
/// <param name="states">�R�����X�e�[�g</param>
RenderManager::RenderManager(CommonResources* commonResources)
	:
	m_commonResources{commonResources}
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//�v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);

	m_shadowMap = std::make_unique<ShadowMapManager>(commonResources);
}

/// <summary>
/// ���f���̒ǉ�
/// </summary>
/// <param name="model3D">�ǉ����f��</param>
void RenderManager::AddModel3D(Model3D* model3D)
{
	//�I�[�_�[�̏ꏊ�֒ǉ�
	auto itr = m_model3Ds.begin();
	//�}���ꏊ����
	while (itr != m_model3Ds.end()&& model3D->GetRenderOrder() > (*itr)->GetRenderOrder())
	{
		itr++;
	}
	m_model3Ds.insert(itr, model3D);
}

/// <summary>
/// ���f���폜
/// </summary>
/// <param name="model3D">�폜���f��</param>
void RenderManager::RemoveModel3D(Model3D* model3D)
{
	auto remove = std::find(m_model3Ds.begin(), m_model3Ds.end(), model3D);
	if (remove != m_model3Ds.end())
	{
		m_model3Ds.erase(remove);
	}
}

/// <summary>
/// �`�揇�ύX(���f��)
/// </summary>
/// <param name="model3D">�ύX���f��</param>
void RenderManager::ChangeRenderOrder(Model3D* model3D)
{
	//�ړ��v�f������
	auto move = std::find(m_model3Ds.begin(), m_model3Ds.end(),model3D);
	if (move == m_model3Ds.end())return;

	//�ꎞ�ۑ����Ĕz�񂩂�폜
	auto element = std::move(*move);
	m_model3Ds.erase(move);

	//�}���ꏊ����
	auto change = m_model3Ds.begin();
	while (change != m_model3Ds.end() && model3D->GetRenderOrder() > (*change)->GetRenderOrder())
	{
		change++;
	}

	//�}��
	m_model3Ds.insert(change, std::move(element));
}

/// <summary>
/// �摜�����_���[�ǉ�
/// </summary>
/// <param name="render">�ǉ������_���[</param>
void RenderManager::AddPrimitiveRenderer(PrimitiveRenderer* render)
{
	auto itr = m_primitiveRenderer.begin();
	while (itr != m_primitiveRenderer.end() && render->GetRenderOrder() > (*itr)->GetRenderOrder())
	{
		itr++;
	}
	m_primitiveRenderer.insert(itr, render);
}

/// <summary>
/// �摜�����_���[�폜
/// </summary>
/// <param name="render">�폜�����_���[</param>
void RenderManager::RemovePrimitiveRenderer(PrimitiveRenderer* render)
{
	auto remove = std::find(m_primitiveRenderer.begin(), m_primitiveRenderer.end(), render);
	if (remove != m_primitiveRenderer.end())
	{
		m_primitiveRenderer.erase(remove);
	}
}

/// <summary>
/// �`�揇�ύX(�����_���[)
/// </summary>
/// <param name="render">�ύX�����_���[</param>
void RenderManager::ChangeRenderOrder(PrimitiveRenderer* render)
{
	//�ړ��v�f������
	auto move = std::find(m_primitiveRenderer.begin(), m_primitiveRenderer.end(), render);
	if (move == m_primitiveRenderer.end())return;

	//�ꎞ�ۑ����Ĕz�񂩂�폜
	auto element = std::move(*move);
	m_primitiveRenderer.erase(move);

	//�}���ꏊ����
	auto change = m_primitiveRenderer.begin();
	while (change != m_primitiveRenderer.end() && render->GetRenderOrder() > (*change)->GetRenderOrder())
	{
		change++;
	}

	//�}��
	m_primitiveRenderer.insert(change, std::move(element));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�`��J����</param>
void RenderManager::Render(const Camera& camera)
{
	//�V���h�E�}�b�v
	/*m_shadowMap->Render(m_model3Ds, camera);*/


	std::vector<Model3D*> afterdraws;
	//���f���`��
	for (auto& model : m_model3Ds)
	{
		if (!model->GetActive())continue;
		if (model->GetIsAfterDraw())
		{
			//�`���摗�肷��
			afterdraws.push_back(model);
			continue;
		}

		model->Render(camera);
	}

	std::vector<PrimitiveRenderer*> uis;
	//�����_���[�`��
	for (auto& renderer : m_primitiveRenderer)
	{
		if (!renderer->GetActive())continue;
		if (renderer->GetisUiRender())
		{
			//UI�͐摗�肷��
			uis.push_back(renderer);
			continue;
		}
		renderer->Render(m_primitiveBatch.get(), camera);
	}

	//�摗�胂�f���`��
	for (auto& model : afterdraws)
	{
		model->Render(camera);
	}

	//UI�`��
	for (auto& renderer : uis)
	{
		renderer->Render(m_primitiveBatch.get(), camera);
	}
}
