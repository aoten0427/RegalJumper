// ================================================================ 
// �t�@�C���� : TitleCanvas
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g���V�[���p�L�����o�X
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

class TitleCanvas :public GameCanvas
{
private:
public:
	//�R���X�g���N�^
	TitleCanvas(Scene* scene);
	//�f�X�g���N�^
	~TitleCanvas() override = default;
};