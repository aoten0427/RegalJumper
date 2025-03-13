// ================================================================ 
// ファイル名 : ResultScore.h
// 作成者 : 景山碧天
// 説明 :  リザルトのスコア表示
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Tween;

class ResultScore :public UserInterface
{
private:
	//スコア枠
	UserInterface* m_mark;
	DirectX::SimpleMath::Vector2 m_markSize;
	Tween* m_markTween;
	//スコア
	UserInterface* m_score;
	DirectX::SimpleMath::Vector2 m_scoreSize;
	Tween* m_scoreTween;
	//表示カウントタイマー
	float m_timer;
public:
	//コンストラクタ
	ResultScore(Canvas* canvas);
	//デストラクタ
	~ResultScore() override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	//データ読み込み
	void LoadJSON();
	//データ書き込み
	void WriteJSON();
	//Tweenスキップ処理
	void Skip();
};