// ================================================================ 
// ファイル名 : SpiderModelStateMachine.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛モデルの描画状態の管理
// ================================================================
#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"

class SpiderModels;

class SpiderModelStateMachine:public StateMachine<SpiderModelState,SpiderModelState::RenderType>
{
private:
	//更新ステート
	SpiderModelState* m_currensState;
	//登録ステート
	std::unordered_map<SpiderModelState::RenderType, SpiderModelState*> m_states;
public:
	//コンストラクタ
	SpiderModelStateMachine(SpiderModels* models);
	//描画
	void Render(const Camera& camera);
	//更新ステートを設定
	void DerivationChangeState(SpiderModelState::RenderType type)override;
	//ステートを登録
	void DerivationAddState(SpiderModelState* state, SpiderModelState::RenderType type) override;

	
};