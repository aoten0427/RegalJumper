// ================================================================ 
// ファイル名 : Cursor.h
// 作成者 : 景山碧天
// 説明 :  カーソルを表示
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Cursor :public UserInterface
{
private:
public:
	//コンストラクタ
	Cursor(Canvas* canvas);
	//デストラクタ
	~Cursor() override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	//エフェクト生成
	void MakeEffect();
};