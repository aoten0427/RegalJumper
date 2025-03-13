// ================================================================ 
// �t�@�C���� : SpiderModelState.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w偃��f���̕`����
// ================================================================
#include"pch.h"
#include"SpiderModelState.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�w偃��f���X�e�[�g�}�V��</param>
/// <param name="spidermodel">�w偃��f��</param>
SpiderModelState::SpiderModelState(SpiderModelStateMachine* machine, SpiderModels* spidermodel)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(spidermodel);
}

/// <summary>
/// ��ԕύX
/// </summary>
/// <param name="type">�ύX�X�e�[�g</param>
void SpiderModelState::ChangeState(RenderType type)
{
	m_machine->ChangeState(type);
}
