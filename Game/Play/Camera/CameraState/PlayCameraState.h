// ================================================================ 
// ファイル名 : PlayCameraState.h
// 作成者 : 景山碧天
// 説明 :  プレイカメラの状態基底クラス
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class PlayCamera;
class PlayCameraStateMachine;

class PlayCameraState :public IState
{
public:
	//ステート
	enum class State
	{
		RESERVE,
		NOMAL
	};
private:
	PlayCameraStateMachine* m_machine;
public:
	//コンストラクタ
	PlayCameraState(PlayCameraStateMachine* machine, PlayCamera* camera);
	void ChangeState(State state);
};