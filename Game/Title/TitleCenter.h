// ================================================================ 
// ファイル名 :TitleCenter 
// 作成者 : 景山碧天
// 説明 :  タイトルシーンを管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;

class TitleCenter :public Object
{
private:
	//開始オブザーバー
	Observer<>* m_begin;
public:
	//コンストラクタ
	TitleCenter(Scene* scene);
	//デストラクタ
	~TitleCenter()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
};
