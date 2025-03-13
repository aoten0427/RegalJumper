// ================================================================ 
// ファイル名 : ResultOrderTime.h
// 作成者 : 景山碧天
// 説明 :  目標時間の表示
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time;
class Tween;

class ResultOrderTIme :public UserInterface
{
private:
	//各スコア表示UI
	UserInterface* m_score[3];
	Time* m_orderTimes[3];
	//アルファ値変化用Tween
	Tween* m_tween;
	//アルファ値
	float m_alpha;
	//
	UserInterface* m_mouse;
public:
	//コンストラクタ
	ResultOrderTIme(Canvas* canvas);
	//デストラクタ
	~ResultOrderTIme()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	//データ読み込み
	void LoadData();
	//Tweenスキップ処理
	void Skip();
};