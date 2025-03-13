// ================================================================ 
// �t�@�C���� : Model3D.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���f���`����s��
// ================================================================

#include"pch.h"
#include"Model3D.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Resource/GameResources.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/Object/Object.h"
#include"Base/Camera/Camera.h"
#include"Base/Component/Transform/Transform.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="modelname">�ǂݍ��݃��f����</param>
/// <param name="renderOrder">�`�揀</param>
Model3D::Model3D(Object* object, std::string modelname, int renderOrder):Component(object)
	,
	m_renderOrder(renderOrder),
	m_model{nullptr},
	m_position{DirectX::SimpleMath::Vector3::Zero},
	m_scale{DirectX::SimpleMath::Vector3::One},
	m_rotate{ DirectX::SimpleMath::Quaternion::Identity },
	m_matrix{DirectX::SimpleMath::Matrix::Identity},
	m_render{nullptr},
	m_isAfterRender{false},
	m_isShadow{true}
{
	//�`��}�l�[�W���[�ւ̓o�^
	object->GetScene()->GetRenderManager()->AddModel3D(this);

	//���f�������ݒ肳��Ă����烍�[�h����
	if (modelname != Config::NONE_FILE)Load(modelname);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Model3D::~Model3D()
{
	//�`��}�l�[�W���[����폜
	GetObject()->GetScene()->GetRenderManager()->RemoveModel3D(this);
}

/// <summary>
/// ���f���ǂݍ���
/// </summary>
/// <param name="name">���f����</param>
void Model3D::Load(std::string name)
{
	m_model = GameResources::GetInstance()->GetModel(name);
}

/// <summary>
/// ���[���hmatrix�擾
/// </summary>
/// <returns>���[���h�s��</returns>
DirectX::SimpleMath::Matrix Model3D::GetWorldMatrix()
{
	return m_matrix * GetObject()->GetTransform()->GetWorldMatrix();
}


/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void Model3D::Render(const Camera& camera)
{
	
	if (m_render)
	{
		m_render(camera);
	}
	else if(m_model != nullptr)
	{
		auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
		auto states = GetCommonResources()->GetCommonStates();
		m_model->Draw(context, *states,GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
	
}

/// <summary>
/// �`�揇�ύX
/// </summary>
/// <param name="renderOrder">�D��x</param>
void Model3D::ChangeRenderOrder(int renderOrder)
{
	m_renderOrder = renderOrder;
}

/// <summary>
/// �|�W�V�����Z�b�g
/// </summary>
/// <param name="position">�ʒu</param>
void Model3D::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	m_position = position;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// �X�P�[���Z�b�g
/// </summary>
/// <param name="scale">�X�P�[��</param>
void Model3D::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	m_scale = scale;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// ��]�Z�b�g
/// </summary>
/// <param name="rotate">��]</param>
void Model3D::SetRotate(DirectX::SimpleMath::Quaternion roteto)
{
	m_rotate = roteto;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// �ʕ`��Z�b�g
/// </summary>
/// <param name="render">�ʕ`��</param>
void Model3D::SetRender(std::function<void(const Camera&)> render)
{
	m_render = render;
}

/// <summary>
/// �V�[���؂�ւ��C�x���g
/// </summary>
/// <param name="scene">�ύX�V�[��</param>
void Model3D::LoadScene(Scene* scene)
{
	//�`��}�l�[�W���[�ւ̓o�^
	scene->GetRenderManager()->AddModel3D(this);
}
