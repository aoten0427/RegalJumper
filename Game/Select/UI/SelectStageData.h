// ================================================================ 
// ファイル名 : SelectStageData.h
// 作成者 : 景山碧天
// 説明 :  ステージ番号を表示
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Tween;
template<typename...Args>
class Observer;

class SelectStageData :public UserInterface
{
private:
	//大きさ
	DirectX::SimpleMath::Vector2 m_numberSize;
	//ステージ番号
	UserInterface* m_stageNumber[2];
	//大きさ変更Tween
	Tween* m_tween;
	//ステージ変更オブザーバー
	Observer<>* m_observer;
public:
	//コンストラクタ
	SelectStageData(Canvas* canvas);
	//デストラクタ
	~SelectStageData()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//データ更新
	void DataUpdate();
};