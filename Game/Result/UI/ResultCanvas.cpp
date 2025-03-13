// ================================================================ 
// ファイル名 : ResultCanvas.cpp
// 作成者 : 景山碧天
// 説明 :  リザルト用キャンバス
// ================================================================

#include"pch.h"
#include"ResultCanvas.h"
#include"Base/Scene/Scene.h"
#include"Game/Result/UI/ResultBG.h"
#include"Game/Result/UI/ResultStageData.h"
#include"Game/Result/UI/ResultTime.h"
#include"Game/Result/UI/ResultScore.h"
#include"Game/Result/UI/ResultOrderTime.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
ResultCanvas::ResultCanvas(Scene* scene):GameCanvas(scene)
{
	scene->AddObject<ResultBG>(this);
	scene->AddObject<ResultStageData>(this);
	scene->AddObject<ResultTime>(this);
	scene->AddObject<ResultScore>(this);
	scene->AddObject<ResultOrderTIme>(this);
}
