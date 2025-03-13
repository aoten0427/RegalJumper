// ================================================================ 
// �t�@�C���� : GameFade.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���̊�{�t�F�[�h
// ================================================================
#include"pch.h"
#include"GameFade.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/Sequence.h"
#include"Base/Tween/TweenCore.h"
#include"Base/Event/Subject.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
GameFade::GameFade(Canvas* canvas):Fade(canvas,"NormalFade")
	,
	m_position{ Screen::WIDTH * 2, Screen::CENTER_Y },
	m_closeFunction{nullptr}
{
	GetScene()->ChangeState(Scene::State::RESERVE);

	using namespace DirectX::SimpleMath;
	//��{���ݒ�
	SetPosition(m_position);
	SetSize(Vector2(Screen::WIDTH * 2, Screen::HEIGHT));
	SetColor(Vector4(0, 0, 0, 1));
	SetTexture("Fade1");

	m_sequence = AddComponent<Sequence>(this);
	//�t�F�[�h�C�������쐬
	m_sequence->AppendVector2(m_position, Vector2(Screen::CENTER_X, Screen::CENTER_Y), 0.7f).SetCompleteFunction([&]() {
		if (m_closeFunction)m_closeFunction();
		SetState(Fade::State::In);
		});
	//�N���[�Y�����쐬
	m_sequence->AppendVector2(m_position, Vector2(Screen::CENTER_X, Screen::CENTER_Y), 0.1f).SetChangeType(TweenCore::ChangeType::ReLoad).
			SetCompleteFunction([&]() {
			SetState(Fade::State::DoOut);
			GetScene()->ChangeState(Scene::State::FEAD);
		});
	//�t�F�[�h�A�E�g�����쐬
	m_sequence->AppendVector2(m_position, Vector2(-Screen::WIDTH, Screen::CENTER_Y), 0.7f).SetChangeType(TweenCore::ChangeType::ReLoad).
			SetCompleteFunction([&]() {
			SetState(Fade::State::Out);
			//�|�W�V�������Z�b�g
			m_position = Vector2(Screen::WIDTH * 2, Screen::CENTER_Y);
			//�V�[�P���X��������Ԃ�
			m_sequence->ReStart();
			m_sequence->Pause();
			GetScene()->ChangeState(Scene::State::RESERVE);
		});
	m_sequence->Pause();

	m_finishSubject = AddComponent<Subject<>>(this, "GameFade");
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void GameFade::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//�|�W�V�������Z�b�g
	SetPosition(m_position);
}

/// <summary>
/// �t�F�[�h�J�n
/// </summary>
/// <param name="function">�N���[�Y���̏���</param>
void GameFade::Start(std::function<void()> function)
{
	//�V�[�����t�F�[�h��Ԃ�
	GetScene()->ChangeState(Scene::State::FEAD);
	//�t�F�[�h�C����ԂɕύX
	SetState(Fade::State::DoIn);
	//������ݒ�
	m_closeFunction = function;
	//Sequence���J�n
	m_sequence->Play();
}


