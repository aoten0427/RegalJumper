// ================================================================ 
// �t�@�C���� : SpiderAnimatorCenter.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̃A�j���[�V�������Ǘ�
// ================================================================

#pragma once
#include"Base/MyLibraries/Animation/AnimatorCenter.h"

class SpiderModels;

class SpiderAnimatorCenter :public AnimatiorCenter
{
private:
public:
	SpiderAnimatorCenter(SpiderModels* models);
	~SpiderAnimatorCenter() = default;
};