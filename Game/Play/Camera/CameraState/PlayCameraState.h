// ================================================================ 
// �t�@�C���� : PlayCameraState.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�J�����̏�Ԋ��N���X
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class PlayCamera;
class PlayCameraStateMachine;

class PlayCameraState :public IState
{
public:
	//�X�e�[�g
	enum class State
	{
		RESERVE,
		NOMAL
	};
private:
	PlayCameraStateMachine* m_machine;
public:
	//�R���X�g���N�^
	PlayCameraState(PlayCameraStateMachine* machine, PlayCamera* camera);
	void ChangeState(State state);
};