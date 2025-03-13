// ================================================================ 
// �t�@�C���� : PlayCameraStateMachine.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�J������Ԃ̊Ǘ�
// ================================================================
#include"pch.h"
#include"PlayCameraStateMachine.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Camera/CameraState/PlayCameraNormal.h"
#include"Game/Play/Camera/CameraState/PlayCameraReserve.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera">�v���C�J����</param>
PlayCameraStateMachine::PlayCameraStateMachine(PlayCamera* camera)
{
	//�X�e�[�g����
	AddState(std::make_unique<PlayCameraNormal>(this, camera), PlayCameraState::State::NOMAL);
	AddState(std::make_unique<PlayCameraReserve>(this, camera), PlayCameraState::State::RESERVE);
	
	SetStart(PlayCameraState::State::RESERVE);
}
