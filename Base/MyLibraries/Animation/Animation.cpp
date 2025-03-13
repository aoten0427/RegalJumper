// ================================================================ 
// �t�@�C���� : Animation.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �ʒu�Ɖ�]��ω�������A�j���[�V����
// ================================================================
#include"pch.h"
#include"Animation.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="holder">�����I�u�W�F�N�g</param>
Animation::Animation(Object* holder)
	:
	m_holder{holder},
	m_changePosition{false,DirectX::SimpleMath::Vector3::Zero},
	m_positionSequence{nullptr},
	m_changeRotate{false,DirectX::SimpleMath::Quaternion::Identity},
	m_rotateSequence{nullptr}
{
}

/// <summary>
/// �A�j���[�V�����A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Animation::AnimationUpdate()
{
	//�|�W�V�����A�j���[�V����
	if (m_changePosition.first)
	{
		m_holder->GetTransform()->SetPosition(m_changePosition.second);
	}
	//��]�A�j���[�V����
	if (m_changeRotate.first)
	{
		m_holder->GetTransform()->SetRotate(m_changeRotate.second);
	}
}

/// <summary>
/// �|�W�V�����A�j���[�V�����ǉ�
/// </summary>
/// <param name="position">�ύX��</param>
/// <param name="speed">�ύX�X�s�[�h</param>
/// <param name="ease">�C�[�W���O�^�C�v</param>
/// <param name="delay">�f�B���C����</param>
void Animation::AddPositionAnimation(DirectX::SimpleMath::Vector3 position, float speed, std::string ease, float delay)
{
	//�L���t���O���Z�b�g
	m_changePosition.first = true;
	//�V�[�N�G���X�쐬
	if (m_positionSequence == nullptr)m_positionSequence = m_holder->AddComponent<Sequence>(m_holder);
	//Tween�ݒ�
	m_positionSequence->AppendVector3(m_changePosition.second, position, speed).SetChangeType(TweenCore::ChangeType::ReLoad).SetDelay(delay);
}

/// <summary>
/// �|�W�V�����A�j���[�V�������[�v�ݒ�
/// </summary>
void Animation::PositionLoop()
{
	if(m_positionSequence)m_positionSequence->Loop();
}

/// <summary>
/// ��]�A�j���[�V�����ǉ�
/// </summary>
/// <param name="rotate">�ύX��</param>
/// <param name="speed">�ύX�X�s�[�h</param>
/// <param name="ease">�C�[�W���O�^�C�v</param>
/// <param name="delay">�f�B���C����</param>
void Animation::AddRotateAnimation(DirectX::SimpleMath::Quaternion rotate, float speed, std::string ease, float delay)
{
	//�L���t���O���Z�b�g
	m_changeRotate.first = true;
	//�V�[�N�G���X�쐬
	if (m_rotateSequence == nullptr)m_rotateSequence = m_holder->AddComponent<Sequence>(m_holder);
	//Tween�ݒ�
	m_rotateSequence->AppendQuaternion(m_changeRotate.second, rotate, speed).SetChangeType(TweenCore::ChangeType::ReLoad).SetDelay(delay);
}

/// <summary>
/// ��]�A�j���[�V�������[�v�ݒ�
/// </summary>
void Animation::RotateLoop()
{
	if(m_rotateSequence)m_rotateSequence->Loop();
}

/// <summary>
/// �J�n����
/// </summary>
void Animation::Play()
{
	//�J�n�ʒu��ݒ�
	m_changePosition.second = m_holder->GetTransform()->GetPosition();
	m_changeRotate.second = m_holder->GetTransform()->GetRotate();
	//���X�^�[�g����
	if (m_positionSequence)m_positionSequence->ReStart();
	if (m_rotateSequence)m_rotateSequence->ReStart();
}

/// <summary>
/// �I������
/// </summary>
void Animation::End()
{
	if(m_positionSequence)m_positionSequence->Pause();
	if(m_rotateSequence)m_rotateSequence->Pause();
}


