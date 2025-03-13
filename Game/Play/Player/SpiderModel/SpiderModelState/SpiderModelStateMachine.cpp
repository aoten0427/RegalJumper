// ================================================================ 
// �t�@�C���� : SpiderModelStateMachine.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w偃��f���̕`���Ԃ̊Ǘ�
// ================================================================
#include"pch.h"
#include"SpiderModelStateMachine.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelNormal.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelEnter.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelExit.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelPlay.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelNone.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="models">�w偃��f��</param>
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
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void SpiderModelStateMachine::Render(const Camera& camera)
{
	if (m_currensState)
	{
		m_currensState->Render(camera);
	}
}

/// <summary>
/// ���݂̕`���Ԃ�ύX
/// </summary>
/// <param name="type">�ω��X�e�[�g</param>
void SpiderModelStateMachine::DerivationChangeState(SpiderModelState::RenderType type)
{
	m_currensState = m_states[type];
}

/// <summary>
/// �`���Ԃ�ǉ�
/// </summary>
/// <param name="state">�ǉ��X�e�[�g</param>
/// <param name="type">�`��^�C�v</param>
void SpiderModelStateMachine::DerivationAddState(SpiderModelState* state, SpiderModelState::RenderType type)
{
	m_states.insert({ type,state });
}


