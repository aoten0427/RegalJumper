// ================================================================ 
// ファイル名 : ThreadHolder.cpp
// 作成者 : 景山碧天
// 説明 :  糸を保持する機能
// ================================================================
#include"pch.h"
#include"ThreadHolder.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object"></param>
ThreadHolder::ThreadHolder(Object* object) :Component(object)
	,
	m_conectFunction{ nullptr },
	m_cutFunction{ nullptr }
{
}

/// <summary>
/// つながった
/// </summary>
void ThreadHolder::Conect()
{
	if (m_conectFunction)m_conectFunction();
}

/// <summary>
/// 切れた
/// </summary>
void ThreadHolder::Cut()
{
	if (m_cutFunction)m_cutFunction();
}
