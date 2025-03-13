// ================================================================ 
// ファイル名 : TitleCanvas
// 作成者 : 景山碧天
// 説明 :  タイトルシーン用キャンバス
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

class TitleCanvas :public GameCanvas
{
private:
public:
	//コンストラクタ
	TitleCanvas(Scene* scene);
	//デストラクタ
	~TitleCanvas() override = default;
};