// ================================================================ 
// �t�@�C���� : SelectCanvas.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[���L�����o�X
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

class SelectCanvas :public GameCanvas
{
private:
public:
	//�R���X�g���N�^
	SelectCanvas(Scene* scene);
	//�f�X�g���N�^
	~SelectCanvas()override = default;
};