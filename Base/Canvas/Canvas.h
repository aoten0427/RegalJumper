// ================================================================ 
// ファイル名 : Canvas.h
// 作成者 : 景山碧天
// 説明 :  キャンバス基底クラス
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Canvas : public Object
{
private:
public:
	Canvas(Scene* scene);
	~Canvas() = default;
};