// ================================================================ 
// ファイル名 : Button.h
// 作成者 : 景山碧天
// 説明 :  ボタン基底クラス
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Button :public UserInterface
{
public:
	//関数セット
	void SetFunction(std::function<void()> function) { m_function = function; }
private:
	//呼び出し関数
	std::function<void()> m_function;
public:
	//コンストラクタ
	Button(Canvas* canvas, std::string filename = "Quad", int renderorder = 0);
	virtual ~Button()override = default;
	//ファンクション実行
	void DoFunction();
	//左クリックイベント
	void LeftClickEvent(bool within)override;
};