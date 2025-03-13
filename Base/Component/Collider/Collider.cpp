// ================================================================ 
// �t�@�C���� : Collider.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �e�����蔻��
// ================================================================
#include"pch.h"
#include"Collider.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/CollisonManager.h"
#include"Base/CommonManager/DebugCollider.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="tag">�R���C�_�[���</param>
/// <param name="type">�R���W�������</param>
/// <param name="rigidbody">���W�b�h�{�f�B</param>
/// <param name="view">�\���t���O</param>
Collider::Collider(Object* object, ColliderTag tag, CollisionType type, Rigidbody* rigidbody,bool view):Component(object)
	,
	m_colliderTag{ tag },
	m_transform{object->GetTransform()},
	m_rigidbody{ rigidbody },
	m_position{DirectX::SimpleMath::Vector3::Zero},
	m_scale{DirectX::SimpleMath::Vector3::One},
	m_matrix{DirectX::SimpleMath::Matrix::Identity},
	m_isNotPas{ false }
{
	UNREFERENCED_PARAMETER(view);

	//�R���W�����}�l�[�W���[�ւ̓o�^
	auto collision = GetObject()->GetScene()->GetCollisionManager();
	collision->AddCollider(this, type);

#if defined(_DEBUG)
	//�f�o�b�O�\���̓o�^
	if (view)
	{
		auto debug = GetObject()->GetScene()->GetDebugCollider();
		debug->AddCollider(this);
	}
#endif
	//matrix������
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Collider::~Collider()
{
	//�f�o�b�O�\������폜
#if defined(_DEBUG)
	auto debug = GetObject()->GetScene()->GetDebugCollider();
	debug->RemoveCollider(this);
#endif
	//�R���W�����}�l�[�W���[����폜
	auto collision = GetObject()->GetScene()->GetCollisionManager();
	collision->ReMoveCollider(this);
}

/// <summary>
/// �|�W�V�����Z�b�g
/// </summary>
/// <param name="position">�ύX�|�W�V����</param>
void Collider::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// �X�P�[���Z�b�g
/// </summary>
/// <param name="scale">�ύX�X�P�[��</param>
void Collider::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// ���[���h�|�W�V�����擾
/// </summary>
/// <returns>���[���h�|�W�V����</returns>
DirectX::SimpleMath::Vector3 Collider::GetWorldPosition()
{
	return GetTransform().GetRotatePosition() + m_position;
}

/// <summary>
/// ���[���h�X�P�[���擾
/// </summary>
/// <returns>���[���h�X�P�[��</returns>
DirectX::SimpleMath::Vector3 Collider::GetWorldScale()
{
	return GetTransform().GetWorldScale() * m_scale * DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
}

/// <summary>
/// matrix�擾
/// </summary>
/// <returns>���[���h�s��</returns>
DirectX::SimpleMath::Matrix Collider::GetWorldMatrix()
{
	return m_matrix * GetTransform().GetWorldMatrix();
}

/// <summary>
/// �o�E���f�B���O�X�t�B�A�p���a�擾
/// </summary>
/// <returns>���g�̔��a</returns>
float Collider::GetRadius()
{
	return 1.0f;
}


//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          AABB                             ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////


/// <summary>
/// AABB �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="type">�R���W�������</param>
/// <param name="rigidbody">���W�b�h�{�f�B</param>
/// <param name="view">�\���t���O</param>
AABB::AABB(Object* object, CollisionType type, Rigidbody* rigidbody, bool view):Collider(object,ColliderTag::AABB,type,rigidbody,view)
{
}

/// <summary>
/// matrix�擾(��]��������������)
/// </summary>
/// <returns>�ʒu�Ƒ傫���݂̂�Ή��������s��</returns>
DirectX::SimpleMath::Matrix AABB::GetWorldMatrix()
{
	Transform trans = GetTransform();
	trans.SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	return trans.GetWorldMatrix();
}

/// <summary>
/// �e���̑傫���擾
/// </summary>
/// <returns>�傫��</returns>
DirectX::SimpleMath::Vector3 AABB::GetExtents()
{
	return GetObject()->GetTransform()->GetWorldScale() * DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f) * GetScale();
}

/// <summary>
/// ���a�擾
/// </summary>
/// <returns>���g�̔��a</returns>
float AABB::GetRadius()
{
	DirectX::SimpleMath::Vector3 extents = GetExtents();
	return std::sqrtf(extents.x * extents.x + extents.y * extents.y + extents.z * extents.z);
}

//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          OBB                              ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////

/// <summary>
/// OBB �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="type">�R���W�������</param>
/// <param name="rigidbody">���W�b�h�{�f�B</param>
/// <param name="view">�\���t���O</param>
OBB::OBB(Object* object, CollisionType type, Rigidbody* rigidbody, bool view) :Collider(object, ColliderTag::OBB, type, rigidbody, view)
{
}


