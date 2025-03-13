// ================================================================ 
// ファイル名 : SpiderAnimatorCenter.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛のアニメーションを管理
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