// ================================================================ 
// ファイル名 : GameCanvas.h
// 作成者 : 景山碧天
// 説明 :  ゲームで使うキャンバス基礎
// ================================================================

#pragma once
#include"Base/Canvas/Canvas.h"

class GameCanvas :public Canvas
{
private:
public:
	//コンストラクタ
	GameCanvas(Scene* scene);
	//デストラクタ
	~GameCanvas()override = default;
};