/// <summary>
///  �e���̑傫���擾
/// </summary>
/// <returns>�傫��</returns>
DirectX::SimpleMath::Vector3 OBB::GetExtents()
{
	return GetObject()->GetTransform()->GetWorldScale() * DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f) * GetScale();
}

/// <summary>
/// ���a�擾	
/// </summary>
/// <returns>���g�̔��a</returns>
float OBB::GetRadius()
{
	DirectX::SimpleMath::Vector3 extents = GetExtents();
	return std::sqrtf(extents.x * extents.x + extents.y * extents.y + extents.z * extents.z);
}

//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          Sphere                           ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////

/// <summary>
/// �� �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="type">�R���W�������</param>
/// <param name="rigidbody">���W�b�h�{�f�B</param>
/// <param name="view">�\���t���O</param>
/// <param name="radius">���a</param>
Sphere::Sphere(Object* object, CollisionType type, Rigidbody* rigidbody, bool view, float radius) :Collider(object, ColliderTag::SPHERE, type, rigidbody, view)
	,
	m_radius{radius}
{

}

/// <summary>
/// ���a�ݒ�
/// </summary>
/// <param name="radius">�ύX���a</param>
void Sphere::SetRadius(float radius)
{
	m_radius = radius;
}

/// <summary>
/// ���a�擾	
/// </summary>
/// <returns>���g�̔��a</returns>
float Sphere::GetRadius()
{
	DirectX::SimpleMath::Vector3 scale = GetTransform().GetWorldScale();

	return m_radius * std::max(scale.x, std::max(scale.y, scale.z));
}



//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          Segment                          ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////

/// <summary>
/// ���� �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="type">�R���W�������</param>
/// <param name="rigidbody">���W�b�h�{�f�B</param>
/// <param name="view">�\���t���O</param>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
Segment::Segment(Object* object, CollisionType type, Rigidbody* rigidbody, bool view, DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
	:Collider(object, ColliderTag::SEGMENT, type, rigidbody, view)
	,
	m_strPos{start},
	m_endPos{end}
{
}

/// <summary>
/// ���[�J���n�_�擾
/// </summary>
/// <returns>�I�u�W�F�N�g�̍��W���l�����Ȃ��n�_</returns>
DirectX::SimpleMath::Vector3 Segment::GetLocalStartPos()
{
	Transform* trans = GetObject()->GetTransform();
	DirectX::SimpleMath::Vector3 strpos = DirectX::SimpleMath::Vector3::Transform(m_strPos, trans->GetWorldRotate());
	return strpos;
}

/// <summary>
/// ���[�J���I�_�擾
/// </summary>
/// <returns>�I�u�W�F�N�g�̍��W���l�����Ȃ��I�_</returns>
DirectX::SimpleMath::Vector3 Segment::GetLocalEndPos()
{
	Transform* trans = GetObject()->GetTransform();
	DirectX::SimpleMath::Vector3 endpos = DirectX::SimpleMath::Vector3::Transform(m_endPos, trans->GetWorldRotate());
	return endpos;
}

/// <summary>
/// ���[���h�n�_�擾
/// </summary>
/// <returns>�I�u�W�F�N�g�̍��W���l�������n�_</returns>
DirectX::SimpleMath::Vector3 Segment::GetWorldStartPos()
{
	Transform* trans = GetObject()->GetTransform();
	return trans->GetRotatePosition() + GetLocalStartPos();
}

/// <summary>
///	���[���h�I�_�擾
/// </summary>
/// <returns>�I�u�W�F�N�g�̍��W���l�������I�_</returns>
DirectX::SimpleMath::Vector3 Segment::GetWorldEndPos()
{
	Transform* trans = GetObject()->GetTransform();
	return trans->GetRotatePosition() + GetLocalEndPos();
}

/// <summary>
/// �n�_����I�_�ւ̃x�N�g���擾
/// </summary>
/// <returns>�n�_����I�_�ւ̃x�N�g��</returns>
DirectX::SimpleMath::Vector3 Segment::GetVector()
{
	return GetLocalEndPos() - GetLocalStartPos();
}

/// <summary>
/// �n�_����I�_�ւ̌����擾
/// </summary>
/// <returns>�n�_����I�_�܂ł̌���</returns>
DirectX::SimpleMath::Vector3 Segment::GetDirection()
{
	DirectX::SimpleMath::Vector3 vec = GetVector();
	vec.Normalize();
	return vec;
}

/// <summary>
/// �����擾
/// </summary>
/// <returns>����</returns>
float Segment::GetLength()
{
	return GetVector().Length();
}

/// <summary>
/// ���a�擾	
/// </summary>
/// <returns>���a</returns>
float Segment::GetRadius()
{
	return GetLength();
}


