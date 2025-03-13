// ================================================================ 
// ファイル名 : GameCanvas.cpp
// 作成者 : 景山碧天
// 説明 :  ゲームで使うキャンバス基礎
// ================================================================

#include"pch.h"
#include"GameCanvas.h"
#include"Base/Object/UnbreakableManager.h"
#include"Game/Title/UI/GameFade.h"
#include"Game/Option/Option.h"
#include"Game/Cursor/Cursor.h"
#include"Game/GameSound.h"
#include"Game/Play/UI/PlayFade.h"

/// <summary>
/// コンストラクタ 各非破壊オブジェクトの作成
/// </summary>
/// <param name="scene">所属シーン</param>
GameCanvas::GameCanvas(Scene* scene) :Canvas(scene)
{
	//フェード作成
	UnbreakableManager::GetInstance()->AddObject<GameFade>("NormalFade", this);
	UnbreakableManager::GetInstance()->AddObject<PlayFade>("PlayFade", this);
	//オプション作成
	UnbreakableManager::GetInstance()->AddObject<Option>("Option", this);
	//カーソル作成
	UnbreakableManager::GetInstance()->AddObject<Cursor>("Cursor", this);
	//サウンド作成
	UnbreakableManager::GetInstance()->AddObject<GameSound>("GameSound", scene);
}
