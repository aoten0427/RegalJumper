// ================================================================ 
// ファイル名 : UIReticle.h
// 作成者 : 景山碧天
// 説明 :  レティクル
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class UIReticle :public UserInterface
{
private:
public:
	//コンストラクタ
	UIReticle(Canvas* canvas);
	//デストラクタ
	~UIReticle()override = default;
private:
	void ChangeColor(bool hit);
};