// ================================================================ 
// ファイル名 : SelectScene.cpp
// 作成者 : 景山碧天
// 説明 :  セレクトシーン
// ================================================================
#include"pch.h"
#include"SelectScene.h"
#include"Base/Camera/DebugCamera.h"
#include"Game/GameManager.h"
#include"Game/Select/UI/SelectCanvas.h"
#include"Game/Select/SelectCenter.h"
#include"Game/Select/Object/SelectObjects.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">コモンリソース</param>
SelectScene::SelectScene(CommonResources* resources) :Scene(resources,"Select")
{
	//カメラ生成
	m_camera = AddObject<Camera>(this);
	//キャンバス生成
	m_canvas = AddObject<SelectCanvas>(this);
	//管理者生成
	AddObject<SelectCenter>(this);
	//オブジェクト生成
	AddObject<SelectObjects>(this);

	//カーソルをオンにする
	GameManager::GetInstance()->ViewCursor(true);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void SelectScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

