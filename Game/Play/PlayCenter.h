// ================================================================ 
// ファイル名 : PlayCenter.h
// 作成者 : 景山碧天
// 説明 :  プレイシーンの管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;
template<typename...Args>
class Subject;

class PlayCenter :public Object
{
private:
	//リセット関数呼び出しオブザーバー
	Observer<>* m_resetObserver;
	// リセット関数呼び出しサブジェクト
	Subject<>* m_resetSubject;
	//リザルト画面以降オブザーバー
	Observer<>* m_exitObserver;
public:
	//コンストラクタ
	PlayCenter(Scene* scene);
	//デストラクタ
	~PlayCenter() override = default;
private:
	//プレイシーンリセット処理
	void Reset();
	//リザルトシーン遷移処理
	void ToResult();
};