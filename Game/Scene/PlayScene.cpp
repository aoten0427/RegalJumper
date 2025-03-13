#include"pch.h"
#include"PlayScene.h"
#include"Base/CommonResources.h"
#include"Game/GameManager.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/UI/PlayCanvas.h"
#include"Game/Play/PlayCenter.h"
#include"Game/Play/Player/PlayerCenter.h"
#include"Game/Play/Stage/StageCenter.h"
#include"Game/Parameter/ParameterManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">コモンリソース</param>
PlayScene::PlayScene(CommonResources* resources) :Scene(resources,"Play")
{
	ParameterManager::LoadDaata();
	//カメラ生成
	m_camera = AddObject<PlayCamera>(this);
	//キャンバス生成
	m_canvas = AddObject<PlayCanvas>(this);
	//管理者生成
	AddObject<PlayCenter>(this);
	//プレイヤー生成
	AddObject<PlayerCenter>(this);
	//ステージ生成
	AddObject<StageCenter>(this);

	//カーソルをオフにする
	GameManager::GetInstance()->ViewCursor(false);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void PlayScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

