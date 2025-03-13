// ================================================================ 
// ファイル名 : ResultCenter.h
// 作成者 : 景山碧天
// 説明 :  リザルトシーンの管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;
template<typename...Args>
class Subject;

class ResultCenter :public Object
{
private:
	//開始オブザーバー
	Observer<>* m_beginObserver;
	//スキップ呼び出しサブジェクト
	Subject<>* m_skipSubject;
public:
	//コンストラクタ
	ResultCenter(Scene* scene);
	//デストラクタ
	~ResultCenter()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
};