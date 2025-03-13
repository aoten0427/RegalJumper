// ================================================================ 
// �t�@�C���� : PlayFade.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[�����Z�b�g�p�t�F�[�h
// ================================================================
#include"pch.h"
#include"PlayFade.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
PlayFade::PlayFade(Canvas* canvas):Fade(canvas,"PlayFade")
	,
	m_position{ Screen::WIDTH * 2, Screen::CENTER_Y },
	m_closeFunction{ nullptr }
{

	using namespace DirectX::SimpleMath;
	//��{���ݒ�
	SetPosition(m_position);
	SetSize(Vector2(Screen::WIDTH * 2, Screen::HEIGHT));
	SetColor(Vector4(0, 0, 0, 1));

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
			});
	m_sequence->Pause();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void PlayFade::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//�|�W�V�������Z�b�g
	SetPosition(m_position);
}

/// <summary>
/// �t�F�[�h�X�^�[�g
/// </summary>
/// <param name="function">���s�C�x���g</param>
void PlayFade::Start(std::function<void()> function)
{
	//�t�F�[�h�C����ԂɕύX
	SetState(Fade::State::DoIn);
	//������ݒ�
	m_closeFunction = function;
	//Sequence���J�n
	m_sequence->Play();
}
