// ================================================================ 
// ファイル名 : PauseButton.h
// 作成者 : 景山碧天
// 説明 :  ポーズで扱うボタン
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class PauseButton :public Button
{
public:
	//選択タイプ
	enum class TYPE
	{
		RESTART,
		STAGESELECT,
		OPTION,
		QUIT
	};
private:
public:
	//コンストラクタ
	PauseButton(Canvas* canvas,TYPE type);
	//デストラクタ
	~PauseButton()override = default;

	//マウス感知イベント
	void MouseWithinEvent(bool within) override;
	//左クリックイベント
	void LeftClickEvent(bool within) override;
private:
	//データセット
	void SetData(TYPE type);
};