// ================================================================ 
// ファイル名 : SpiderAnimatorCenter.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛のアニメーションを管理
// ================================================================
#include"pch.h"
#include"SpiderAnimatorCenter.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"
#include"Game/Play/Player/SpiderAnimation/SpiderActionAnimator.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="models">蜘蛛モデル</param>
SpiderAnimatorCenter::SpiderAnimatorCenter(SpiderModels* models)
{
	//アニメーター作成
	AddAnimator(std::make_unique<Animator>("PlayerIdle","Resources/JSON/PlayerData/Player_Idle.json"));
	AddAnimator(std::make_unique<Animator>("PlayerWalk","Resources/JSON/PlayerData/Player_Walk.json"));
	AddAnimator(std::make_unique<Animator>("PlayerAir", "Resources/JSON/PlayerData/Player_Air.json"));
	AddAnimator(std::make_unique<SpiderActionAnimator>("PlayerAction", models));
	//アニメーターにオブジェクトを登録
	AddAnimationObject("Main",models);
	auto modelParts = models->GetModelParts();
	for (auto& parts : modelParts)
	{
		AddAnimationObject(parts->GetName(), parts);
	}
	AddAnimationToAnimator();
	//アニメーションロード
	LoadAnimation();

	SetActiveAnimator("PlayerIdle", true);
}
