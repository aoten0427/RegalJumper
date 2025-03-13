// ================================================================ 
// �t�@�C���� : SpiderModelStateMachine.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偃��f���̕`���Ԃ̊Ǘ�
// ================================================================
#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"

class SpiderModels;

class SpiderModelStateMachine:public StateMachine<SpiderModelState,SpiderModelState::RenderType>
{
private:
	//�X�V�X�e�[�g
	SpiderModelState* m_currensState;
	//�o�^�X�e�[�g
	std::unordered_map<SpiderModelState::RenderType, SpiderModelState*> m_states;
public:
	//�R���X�g���N�^
	SpiderModelStateMachine(SpiderModels* models);
	//�`��
	void Render(const Camera& camera);
	//�X�V�X�e�[�g��ݒ�
	void DerivationChangeState(SpiderModelState::RenderType type)override;
	//�X�e�[�g��o�^
	void DerivationAddState(SpiderModelState* state, SpiderModelState::RenderType type) override;

	
};