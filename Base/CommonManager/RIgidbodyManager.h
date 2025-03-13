// ================================================================ 
// ファイル名 : RigidbodyManager.h
// 作成者 : 景山碧天
// 説明 :  RIgidbodyの管理を行う
// ================================================================

#pragma once

class Rigidbody;

class RigidbodyManager
{
private:
	//管理Rigidbody
	std::unordered_set<Rigidbody*> m_rigidbodys;
public:
	//コンストラクタ
	RigidbodyManager();
	//デストラクタ
	~RigidbodyManager() = default;
	//アップデート
	void Update(float deltatime);
	//Rigidbody追加
	void AddRigidbody(Rigidbody* rigidbody);
	//Rigidbody削除
	void RemoveRigidbody(Rigidbody* rigidbody);
};