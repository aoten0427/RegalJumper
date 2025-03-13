// ================================================================ 
// ファイル名 : SpiderModelState.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛モデルの描画状態
// ================================================================
#include"pch.h"
#include"SpiderModelState.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">蜘蛛モデルステートマシン</param>
/// <param name="spidermodel">蜘蛛モデル</param>
SpiderModelState::SpiderModelState(SpiderModelStateMachine* machine, SpiderModels* spidermodel)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(spidermodel);
}

/// <summary>
/// 状態変更
/// </summary>
/// <param name="type">変更ステート</param>
void SpiderModelState::ChangeState(RenderType type)
{
	m_machine->ChangeState(type);
}
