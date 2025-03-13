// ================================================================ 
// �t�@�C���� : PlayCanvas.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���L�����o�X
// ================================================================
#include"pch.h"
#include"PlayCanvas.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"
#include"Base/Object/UnbreakableManager.h"
#include"Game/GameManager.h"
#include"Game/Play/UI/Time.h"
#include"Game/Play/UI/UIReticle.h"
#include"Game/Play/UI/Pause/Pause.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
PlayCanvas::PlayCanvas(Scene* scene):GameCanvas(scene)
	,
	m_gameTimer{},
	m_time{nullptr}
{
	//�^�C�}�[�쐬
	m_time = scene->AddObject<Time>(this);
	m_time->SetStartX(520);
	m_time->SetPositionY(50);
	m_time->SetSize(DirectX::SimpleMath::Vector2(40, 70));
	//���e�B�N���͈͍쐬
	scene->AddObject<UIReticle>(this);
	//�|�[�Y�쐬
	scene->AddObject<Pause>(this);

	//�I���I�u�U�[�o�[�쐬
	m_finishObserver = AddComponent<Observer<>>(this);
	m_finishObserver->SetFunction([&]() {
		GameManager::GetInstance()->SetResultTimer(m_gameTimer);
		});
	m_finishObserver->RegistrationSubject("SpiderExit");
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void PlayCanvas::ObjectUpdate(float deltatime)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//�v���C���ԍX�V
	m_gameTimer += deltatime;
	m_time->SetCount(m_gameTimer);
}
