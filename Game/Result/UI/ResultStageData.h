// ================================================================ 
// �t�@�C���� : ResultStageData.h
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�ł̃X�e�[�W���\��
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class ResultStageData :public UserInterface
{
private:
public:
	//�R���X�g���N�^
	ResultStageData(Canvas* canvas);
	//�f�X�g���N�^
	~ResultStageData() override = default;
};