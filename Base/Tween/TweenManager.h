// ================================================================ 
// ファイル名 : TweenManager.h
// 作成者 : 景山碧天
// 説明 :  Tween管理
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"

class Tween;
class Sequence;
class TweenCore;
class Sequence;

class TweenManager:public Singleton<TweenManager>
{
	friend class Singleton<TweenManager>;
private:
	TweenManager();
private:
	//tween本体
	std::vector<std::unique_ptr<TweenCore>> m_tweens;
	//Core破壊フラグ
	bool m_isCoreDestroy;
public:
	~TweenManager();
	//Tweenからの作成依頼
	TweenCore* AddTween(const Tween& tween);
	//Sequenceからの作成依頼
	TweenCore* AddTween(const Sequence& sequence);
	//アップデート
	void Update(float deltatime);
	//コア破壊フラグをオンに
	void CoreDestroyOn() { m_isCoreDestroy = true; }
private:
	//Tween削除
	void RemoveTween();
};