// ================================================================ 
// �t�@�C���� : StageCenter
// �쐬�� : �i�R�ɓV
// ���� :  �v���C��ʂɔz�u����I�u�W�F�N�g���Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class StageCenter :public Object
{
private:
public:
	//�R���X�g���N�^
	StageCenter(Scene* scene);
	//�f�X�g���N�^
	~StageCenter()override = default;
private:
	//�f�[�^�ǂݍ���
	void LoadData();
};
