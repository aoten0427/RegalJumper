// ================================================================ 
// �t�@�C���� : PlayerState.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�̏�Ԃ��Ǘ�
// ================================================================
#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class Player;
class PlayerStateMachine;


class PlayerState :public IState
{
public:
	enum class State
	{
		IDLE,
		WALK,
		SHOT,
		MOVETHREAD,
		DAMAGE,
	};
private:
	//�X�e�[�g�}�V��
	PlayerStateMachine* m_machine;
public:
	//�R���X�g���N�^
	PlayerState(PlayerStateMachine* machine, Player* player);
	//�f�X�g���N�^
	virtual ~PlayerState() = default;
	//��ԕύX
	void ChangeState(State nextstate);
};