// ================================================================ 
// ファイル名 :PlayerCenter.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤーに関係するものを管理
// ================================================================
#include"pch.h"
#include"PlayerCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Player/Search.h"
#include"Game/Play/Player/Reticle.h"
#include"Game/Parameter/PlayerParameter.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
PlayerCenter::PlayerCenter(Scene* scene):Object(scene)
{
	//プレイヤー生成
	m_player = scene->AddObject<Player>(scene,this);
	//糸生成
	m_thread = scene->AddObject<Thread>(scene);
	//サーチャー生成
	m_search = scene->AddObject<Search>(scene,m_player);
	m_search->SetRange(PlayerParameter::PARAMETER()->SEARCH_RANGE);
	m_search->SetVision(PlayerParameter::PARAMETER()->SEARCH_VISION);
	//レティクル生成
	scene->AddObject<Reticle>(scene, m_player);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void PlayerCenter::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	Camera* camera = GetScene()->GetCamera();
	//サーチャーの向きを設定
	m_search->SetViewingDirection((camera->GetTargetPosition() - camera->GetEyePosition()));
}

/// <summary>
/// 糸発射
/// </summary>
/// <param name="direction">発射方向</param>
void PlayerCenter::ThreadShot(DirectX::SimpleMath::Vector3 direction)
{
	m_thread->Shot(m_player, m_player->GetTransform()->GetWorldPosition(), direction,m_search->GetTarget());
}
