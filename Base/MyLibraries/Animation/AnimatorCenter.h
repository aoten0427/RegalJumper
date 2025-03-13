// ================================================================ 
// ファイル名 : AnimatorCcenter.h
// 作成者 : 景山碧天
// 説明 :  同一のオブジェクトを動かすアニメーターの管理を行う
// ================================================================

#pragma once
#include"Base/MyLibraries/Animation/Animator.h"
class Object;
class Animator;

class AnimatiorCenter
{
private:
	std::unordered_map<std::string, Animator*> m_activeAnimator;
	//動作アニメーター
	/*std::pair<std::string,Animator*> m_currentAnimator;*/
	//登録アニメーター
	std::unordered_map<std::string, std::unique_ptr<Animator>> m_animators;
	//アニメーションオブジェクト
	std::unordered_map<std::string, Object*> m_animationObjects;
	//
	std::pair<std::string,Animator*> m_singleAnimator;
	//
	std::unordered_set<std::string> m_removeAnimator;
public:
	AnimatiorCenter();
	~AnimatiorCenter() = default;
	//アップデート
	void Update(float deltatime);

	//アニメーターのアクティブを設定
	void SetActiveAnimator(std::string name, bool active);
	//アニメーター追加
	void AddAnimator(std::unique_ptr<Animator> animator);
	//オブジェクト追加
	void AddAnimationObject(std::string name, Object* object);
	//各アニメーターにアニメーション追加
	void AddAnimationToAnimator();
	//各アニメーターにファイルのロード指示
	void LoadAnimation();
};