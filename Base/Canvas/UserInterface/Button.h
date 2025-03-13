// ================================================================ 
// �t�@�C���� : Button.h
// �쐬�� : �i�R�ɓV
// ���� :  �{�^�����N���X
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Button :public UserInterface
{
public:
	//�֐��Z�b�g
	void SetFunction(std::function<void()> function) { m_function = function; }
private:
	//�Ăяo���֐�
	std::function<void()> m_function;
public:
	//�R���X�g���N�^
	Button(Canvas* canvas, std::string filename = "Quad", int renderorder = 0);
	virtual ~Button()override = default;
	//�t�@���N�V�������s
	void DoFunction();
	//���N���b�N�C�x���g
	void LeftClickEvent(bool within)override;
};