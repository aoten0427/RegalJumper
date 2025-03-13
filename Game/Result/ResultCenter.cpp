// ================================================================ 
// �t�@�C���� : ResultCenter.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�V�[���̊Ǘ�
// ================================================================
#include"pch.h"
#include"ResultCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonResources.h"
#include"Base/Input/DirectXInputs.h"
#include"Base/Event/Observer.h"
#include"Base/Event/Subject.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
ResultCenter::ResultCenter(Scene* scene):Object(scene)
{
	//�v���C��Ԃւ̑J�ڃI�u�U�[�o-
	m_beginObserver = AddComponent<Observer<>>(this);
	m_beginObserver->SetFunction([&]() {GetScene()->ChangeState(Scene::State::PLAY); });
	m_beginObserver->RegistrationSubject("Reserve");
	//���U���g�����̃X�L�b�v�T�u�W�F�N�g
	m_skipSubject = AddComponent<Subject<>>(this, "ResultSkip");

	GetScene()->ChangeState(Scene::State::PLAY);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void ResultCenter::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//���}�E�X�N���b�N
	if (GetCommonResources()->GetInput()->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//�v���C��Ԃ̏ꍇ�X�L�b�v����
		if (GetScene()->GetState() == Scene::State::PLAY)
		{
			m_skipSubject->Notify();
			GetScene()->ChangeState(Scene::State::END);
		}
		//�I����Ԃ̏ꍇ�Z���N�g�V�[���֑J��
		else if (GetScene()->GetState() == Scene::State::END)
		{
			FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
				GetScene()->ChangeScene(Scene::SceneID::SELECT);
				});
		}
	}
}
