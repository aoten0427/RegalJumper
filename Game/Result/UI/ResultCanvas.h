// ================================================================ 
// ファイル名 : ResultCanvas.h
// 作成者 : 景山碧天
// 説明 :  リザルト用キャンバス
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

class ResultCanvas :public GameCanvas
{
private:
public:
	ResultCanvas(Scene* scene);
	~ResultCanvas()override = default;
};