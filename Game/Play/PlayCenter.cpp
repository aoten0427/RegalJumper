// ================================================================ 
// �t�@�C���� : PlayCenter.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���̊Ǘ�
// ================================================================

#include"pch.h"
#include"PlayCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"
#include"Base/Event/Subject.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
PlayCenter::PlayCenter(Scene* scene) :Object(scene)
{
	//���Z�b�g�Ăяo���I�u�U�[�o�[�쐬
	m_resetObserver = AddComponent<Observer<>>(this);
	m_resetObserver->SetFunction([&]() {Reset(); });
	m_resetObserver->RegistrationSubject("PlayerDeath");

	//���Z�b�g�p�T�u�W�F�N�g�쐬
	m_resetSubject = AddComponent<Subject<>>(this, "PlayReset");

	//���U���g�V�[���J�ڃI�u�U�[�o�쐬
	m_exitObserver = AddComponent<Observer<>>(this);
	m_exitObserver->SetFunction([&]() {ToResult(); });
	m_exitObserver->RegistrationSubject("SpiderExit");
}

/// <summary>
/// �v���C�V�[�����Z�b�g����
/// </summary>
void PlayCenter::Reset()
{
	FadeManager::GetInstance()->FadeStart("PlayFade", [&]() {
		m_resetSubject->Notify();
		});
}

/// <summary>
/// ���U���g�V�[���J�ڏ���
/// </summary>
void PlayCenter::ToResult()
{
	FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
		GetScene()->ChangeScene(Scene::SceneID::RESULT);
		});
}