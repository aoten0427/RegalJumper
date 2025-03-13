// ================================================================ 
// ファイル名 : ResultTime.h
// 作成者 : 景山碧天
// 説明 :  リザルトでのタイム表示
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time;
class Tween;

class ResultTime :public UserInterface
{
private:
	//クリア時間
	Time* m_time;
	DirectX::SimpleMath::Vector2 m_timesize;
	Tween* m_timeTween;
	//バー
	UserInterface* m_bar;
	DirectX::SimpleMath::Vector2 m_barsize;
	Tween* m_barTween;
public:
	//コンストラクタ
	ResultTime(Canvas* canvas);
	//デストラクタ
	~ResultTime()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	//スキップ処理
	void Skip();
};