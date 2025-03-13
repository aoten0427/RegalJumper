// ================================================================ 
// ファイル名 : SelectBestTime.h
// 作成者 : 景山碧天
// 説明 :  ステージセレクトでのベストタイム
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time;
template<typename...Args>
class Observer;

class SelectBestTime :public UserInterface
{
private:
	//最高記録
	Time* m_bestTime;
	//目標時間
	Time* m_orderTimes[3];
	//最高記録のスコアマーク
	UserInterface* m_scoreMarks[2];
	//ステージ変更オブザーバー
	Observer<>* m_observer;
public:
	//コンストラクタ
	SelectBestTime(Canvas* canvas);
	//デストラクタ
	~SelectBestTime()override = default;
	//データ更新
	void DataUpdate();
private:
	//データ読み込み
	void LoadData();
};