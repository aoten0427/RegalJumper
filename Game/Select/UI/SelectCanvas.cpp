// ================================================================ 
// ファイル名 : SelectCanvas.cpp
// 作成者 : 景山碧天
// 説明 :  セレクトシーンキャンバス
// ================================================================
#include"pch.h"
#include"SelectCanvas.h"
#include"Base/Scene/Scene.h"
#include"Game/Select/UI/SelectUIBase.h"
#include"Game/Select/UI/SelectStageData.h"
#include"Game/Select/UI/SelectArrow.h"
#include"Game/Select/UI/SelectBestTime.h"
#include"Game/Select/UI/SelectExitButton.h"
#include"Game/Select/UI/SelectPlayButton.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
SelectCanvas::SelectCanvas(Scene* scene):GameCanvas(scene)
{
	scene->AddObject<SelectUIBase>(this);
	scene->AddObject<SelectBestTime>(this);
	scene->AddObject<SelectArrow>(this);
	scene->AddObject<SelectArrow>(this, true);
	scene->AddObject<SelectStageData>(this);
	scene->AddObject<SelectExitButton>(this);
	scene->AddObject<SelectPlayButton>(this);
}
