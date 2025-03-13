// ================================================================ 
// ファイル名 : PlayCameranNormal.h
// 作成者 : 景山碧天
// 説明 :  ゲームプレイ時のプレイカメラ状態
// ================================================================
#pragma once
#include"Game/Play/Camera/CameraState/PlayCameraState.h"


class Segment;
template<typename...Args>
class Observer;

class PlayCameraNormal :public PlayCameraState
{
private:
	//プレイカメラ
	PlayCamera* m_camera;
	//判定
	Segment* m_collider;
	//プレイヤーからの距離
	float m_length;
	//回転量
	float m_rotationY;
	float m_rotationX;
	//めり込み量
	DirectX::SimpleMath::Vector3 m_pushback;
	//
	Observer<>* m_resetObserver;
public:
	//コンストラクタ
	PlayCameraNormal(PlayCameraStateMachine* machine, PlayCamera* camera);

	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
private:
	//マウスコントロール
	void MouseControl();
	//リセット
	void Reset();
};