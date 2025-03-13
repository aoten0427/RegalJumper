// ================================================================ 
// ファイル名 : ThreadHolder.h
// 作成者 : 景山碧天
// 説明 :  糸を保持する機能
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class ThreadHolder :public Component
{
public:
	//接続時呼び出し関数セット
	void SetConect(std::function<void()> function) { m_conectFunction = function; }
	//切れた際に呼び出し関数セット
	void SetCut(std::function<void()> function) { m_cutFunction = function; }
private:
	//つながった際に呼び出し関数
	std::function<void()> m_conectFunction;
	//切れた際に呼び出す関数
	std::function<void()> m_cutFunction;
public:
	//コンストラクタ
	ThreadHolder(Object* object);
	//デストラクタ
	~ThreadHolder()override = default;
	//つながった
	void Conect();
	//切れた
	void Cut();
};
