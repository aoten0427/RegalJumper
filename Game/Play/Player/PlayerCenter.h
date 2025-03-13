// ================================================================ 
// ファイル名 :PlayerCenter.h 
// 作成者 : 景山碧天
// 説明 :  プレイヤーに関係するものを管理
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Player;
class Thread;
class Target;
class Search;

class PlayerCenter:public Object
{
private:
	//プレイヤー
	Player* m_player;
	//糸
	Thread* m_thread;
	//サーチャー
	Search* m_search;
public:
	//コンストラクタ
	PlayerCenter(Scene* scene);
	//デストラクタ
	~PlayerCenter()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//糸発射
	void ThreadShot(DirectX::SimpleMath::Vector3 direction);
};
