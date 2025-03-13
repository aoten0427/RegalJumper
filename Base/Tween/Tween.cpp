// ================================================================ 
// �t�@�C���� : Tween.h
// �쐬�� : �i�R�ɓV
// ���� :  Tween���������߂̃N���X
// ================================================================
#include"pch.h"
#include"Tween.h"
#include"TweenManager.h"
#include"TweenCore.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
Tween::Tween(Object* object,bool reuse):Component(object)
	,
	m_core{nullptr},
	m_reuse{reuse}
{
	m_core = TweenManager::GetInstance()->AddTween(*this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Tween::~Tween()
{
	//�{�̂ɍ폜�v��
	if (m_core)m_core->Destroy();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o��</param>
void Tween::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//�R�A���Ȃ��ꍇ�Ԃ�
	if (!m_core)return;
	//�R�A���폜��ԂȂ玩�g���폜
	if (m_core->GetState() == TweenCore::State::DESTROY)
	{
		Destroy();
	}
}

/// <summary>
/// Int����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�R�A</returns>
TweenCore& Tween::DoInt(int& origin, int end, float time)
{
	m_core->DoInt(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Float����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�R�A</returns>
TweenCore& Tween::DoFloat(float& origin, float end, float time)
{
	m_core->DoFloat(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Vector2����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�R�A</returns>
TweenCore& Tween::DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time)
{
	m_core->DoVector2(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Vector3����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�R�A</returns>
TweenCore& Tween::DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time)
{
	m_core->DoVector3(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Vector4����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�R�A</returns>
TweenCore& Tween::DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time)
{
	m_core->DoVector4(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Quaternion����
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�R�A</returns>
TweenCore& Tween::DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time)
{
	m_core->DOQuaternion(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// �I��
/// </summary>
void Tween::Kill()
{
	//�R�A���Ȃ��ꍇ�Ԃ�
	if (!m_core)return;
	m_core->Kill();
}

/// <summary>
/// �ꎞ��~
/// </summary>
void Tween::Pause()
{
	//�R�A���Ȃ��ꍇ�Ԃ�
	if (!m_core)return;
	m_core->Pause();
}

/// <summary>
/// �ĊJ
/// </summary>
void Tween::Play()
{
	//�R�A���Ȃ��ꍇ�Ԃ�
	if (!m_core)return;
	m_core->Play();
}
