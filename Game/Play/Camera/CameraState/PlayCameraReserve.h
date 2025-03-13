// ================================================================ 
// ファイル名 : PlayCameraReserve.h
// 作成者 : 景山碧天
// 説明 :  ゲーム開始時のプレイカメラ状態
// ================================================================

#pragma once
#include"Game/Play/Camera/CameraState/PlayCameraState.h"
#include"Base/Scene/Scene.h"

class Tween;
template<typename...Args>
class Observer;



class PlayCameraReserve :public PlayCameraState
{
private:
	//プレイカメラ
	PlayCamera* m_camera;
	//視点
	DirectX::SimpleMath::Vector3 m_eyePotision;
	//初期視線方向
	DirectX::SimpleMath::Vector3 m_direction;
	//移動用Tween
	Tween* m_eyeTween;
	Tween* m_targetTween;
	//Tween再生停止オブザーバー
	Observer<Scene::State, Scene::State>* m_playbackObserver;
public:
	//コンストラクタ
	PlayCameraReserve(PlayCameraStateMachine* machine, PlayCamera* camera);
	//デストラクタ
	~PlayCameraReserve()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
private:
	//再生判断
	void PlayBack(Scene::State type);
};