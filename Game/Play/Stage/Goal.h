// ================================================================ 
// �t�@�C���� : Goal.h
// �쐬�� : �i�R�ɓV
// ���� :  �S�[��
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Goal :public Object
{
private:
	//�^�O�擾
	ObjectTag GetTag() override { return ObjectTag::Goal; };
public:
	//�R���X�g���N�^
	Goal(Scene* scene);
	//�f�X�g���N�^
	~Goal()override = default;
};