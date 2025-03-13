// ================================================================ 
// �t�@�C���� : Button.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �{�^�����N���X
// ================================================================

#include"pch.h"
#include"Button.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="filename">�ǂݍ��݉摜</param>
/// <param name="renderorder">�D��x</param>
Button::Button(Canvas* canvas, std::string filename, int renderorder):UserInterface(canvas,filename,renderorder)
	,
	m_function{nullptr}
{
	//�}�E�X�C�x���g���I����
	SetMouseEventFlag(true);
}

/// <summary>
/// �֐����s
/// </summary>
void Button::DoFunction()
{
	if (m_function)m_function();
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">��������</param>
void Button::LeftClickEvent(bool within)
{
	if (!within)return;
	DoFunction();
}
