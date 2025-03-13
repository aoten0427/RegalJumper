// ================================================================ 
// ファイル名 : SpiderModelStateMachine.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛モデルの描画状態の管理
// ================================================================
#include"pch.h"
#include"SpiderModelStateMachine.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelNormal.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelEnter.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelExit.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelPlay.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelNone.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="models">蜘蛛モデル</param>
SpiderModelStateMachine::SpiderModelStateMachine(SpiderModels* models)
	:
	m_currensState{nullptr},
	m_states{}
{
	AddState(std::make_unique<SpiderModelNormal>(this, models), SpiderModelState::RenderType::NORMAL);
	AddState(std::make_unique<SpiderModelEnter>(this, models), SpiderModelState::RenderType::ENTRY);
	AddState(std::make_unique<SpiderModelExit>(this, models), SpiderModelState::RenderType::EXIT);
	AddState(std::make_unique<SpiderModelPlay>(this, models), SpiderModelState::RenderType::PLAY);
	AddState(std::make_unique<SpiderModelNone>(this, models), SpiderModelState::RenderType::NONE);

	SetStart(SpiderModelState::RenderType::NORMAL);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void SpiderModelStateMachine::Render(const Camera& camera)
{
	if (m_currensState)
	{
		m_currensState->Render(camera);
	}
}

/// <summary>
/// 現在の描画状態を変更
/// </summary>
/// <param name="type">変化ステート</param>
void SpiderModelStateMachine::DerivationChangeState(SpiderModelState::RenderType type)
{
	m_currensState = m_states[type];
}

/// <summary>
/// 描画状態を追加
/// </summary>
/// <param name="state">追加ステート</param>
/// <param name="type">描画タイプ</param>
void SpiderModelStateMachine::DerivationAddState(SpiderModelState* state, SpiderModelState::RenderType type)
{
	m_states.insert({ type,state });
}


