// ================================================================ 
// �t�@�C���� : FadeManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �t�F�[�h�̊Ǘ����s��
// ================================================================

#include"pch.h"
#include"FadeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
FadeManager::FadeManager()
	:
	m_currentFade{nullptr},
	m_fades{}
{
}

/// <summary>
/// �t�F�[�h�̊J�n
/// </summary>
/// <param name="fadeName">�ғ�����t�F�[�h</param>
/// <param name="function">�t�F�[�h�A�E�g��̏���</param>
void FadeManager::FadeStart(std::string fadeName, std::function<void()> function)
{
	//�t�F�[�h����
	if (m_fades.find(fadeName) != m_fades.end())
	{
		//�ғ��������ׂ�
		if (m_fades[fadeName]->GetState() == Fade::State::Out)
		{
			//�ғ��t�F�[�h�ɃZ�b�g
			m_currentFade = m_fades[fadeName];
			m_currentFade->Start(function);
		}
	}
}

/// <summary>
/// �ғ����̃t�F�[�h�̏�Ԃ𓾂�
/// </summary>
/// <returns>�ғ��t�F�[�h�̏��</returns>
Fade::State FadeManager::GetCurrentFadeState()
{
	//�ғ��t�F�[�h�̏�Ԃ�Ԃ�
	if (m_currentFade != nullptr)
	{
		return m_currentFade->GetState();
	}
	return Fade::State::Out;
}

/// <summary>
/// �t�F�[�h�ǉ�
/// </summary>
/// <param name="fade">�ǉ��t�F�[�h</param>
void FadeManager::AddFade(Fade* fade)
{
	m_fades.insert({ fade->GetName(),fade });
}
