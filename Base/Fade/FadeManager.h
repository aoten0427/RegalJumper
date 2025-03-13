// ================================================================ 
// �t�@�C���� : FadeManager
// �쐬�� : �i�R�ɓV
// ���� :  �t�F�[�h�̊Ǘ����s��
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"
#include"Base/Fade/Fade.h"


class FadeManager :public Singleton<FadeManager>
{
	friend class Singleton<FadeManager>;
private:
	FadeManager();
private:
	//���݉ғ����̃t�F�[�h
	Fade* m_currentFade;
	//�o�^����Ă���t�F�[�h
	std::unordered_map<std::string, Fade*> m_fades;
public:
	~FadeManager() = default;
	//�t�F�[�h�̊J�n(�ғ�����t�F�[�h,�t�F�[�h�A�E�g��̏���)
	void FadeStart(std::string fadeName, std::function<void()> function = nullptr);
	//�ғ����̃t�F�[�h�̏�Ԃ𓾂�
	Fade::State GetCurrentFadeState();
	//�t�F�[�h�o�^
	void AddFade(Fade* fade);
};