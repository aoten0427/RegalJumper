// ================================================================ 
// �t�@�C���� : PlayCameraStateMachine.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�J������Ԃ̊Ǘ�
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Camera/CameraState/PlayCameraState.h"

class PlayCamera;

class PlayCameraStateMachine :public StateMachine<PlayCameraState, PlayCameraState::State>
{
private:
public:
	//�R���X�g���N�^
	PlayCameraStateMachine(PlayCamera* camera);
};