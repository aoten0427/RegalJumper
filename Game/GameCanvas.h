// ================================================================ 
// �t�@�C���� : GameCanvas.h
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���Ŏg���L�����o�X��b
// ================================================================

#pragma once
#include"Base/Canvas/Canvas.h"

class GameCanvas :public Canvas
{
private:
public:
	//�R���X�g���N�^
	GameCanvas(Scene* scene);
	//�f�X�g���N�^
	~GameCanvas()override = default;
};