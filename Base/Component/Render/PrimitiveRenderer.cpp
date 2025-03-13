// ================================================================ 
// �t�@�C���� : PrimitiveRenderer.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���~�e�B�u�o�b�`�ł̕`����s��
// ================================================================
#include"pch.h"
#include"PrimitiveRenderer.h"
#include"Base/Resource/GameResources.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/Object/Object.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="filename">�ǂݍ��݉摜</param>
/// <param name="renderOrder">�`�揇</param>
/// <param name="ui">UI���̔���</param>
PrimitiveRenderer::PrimitiveRenderer(Object* object, std::string filename, int renderOrder, bool ui):Component(object)
	,
	m_renderOrder{renderOrder},
	m_isUi(ui),
	m_render{nullptr}
{
	//�`��}�l�[�W���[�ɓo�^
	object->GetScene()->GetRenderManager()->AddPrimitiveRenderer(this);
	//�摜�ǂݍ���
	if (filename != Config::NONE_FILE)Load(filename);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PrimitiveRenderer::~PrimitiveRenderer()
{
	//�`��}�l�[�W���[����폜
	GetObject()->GetScene()->GetRenderManager()->RemovePrimitiveRenderer(this);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="primitiveBatch">�v���~�e�B�u�o�b�`</param>
/// <param name="camera">�J����</param>
void PrimitiveRenderer::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	if (m_render == nullptr)return;
	m_render(primitiveBatch, camera);
}

/// <summary>
/// �摜���[�h
/// </summary>
/// <param name="filename">�摜��</param>
void PrimitiveRenderer::Load(std::string filename)
{
	auto resource = GameResources::GetInstance();
	m_texture = resource->GetTexture(filename);
}

/// <summary>
/// �D��x�ύX
/// </summary>
/// <param name="order">�D��x</param>
void PrimitiveRenderer::SetRenderOrder(int order)
{
	m_renderOrder = order;
	//�`��}�l�[�W���[�ɓo�^
	GetObject()->GetScene()->GetRenderManager()->ChangeRenderOrder(this);
}

/// <summary>
/// �V�[���؂�ւ��C�x���g
/// </summary>
/// <param name="scene">�ύX�V�[��</param>
void PrimitiveRenderer::LoadScene(Scene* scene)
{
	//�`��}�l�[�W���[�ɓo�^
	scene->GetRenderManager()->AddPrimitiveRenderer(this);
}
