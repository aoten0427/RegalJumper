// ================================================================ 
// ファイル名 : TitleScene.cpp
// 作成者 : 景山碧天
// 説明 :  タイトルシーン
// ================================================================
#include"pch.h"
#include"TitleScene.h"
#include"Base/CommonResources.h"
#include"Base/Camera/DebugCamera.h"
#include"Game/Title/UI/TitleCanvas.h"
#include"Game/Title/TitleCenter.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">コモンリソース</param>
TitleScene::TitleScene(CommonResources* resources):Scene(resources,"Title")
{
	//カメラ生成
	m_camera = AddObject<DebugCamera>(this);
	//キャンバス生成
	m_canvas = AddObject<TitleCanvas>(this);
	//管理者生成
	AddObject<TitleCenter>(this);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void TitleScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}


