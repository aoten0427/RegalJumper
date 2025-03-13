// ================================================================ 
// ファイル名 : SpiderModelState.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛モデルの描画状態
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class SpiderModelStateMachine;
class SpiderModels;

class Camera;

class SpiderModelState:public IState
{
public:
	//描画状態
	enum class RenderType
	{
		NONE,
		ENTRY,
		NORMAL,
		PLAY,
		EXIT
	};
private:
	SpiderModelStateMachine* m_machine;
public:
	//コンストラクタ
	SpiderModelState(SpiderModelStateMachine* machine,SpiderModels* spidermodel);
	//デストラクタ
	virtual ~SpiderModelState() = default;
	//描画
	virtual void Render(const Camera& camera) = 0;
	//状態変化
	void ChangeState(RenderType type);
};