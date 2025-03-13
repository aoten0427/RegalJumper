// ================================================================ 
// �t�@�C���� : TweenCore.cpp
// �쐬�� : �i�R�ɓV
// ���� :  Tween�̎��s�{��
// ================================================================

#include"pch.h"
#include"TweenCore.h"
#include"TweenManager.h"
#include"TweenUpdate.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TweenCore::TweenCore()
	:
	m_state{State::PLAY},
	m_update{nullptr},
	m_delayTime{0},
	m_function{nullptr},
	m_loopCount{0},
	m_loopType{LoopType::Yoyo},
	m_reuse{false}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TweenCore::~TweenCore()
{
	m_update = nullptr;
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void TweenCore::Update(float deltatime)
{
	if (!m_update)return;
	//�v���C��ԂłȂ��Ȃ�Ԃ�
	if (m_state != State::PLAY)return;

	//�x�����Ԃ��߂��Ă��Ȃ��Ȃ猸�������Ԃ�
	if (m_delayTime > 0)
	{
		m_delayTime -= deltatime;
		return;
	}
	//�I���t���O���i�[
	bool isFinish = m_update->Update(deltatime);

	//�I���������s
	if (isFinish)
	{
		m_state = State::FINISH;
		//�֐����s
		DoFunction();

		//�I�����f
		if (m_loopCount == 0)
		{
			//�ė��p�t���O��false�̏ꍇ�폜
			if (!m_reuse)
			{
				Destroy();
			}
			return;
		}

		//���[�v����
		Loop();
	}
}

/// <summary>
/// �֐����s
/// </summary>
void TweenCore::DoFunction()
{
	//�֐����s
	if (m_function)m_function();
}

/// <summary>
/// ���[�v����
/// </summary>
void TweenCore::Loop()
{
	//���[�v�ݒ肪�Ȃ��ꍇ�Ԃ�
	if (m_loopCount == 0)return;
	//���[�v�J�E���g������
	if (m_loopCount > 0)m_loopCount--;
	//���[�v�^�C�v�ɂ���Ēl��ύX
	switch (m_loopType)
	{
	case TweenCore::LoopType::Yoyo:
		if (m_update)m_update->Yoyo();
		break;
	case TweenCore::LoopType::ReStart:
		if (m_update)m_update->ReStart();
		break;
	case TweenCore::LoopType::Incremental:
		if (m_update)m_update->Incremental();
		break;
	default:
		break;
	}
	m_state = State::PLAY;
}

/// <summary>
/// �폜
/// </summary>
void TweenCore::Destroy()
{
	//�폜�����˗�
	TweenManager::GetInstance()->CoreDestroyOn();
	//�j���Ԃ�
	m_state = State::DESTROY;
}


/// <summary>
/// Int����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>���g</returns>
TweenCore& TweenCore::DoInt(int& origin, int end, float time)
{
	m_update = std::make_unique<TweenUpdate<int>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Float����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>���g</returns>
TweenCore& TweenCore::DoFloat(float& origin, float end, float time)
{
	m_update = std::make_unique<TweenUpdate<float>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Vector2����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>���g</returns>
TweenCore& TweenCore::DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Vector2>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Vector3����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>���g</returns>
TweenCore& TweenCore::DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Vector3>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Vector4����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>���g</returns>
TweenCore& TweenCore::DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Vector4>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Quaternion����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>���g</returns>
TweenCore& TweenCore::DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Quaternion>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}



/// <summary>
/// �x�����Ԃ�ݒ�
/// </summary>
/// <param name="delaytime">�x������</param>
/// <returns>���g</returns>
TweenCore& TweenCore::SetDelay(float delaytime)
{
	m_delayTime = delaytime;
	return *this;
}

/// <summary>
/// �I�����ɌĂяo���֐���ݒ�
/// </summary>
/// <param name="action">�Ăяo���֐�</param>
/// <returns>���g</returns>
TweenCore& TweenCore::SetCompleteFunction(std::function<void()> action)
{
	m_function = action;
	return *this;
}

/// <summary>
/// �C�[�W���O�̎�ނ�ݒ�
/// </summary>
/// <param name="easy">�C�[�W���O�^�C�v</param>
/// <returns>���g</returns>
TweenCore& TweenCore::SetEase(Easing::Ease easy)
{
	if (m_update)m_update->SetEase(easy);
	return *this;
}

/// <summary>
/// ���[�v��ݒ�
/// </summary>
/// <param name="count">���[�v�� -1�Ŗ���</param>
/// <param name="looptype">���[�v�^�C�v</param>
/// <returns>���g</returns>
TweenCore& TweenCore::SetLoop(int count, LoopType looptype)
{
	m_loopCount = count;
	m_loopType = looptype;
	return *this;
}

/// <summary>
/// �ω��^�C�v�̕ύX
/// </summary>
/// <param name="type">�ω��^�C�v</param>
/// <returns>���g</returns>
TweenCore& TweenCore::SetChangeType(ChangeType type)
{
	m_changeType = type;
	return *this;
}

/// <summary>
/// ���Έړ��ɐݒ�
/// </summary>
/// <returns>���g</returns>
TweenCore& TweenCore::Relative()
{
	if (m_update)m_update->Relative();
	return *this;
}

/// <summary>
/// �����l�����ݒl�ɕύX
/// </summary>
/// <returns>���g</returns>
TweenCore& TweenCore::ReLoad()
{
	if (m_update)m_update->ReLoad();
	return *this;
}

/// <summary>
/// �I��������
/// </summary>
void TweenCore::Kill()
{
	if (m_update)m_update->Kill();
}

/// <summary>
/// �~�߂�
/// </summary>
void TweenCore::Pause()
{
	m_state = State::PAUSE;
}

/// <summary>
/// �ĊJ
/// </summary>
void TweenCore::Play()
{
	m_state = State::PLAY;
	switch (m_changeType)
	{
	case TweenCore::ChangeType::Default:
		break;
	case TweenCore::ChangeType::Relative:
		Relative();
		break;
	case TweenCore::ChangeType::ReLoad:
		ReLoad();
		break;
	default:
		break;
	}
}

/// <summary>
/// �ăX�^�[�g����
/// </summary>
void TweenCore::ReStart()
{
	if (!m_update)return;
	m_state = State::PLAY;
	m_delayTime = 0;
	m_update->ReStart();
}





