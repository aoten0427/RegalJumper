// ================================================================ 
// ファイル名 : Goal.h
// 作成者 : 景山碧天
// 説明 :  ゴール
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Goal :public Object
{
private:
	//タグ取得
	ObjectTag GetTag() override { return ObjectTag::Goal; };
public:
	//コンストラクタ
	Goal(Scene* scene);
	//デストラクタ
	~Goal()override = default;
};