// ================================================================ 
// ファイル名 : PlayCameraStateMachine.h
// 作成者 : 景山碧天
// 説明 :  プレイカメラ状態の管理
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Camera/CameraState/PlayCameraState.h"

class PlayCamera;

class PlayCameraStateMachine :public StateMachine<PlayCameraState, PlayCameraState::State>
{
private:
public:
	//コンストラクタ
	PlayCameraStateMachine(PlayCamera* camera);
};