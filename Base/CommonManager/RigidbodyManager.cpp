// ================================================================ 
// ファイル名 : RigidbodyManager.cpp
// 作成者 : 景山碧天
// 説明 :  RIgidbodyの管理を行う
// ================================================================
#include"pch.h"
#include "RIgidbodyManager.h"
#include"Base/Component/Rigidbody/Rigidbody.h"

/// <summary>
/// コンストラクタ
/// </summary>
RigidbodyManager::RigidbodyManager()
{

}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void RigidbodyManager::Update(float deltatime)
{
	for (auto rigidbody : m_rigidbodys)
	{
		if (!rigidbody->GetActive())continue;
		rigidbody->Compute(deltatime);
	}
}

/// <summary>
/// Rigidbody追加
/// </summary>
/// <param name="rigidbody">追加Rigidbody</param>
void RigidbodyManager::AddRigidbody(Rigidbody* rigidbody)
{
	m_rigidbodys.insert(rigidbody);
}

/// <summary>
/// Rigidbody削除
/// </summary>
/// <param name="rigidbody">削除Rigidbody</param>
void RigidbodyManager::RemoveRigidbody(Rigidbody* rigidbody)
{
	m_rigidbodys.erase(rigidbody);
}
