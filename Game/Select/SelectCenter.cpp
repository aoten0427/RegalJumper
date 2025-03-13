// ================================================================ 
// �t�@�C���� : SelectCenter.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[�����Ǘ�
// ================================================================
#include"pch.h"
#include"SelectCenter.h"
#include"Base/Fade/FadeManager.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
SelectCenter::SelectCenter(Scene* scene):Object(scene)
{
	//�J�n�I�u�U�[�o�[�쐬
	m_begin = AddComponent<Observer<>>(this);
	m_begin->SetFunction([&]() {GetScene()->ChangeState(Scene::State::PLAY); });
	m_begin->RegistrationSubject("Reserve");

	//�I���I�u�U�[�o�[�쐬
	m_finish = AddComponent<Observer<>>(this);
	m_finish->SetFunction([&]() {
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::PLAY);
			});
		});
	m_finish->RegistrationSubject("SpiderExit");
}
