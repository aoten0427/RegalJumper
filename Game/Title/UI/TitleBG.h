// ================================================================ 
// ファイル名 : TitleBG.h
// 作成者 : 景山碧天
// 説明 :  タイトルの背景、ロゴ
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class TitleBG :public UserInterface
{
private:
	//ロゴ
	UserInterface* m_logo;
	//タイマー
	float m_timer;
public:
	//コンストラクタ
	TitleBG(Canvas* canvas);
	//デストラクタ
	~TitleBG() override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
};