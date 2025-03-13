#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"

class SpiderModelNone :public SpiderModelState
{
private:
public:
	SpiderModelNone(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	~SpiderModelNone()override = default;
	// ���O�X�V����
	void PreUpdate()override {};
	// �X�V����
	void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	// ����X�V����
	void PostUpdate()override {};
	//�`�揈��
	void Render(const Camera& camera)override { UNREFERENCED_PARAMETER(camera); };
};