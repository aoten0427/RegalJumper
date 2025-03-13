// ================================================================ 
// ファイル名 : SelectCenter.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーンを管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;

class SelectCenter :public Object
{
private:
	//開始オブザーバー
	Observer<>* m_begin;
	//終了オブザーバー
	Observer<>* m_finish;
public:
	//コンストラクタ
	SelectCenter(Scene* scene);
	//デストラクタ
	~SelectCenter()override = default;
};
