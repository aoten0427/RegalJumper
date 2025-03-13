// ================================================================ 
// �t�@�C���� : PlayerState.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�̏�Ԃ��Ǘ�
// ================================================================
#include"pch.h"
#include"PlayerIdle.h"
#include"Game/Play/Player/PlayerState/PlayerStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�v���C���[�X�e�[�g�}�V��</param>
/// <param name="player">�v���C���[</param>
PlayerState::PlayerState(PlayerStateMachine* machine, Player* player)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(player);
}

/// <summary>
/// ��ԕύX
/// </summary>
/// <param name="nextstate">���̃X�e�[�g</param>
void PlayerState::ChangeState(State nextstate)
{
	//�X�e�[�g�}�V���ɏ�ԕύX�w��
	m_machine->ChangeState(nextstate);
}
