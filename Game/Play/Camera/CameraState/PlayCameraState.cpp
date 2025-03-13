// ================================================================ 
// ファイル名 : PlayCameraState.h
// 作成者 : 景山碧天
// 説明 :  プレイカメラの状態基底クラス
// ================================================================

#include"pch.h"
#include"PlayCameraState.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Camera/CameraState/PlayCameraStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">ステートマシン</param>
/// <param name="camera">カメラ</param>
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
