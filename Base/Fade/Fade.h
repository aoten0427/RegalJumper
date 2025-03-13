// ================================================================ 
// ファイル名 : Fade.h
// 作成者 : 景山碧天
// 説明 :  フェード基底クラス
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Fade :public UserInterface
{
public:
	//フェード状態
	enum class State
	{
		Out,
		DoIn,
		In,
		DoOut
	};
public:
	//状態セット
	void SetState(const State& state) { m_state = state; }
	//状態取得
	State GetState()const { return m_state; }
	//名前取得
	std::string GetName()const { return m_name; }
private:
	//自身の状態
	State m_state;
	//自身の名前
	std::string m_name;
public:
	Fade(Canvas* canvas, std::string fadeName);
	~Fade();
	//フェード開始
	virtual void Start(std::function<void()> function = nullptr) = 0;
};