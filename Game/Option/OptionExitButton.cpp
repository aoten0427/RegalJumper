// ================================================================ 
// �t�@�C���� : OptionExitButton.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �I�v�V�����ޏo�{�^��
// ================================================================
#include"pch.h"
#include"OptionExitButton.h"
#include"Base/Base.h"
#include"Game/Option/Option.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�L�����o�X</param>
/// <param name="option">�I�v�V����</param>
OptionExit::OptionExit(Canvas* canvas,Option* option):Button(canvas,"Exit",6)
{
	////�e��ݒ�
	GetTransform()->SetParent(option->GetTransform());
	//�T�C�Y�ݒ�
	SetSize(DirectX::SimpleMath::Vector2(60, 60));
	//�ʒu�ݒ�
	SetPosition(DirectX::SimpleMath::Vector2(830, 600));
	
	SetActive(false);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">���g�͈͓̔���</param>
void OptionExit::MouseWithinEvent(bool within)
{
	//�F�ύX
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0.1, 0.75f, 0.93f, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}


