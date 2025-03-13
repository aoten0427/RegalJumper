// ================================================================ 
// ファイル名 : SelectCanvas.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーンキャンバス
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

class SelectCanvas :public GameCanvas
{
private:
public:
	//コンストラクタ
	SelectCanvas(Scene* scene);
	//デストラクタ
	~SelectCanvas()override = default;
};