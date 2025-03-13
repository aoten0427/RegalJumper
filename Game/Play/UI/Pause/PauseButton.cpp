// ================================================================ 
// �t�@�C���� : PauseButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �|�[�Y�ň����{�^��
// ================================================================
#include"pch.h"
#include"PauseButton.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"

constexpr DirectX::SimpleMath::Vector2 BUTTON_SIZE = DirectX::SimpleMath::Vector2(400, 80);
constexpr int BEGIN = 240;
constexpr int HEIGHT = 100;//����
constexpr int RESTART_Y = 240;//���X�^�[�g�ʒu
constexpr int RESTART_WIDTH = 400;//���X�^�[�g��
constexpr int STAGE_SELECT_Y = 340;//�X�e�[�W�Z���N�g�ʒu
constexpr int STAGE_SELECT_WIDTH = 400;//�X�e�[�W�Z���N�g��
constexpr int OPTION_Y = 440;//�I�v�V�����ʒu
constexpr int OPTION_WIDTH = 400;//�I�v�V������

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="type">�{�^���̎��</param>
PauseButton::PauseButton(Canvas* canvas, TYPE type):Button(canvas)
{
	SetRenderOrder(3);
	SetData(type);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void PauseButton::MouseWithinEvent(bool within)
{
	//�F�ύX
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0, 0.87f, 0.82f, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void PauseButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	if (within)DoFunction();
}

/// <summary>
/// �I�����ɂ���ăf�[�^��ݒ�
/// </summary>
/// <param name="type"></param>
void PauseButton::SetData(TYPE type)
{
	//�摜�C�ʒu�A�傫����ݒ�
	DirectX::SimpleMath::Vector2 position(Screen::CENTER_X, 0);
	DirectX::SimpleMath::Vector2 size(BUTTON_SIZE);
	switch (type)
	{
	case PauseButton::TYPE::RESTART:
		SetTexture("ReStartButton");
		position.y = BEGIN;
		break;
	case PauseButton::TYPE::STAGESELECT:
		SetTexture("StageSelectButton");
		position.y = BEGIN + HEIGHT;
		break;
	case PauseButton::TYPE::OPTION:
		SetTexture("OptionButton");
		position.y = BEGIN + HEIGHT * 2;
		break;
	case PauseButton::TYPE::QUIT:
		SetTexture("QuitP");
		position.y = BEGIN + HEIGHT * 3;
	default:
		break;
	}
	SetPosition(position);
	SetSize(size);
}
