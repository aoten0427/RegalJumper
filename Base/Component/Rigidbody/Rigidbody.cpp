// ================================================================ 
// �t�@�C���� : Rigidbody.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �I�u�W�F�N�g�̈ړ����Ǘ�����
// ================================================================

#include"pch.h"
#include"Rigidbody.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/RIgidbodyManager.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
Rigidbody::Rigidbody(Object* object):Component(object)
	,
	m_mass{ 1.0f },
	m_velocity{},
	m_addforce{},
	m_isFixed{ false },
	m_reduction{ 1.0f },
	m_isDetection{ false }
{
	//�}�l�[�W���[�֓o�^
	auto rigidbodyManager = object->GetScene()->GetRigidbodyManager();
	rigidbodyManager->AddRigidbody(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Rigidbody::~Rigidbody()
{
	//�}�l�[�W���[����폜
	auto rigidbodyManager = GetObject()->GetScene()->GetRigidbodyManager();
	rigidbodyManager->RemoveRigidbody(this);
}

/// <summary>
/// �X�s�[�h�̌v�Z
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Rigidbody::Compute(float deltatime)
{
	//�Œ蒆�Ȃ�p�X
	if (m_isFixed)return;
	using namespace DirectX::SimpleMath;

	//���x���v�Z
	m_velocity = m_addforce * deltatime;

	//�I�u�W�F�N�g�ړ�
	GetObject()->GetTransform()->Translate(m_velocity);

	//���x����
	m_addforce *= m_reduction;
}

/// <summary>
/// �|�W�V�����擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Rigidbody::GetPosition()
{
	return GetObject()->GetTransform()->GetRotatePosition();
}


