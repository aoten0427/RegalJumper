// ================================================================ 
// �t�@�C���� : SelectUIBase.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[��UI�̃x�[�X
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class SelectUIBase :public UserInterface
{
private:
public:
	//�R���X�g���N�^
	SelectUIBase(Canvas* canvas);
	//�f�X�g���N�^
	~SelectUIBase() override = default;
};