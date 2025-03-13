#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"

class SpiderModelNone :public SpiderModelState
{
private:
public:
	SpiderModelNone(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	~SpiderModelNone()override = default;
	// 事前更新する
	void PreUpdate()override {};
	// 更新する
	void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	// 事後更新する
	void PostUpdate()override {};
	//描画処理
	void Render(const Camera& camera)override { UNREFERENCED_PARAMETER(camera); };
};