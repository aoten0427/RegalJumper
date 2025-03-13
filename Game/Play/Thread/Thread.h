// ================================================================ 
// ファイル名 : Thread.h
// 作成者 : 景山碧天
// 説明 :  糸
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class ThreadStateMachine;
class RopeSolver;
class ThreadParticle;
class ThreadHolder;
class Target;

class Thread :public Object
{
public:
	//糸を飛ばす際のデータ
	struct  ThreadData
	{
		Object* m_holder;//所属者             
		ThreadHolder* m_threadHolder;//ホルダー機能
		DirectX::SimpleMath::Vector3 m_startPosition;//発射位置
		DirectX::SimpleMath::Vector3 m_direction;//発射方向
		Target* m_target;//ターゲット

		void DataSet(Object* holder, DirectX::SimpleMath::Vector3 strpos, DirectX::SimpleMath::Vector3 dire)
		{
			m_holder = holder;
			m_startPosition = strpos;
			m_direction = dire;
			m_target = nullptr;
		}
	};
public:
	//ステートマシンを渡す
	ThreadStateMachine* GetStateMachine() { return m_machine.get(); }
	//パーティクルを渡す
	std::vector<ThreadParticle*> GetThreadParticles() { return m_threadparticles; }
	//パーティクルをセット
	void SetThreadParticle(std::vector<ThreadParticle*> threadparticle) { m_threadparticles = threadparticle; }
	//ロープソルバーを渡す
	RopeSolver* GetRopeSolver() { return m_ropeSolver; }
	//糸データを渡す
	ThreadData& GetData() { return m_data; }
	//長さをセットする
	void SetRopeDistance(float distance) { m_ropeDistance = distance; }
private:
	//ステートマシン
	std::unique_ptr<ThreadStateMachine> m_machine;
	//糸のまとまり
	RopeSolver* m_ropeSolver;
	//糸を構成する粒子
	std::vector<ThreadParticle*> m_threadparticles;
	//自身のデータ
	ThreadData m_data;
	//長さ
	float m_ropeDistance;
public:
	//コンストラクタ
	Thread(Scene* scene);
	//デストラクタ
	~Thread()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//発射
	void Shot(Object* holder, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction, Target* target);
	//データクリア
	void Clear();
};
