// ================================================================ 
// ファイル名 : SelectUIBase.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーンUIのベース
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class SelectUIBase :public UserInterface
{
private:
public:
	//コンストラクタ
	SelectUIBase(Canvas* canvas);
	//デストラクタ
	~SelectUIBase() override = default;
};