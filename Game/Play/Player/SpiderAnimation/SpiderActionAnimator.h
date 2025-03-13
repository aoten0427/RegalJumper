// ================================================================ 
// ファイル名 : SpiderActionAnimation.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛の空中機動アニメーション
// ================================================================

#pragma once
#include"Base/MyLibraries/Animation/Animator.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAction.h"

class SpiderModels;
class Rigidbody;
class Tween;

class SpiderActionAnimator :public Animator
{
private:
	
private:
	enum class State
	{
		NORMAL,
		ROTATE
	};
private:
	State m_state;
	//モデル
	SpiderModels* m_models;
	//リジッドボディ
	Rigidbody* m_playerRigidbody;
	//変更クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	//回転軸
	DirectX::SimpleMath::Vector3 m_axis;
	//回転量
	float m_radian;
	//基準割合
	float m_resetTime;
	//アクション
	std::vector<std::unique_ptr<SpiderAction>> m_actions;
	//変更用Tween
	Tween* m_tween;
public:
	//コンストラクタ
	SpiderActionAnimator(std::string name, SpiderModels* model);
	~SpiderActionAnimator() override = default;
	//プレイ
	void Play()override;
	//アップデート
	void Update(float deltatime)override;

private:
	//アクションの選択
	DirectX::SimpleMath::Vector3 SelectAction();
	//基準値に戻す
	void ToNormal();
};