// ================================================================ 
// ファイル名 : PlayCameraStateMachine.cpp
// 作成者 : 景山碧天
// 説明 :  プレイカメラ状態の管理
// ================================================================
#include"pch.h"
#include"PlayCameraStateMachine.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Camera/CameraState/PlayCameraNormal.h"
#include"Game/Play/Camera/CameraState/PlayCameraReserve.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="camera">プレイカメラ</param>
PlayCameraStateMachine::PlayCameraStateMachine(PlayCamera* camera)
{
	//ステート生成
	AddState(std::make_unique<PlayCameraNormal>(this, camera), PlayCameraState::State::NOMAL);
	AddState(std::make_unique<PlayCameraReserve>(this, camera), PlayCameraState::State::RESERVE);
	
	SetStart(PlayCameraState::State::RESERVE);
}
