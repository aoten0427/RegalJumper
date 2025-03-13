// ================================================================ 
// �t�@�C���� : Pause.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C��ʃ|�[�Y
// ================================================================
#include"pch.h"
#include"Pause.h"
#include"Base/Base.h"
#include"Base/Screen.h"
#include"Base/Event/Subject.h"
#include"Base/Event/Observer.h"
#include"Base/Fade/FadeManager.h"
#include"Game/GameManager.h"
#include"Game/Play/UI/Pause/PauseButton.h"
#include"Game/Play/UI/Pause/PauseExitButton.h"
#include"Game/Play/UI/Pause/QuitPage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
Pause::Pause(Canvas* canvas):UserInterface(canvas)
	,
	m_isOpen{false},
	m_UIBase{nullptr},
	m_base{nullptr},
	m_openSubject{nullptr},
	m_closeSubject{nullptr},
	m_oldSceneState{Scene::State::PLAY}
{
	using namespace DirectX::SimpleMath;
	
	//���w�i
	SetSize(Vector2(Screen::WIDTH, Screen::HEIGHT));
	SetColor(Vector4(1, 1, 1, 0.5));
	m_UIBase = GetScene()->AddObject<Object>(GetScene());
	m_UIBase->GetTransform()->SetParent(GetTransform());

	//�x�[�X�쐬
	m_base = GetScene()->AddObject<UserInterface>(canvas, "Pause", 1);
	m_base->SetSize(Vector2(640, 640));
	m_base->GetTransform()->SetParent(m_UIBase->GetTransform());

	//�ޏo�y�[�W�쐬
	m_quitPage = GetScene()->AddObject<QuitPage>(canvas, this);

	PauseButton* quitButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::QUIT);
	quitButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	quitButton->SetFunction([&]() {
		m_quitPage->SetActive(true);
		SetActive(false);
		});

	//�e�{�^���쐬
	//���X�^�[�g�{�^��
	PauseButton* reStartButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::RESTART);
	reStartButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	reStartButton->SetFunction([&]() {
		//�v���C�V�[���ւ̈ڍs���Z�b�g
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::PLAY);
			});
		});

	//�X�e�[�W�Z���N�g�{�^��
	PauseButton* stageSelectButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::STAGESELECT);
	stageSelectButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	stageSelectButton->SetFunction([&]() {
		//�Z���N�g�V�[���ւ̈ڍs���Z�b�g
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::SELECT);
			});
		});

	//�I�v�V�����{�^��
	PauseButton* optionButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::OPTION);
	optionButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	optionButton->SetFunction([&]() {
		//�I�v�V�������J��
		GameManager::GetInstance()->OpenOption();
		m_UIBase->SetActive(false);
		});

	

	//�ޏo�{�^���쐬
	PauseExitButton* exitButton = GetScene()->AddObject<PauseExitButton>(canvas);
	exitButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	exitButton->SetFunction([&]() {Close(); });
	


	//�T�u�W�F�N�g�쐬
	m_openSubject = AddComponent<Subject<>>(this, "PauseOpen");
	m_closeSubject = AddComponent<Subject<>>(this, "PauseClose");
	//�I�v�V�����{�^���s���I�u�U�[�o�[�쐬
	Observer<>* optionClose = AddComponent<Observer<>>(this);
	optionClose->SetFunction([&]() {m_UIBase->SetActive(true); });
	optionClose->RegistrationSubject("OptionClose");

	//�����Ȃ�����
	SetActive(false);
}

/// <summary>
/// �A�b�v�f�[�g �J�����𔻒f
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Pause::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	Open();
}

/// <summary>
/// �J��
/// </summary>
void Pause::Open()
{
	if (m_isOpen)return;
	//�G�X�P�[�v�������f
	if (!GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::Escape))return;
	//�V�[����������Ԃ��v���C��Ԃ�
	if (GetScene()->GetState() == Scene::State::RESERVE || GetScene()->GetState() == Scene::State::PLAY)
	{
		m_isOpen = true;
		//������悤�ɂ���
		SetActive(true);
		//�X�g�b�v��ԂɕύX
		GetScene()->ChangeState(Scene::State::STOP);
		//�T�u�W�F�N�g���s
		m_openSubject->Notify();
		//��Ԃ��L�^
		m_oldSceneState = GetScene()->GetState();
		//�J�[�\�����I���ɂ���
		GameManager::GetInstance()->ViewCursor(true);
	}
}

/// <summary>
/// ����
/// </summary>
void Pause::Close()
{
	m_isOpen = false;
	//�����Ȃ�����
	SetActive(false);
	//�T�u�W�F�N�g���s
	m_closeSubject->Notify();
	//�V�[���̏�Ԃ�߂�
	GetScene()->ChangeState(m_oldSceneState);
	//�J�[�\�����I�t�ɂ���
	GameManager::GetInstance()->ViewCursor(false);
}
