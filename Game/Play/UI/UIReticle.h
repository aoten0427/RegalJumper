// ================================================================ 
// �t�@�C���� : UIReticle.h
// �쐬�� : �i�R�ɓV
// ���� :  ���e�B�N��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class UIReticle :public UserInterface
{
private:
public:
	//�R���X�g���N�^
	UIReticle(Canvas* canvas);
	//�f�X�g���N�^
	~UIReticle()override = default;
private:
	void ChangeColor(bool hit);
};