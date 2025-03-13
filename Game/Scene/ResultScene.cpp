// ================================================================ 
// ファイル名 : ResultScene.cpp
// 作成者 : 景山碧天
// 説明 :  リザルトシーン
// ================================================================
#include"pch.h"
#include"ResultScene.h"
#include"Base/Camera/DebugCamera.h"
#include"Game/Result/UI/ResultCanvas.h"
#include"Game/Result/ResultCenter.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">コモンリソース</param>
ResultScene::ResultScene(CommonResources* resources) :Scene(resources,"Result")
{
	//カメラ生成
	m_camera = AddObject<DebugCamera>(this);
	//キャンバス生成
	m_canvas = AddObject<ResultCanvas>(this);
	//管理者生成
	AddObject<ResultCenter>(this);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void ResultScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

