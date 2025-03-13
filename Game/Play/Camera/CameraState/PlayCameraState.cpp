// ================================================================ 
// �t�@�C���� : PlayCameraState.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�J�����̏�Ԋ��N���X
// ================================================================

#include"pch.h"
#include"PlayCameraState.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Camera/CameraState/PlayCameraStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�X�e�[�g�}�V��</param>
/// <param name="camera">�J����</param>
PlayCameraState::PlayCameraState(PlayCameraStateMachine* machine, PlayCamera* camera)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(camera);
}

void PlayCameraState::ChangeState(State state)
{
	m_machine->ChangeState(state);
}
