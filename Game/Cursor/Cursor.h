// ================================================================ 
// �t�@�C���� : Cursor.h
// �쐬�� : �i�R�ɓV
// ���� :  �J�[�\����\��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Cursor :public UserInterface
{
private:
public:
	//�R���X�g���N�^
	Cursor(Canvas* canvas);
	//�f�X�g���N�^
	~Cursor() override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	//�G�t�F�N�g����
	void MakeEffect();
};