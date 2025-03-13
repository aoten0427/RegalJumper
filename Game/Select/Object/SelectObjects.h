// ================================================================ 
// ファイル名 : SelectObjects.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーンでのオブジェクト
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;
class SpiderModels;

class SelectObjects :public Object
{
private:
	//蜘蛛モデル
	SpiderModels* m_model;
	//プレイシーン移行オブザーバー
	Observer<>* m_toPlayObserver;
public:
	//コンストラクタ
	SelectObjects(Scene* scene);
	//デストラクタ
	~SelectObjects()override = default;
private:
	//プレイシーン遷移処理
	void ToPlay();
};