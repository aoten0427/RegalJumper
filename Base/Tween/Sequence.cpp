// ================================================================ 
// �t�@�C���� : Sequence.cpp
// �쐬�� : �i�R�ɓV
// ���� :  Tween�𕡐��Ǘ�����
// ================================================================

#include"pch.h"
#include"Sequence.h"
#include"TweenManager.h"
#include"TweenCore.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
Sequence::Sequence(Object* object):Component(object)
	,
	m_cores{},
	m_activeNumber{0}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sequence::~Sequence()
{
	//�R�A�ɍ폜�v��
	for (auto& core : m_cores)
	{
		core->Destroy();
	}
	m_cores.clear();
}

/// <summary>
/// int�ǉ�
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�ǉ��R�A</returns>
TweenCore& Sequence::AppendInt(int& origin, int end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoInt(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// float�ǉ�
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�ǉ��R�A</returns>
TweenCore& Sequence::AppendFloat(float& origin, float end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoFloat(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Vector2�ǉ�
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�ǉ��R�A</returns>
TweenCore& Sequence::AppendVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoVector2(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Vector3�ǉ�
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�ǉ��R�A</returns>
TweenCore& Sequence::AppendVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoVector3(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Vector4�ǉ�
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�ǉ��R�A</returns>
TweenCore& Sequence::AppendVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoVector4(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Quaternion�ǉ�
/// </summary>
/// <param name="origin">�ύX����l</param>
/// <param name="end">�I���l</param>
/// <param name="time">�ύX����</param>
/// <returns>�ǉ��R�A</returns>
TweenCore& Sequence::AppendQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DOQuaternion(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// ����
/// </summary>
void Sequence::Kill()
{
	for (auto& core : m_cores)
	{
		core->Kill();
	}
}

/// <summary>
/// �ĊJ
/// </summary>
void Sequence::Play()
{
	m_cores[m_activeNumber]->Play();
}

/// <summary>
/// �ꎞ��~
/// </summary>
void Sequence::Pause()
{
	m_cores[m_activeNumber]->Pause();
}

/// <summary>
/// ���[�v
/// </summary>
void Sequence::Loop()
{
	if (m_cores.empty())return;
	//�Ō���̊֐��擾
	std::function<void()> function = m_cores.back()->GetFunction();
	m_cores.back()->SetCompleteFunction([&, function]() {
		//�����̊֐������s
		if (function)function();
		//���X�^�[�g�������s
		ReStart();
		});
}

/// <summary>
/// �ŏ�����n�߂�
/// </summary>
void Sequence::ReStart()
{
	if (m_cores.empty())return;
	for (auto& core : m_cores)
	{
		core->ReStart();
		core->Pause();
	}
	m_cores[0]->Play();
	m_activeNumber = 0;
}

/// <summary>
/// �ǉ����̎葱��
/// </summary>
/// <param name="newCore">�ǉ��R�A</param>
void Sequence::AppendProcess(TweenCore* newCore)
{
	m_cores.push_back(newCore);
	//�X�V���~�߂�
	newCore->Pause();
	//��̏ꍇ�͍X�V���J�n���ĕԂ�
	if (m_cores.size() == 1)
	{
		newCore->Play();
		return;
	}

	//�����_�̍Ō���̔ԍ����擾
	int back = static_cast<int>(m_cores.size()) - 1;
	//�����_�̍Ō�� - 1�̊֐����擾
	std::function<void()> function = m_cores[back - 1]->GetFunction();
	//�Ō�� - 1�̏I���֐��ɍŌ����Play�֐����Z�b�g
	m_cores[back - 1]->SetCompleteFunction([&, function,back]() {
		//�����̊֐������s
		if (function)function();
		//�N��
		m_cores[back]->Play();
		m_activeNumber = back;
		});
}
