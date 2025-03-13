#include"pch.h"
#include"TitleCanvas.h"
#include"Base/Scene/Scene.h"
#include"Game/Title/UI/TitleBG.h"
#include"Game/Title/UI/PlayButton.h"
#include"Game/Title/UI/OptionButton.h"
#include"Game/Title/UI/QuitButton.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
TitleCanvas::TitleCanvas(Scene* scene):GameCanvas(scene)
{
	//背景作成
	scene->AddObject<TitleBG>(this);
	//プレイボタン作成
	scene->AddObject<PlayButton>(this);
	//オプションボタン作成
	scene->AddObject<OptionButton>(this);
	//終了ボタン作成
	scene->AddObject<QuitButton>(this);
}

