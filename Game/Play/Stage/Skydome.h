// ================================================================ 
// ファイル名 : Skydome.h
// 作成者 : 景山碧天
// 説明 :  天球
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Skydome :public Object
{
private:
public:
	//コンストラクタ
	Skydome(Scene* scene);
	//デストラクタ
	~Skydome()override = default;
};