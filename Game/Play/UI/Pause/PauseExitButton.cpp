// ================================================================ 
// �t�@�C���� : PauseExitButton.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �|�[�Y�ޏo�{�^��
// ================================================================
#include"pch.h"
#include"PauseExitButton.h"
#include"Base/Scene/Scene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
PauseExitButton::PauseExitButton(Canvas* canvas):Button(canvas,"Exit",3)
{
	SetSize(DirectX::SimpleMath::Vector2(50, 50));
	SetPosition(DirectX::SimpleMath::Vector2(870, 570));
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void PauseExitButton::MouseWithinEvent(bool within)
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
void PauseExitButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	//�|�[�Y�����
	if (within)DoFunction();
}
