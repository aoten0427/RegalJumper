// ================================================================ 
// ファイル名 : PlayCamera.h
// 作成者 : 景山碧天
// 説明 :  プレイシーンカメラ
// ================================================================

#pragma once
#include"Base/Camera/Camera.h"

class PlayCameraStateMachine;
class Player;
class Segment;

class PlayCamera :public Camera
{
public:
	//プロジェクションmatrix取得
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const override { return m_projection; };
	//ビューmatrix取得
	const DirectX::SimpleMath::Matrix& GetViewMatrix()  const override { return m_view; }
	//始点セット
	void SetEyePosition(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }
	//視点取得
	const DirectX::SimpleMath::Vector3& GetEyePosition()  const override { return m_eye; }
	//ターゲットセット
	void SetTargetPosition(DirectX::SimpleMath::Vector3 target) { m_target = target; }
	//ターゲット取得
	const DirectX::SimpleMath::Vector3& GetTargetPosition()  const override { return m_target; }
	//頭方向取得
	const DirectX::SimpleMath::Vector3& GetUpPosition()  const override { return m_up; }
	void SetRotataionY(float rotation) { m_rotationY = rotation; }
	float GetRotationY()const { return m_rotationY; }
	//プレイヤーセット
	void SetPlayer(Player* player) { m_player = player; }
	//プレイヤー取得
	Player* GetPlayer()const { return m_player; }
private:
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// カメラの頭の方向
	DirectX::SimpleMath::Vector3 m_up;
	//回転軸Y
	float m_rotationY;
	//ステートマシン
	std::unique_ptr<PlayCameraStateMachine> m_machine;
	//判定
	Segment* m_collider;
	//
	Player* m_player;
public:
	//コンストラクタ
	PlayCamera(Scene* scene);
	//ですと楽
	~PlayCamera()override = default;
	//情報更新
	void CalculationView() override;
};