// ================================================================ 
// ファイル名 : PlayCamera.cpp
// 作成者 : 景山碧天
// 説明 :  プレイシーンカメラ
// ================================================================
#include"pch.h"
#include"PlayCamera.h"
#include"Base/Screen.h"
#include"Base/Component/Collider/Collider.h"
#include"Game/Play/Camera/CameraState/PlayCameraStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
PlayCamera::PlayCamera(Scene* scene):Camera(scene)
	,
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{},
	m_rotationY{},
	m_machine{},
	m_collider{nullptr},
	m_player{nullptr}
{
	using namespace DirectX::SimpleMath;

	//射影行列を計算
	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.005f, 4500.0f
	);
	//判定作成
	AddComponent<Segment>(this, CollisionType::TRIGGER,nullptr,false);
	//ステートマシン作成
	m_machine = std::make_unique<PlayCameraStateMachine>(this);

	m_up = Vector3::UnitY;
}

/// <summary>
/// 情報更新
/// </summary>
void PlayCamera::CalculationView()
{
	//ステートマシン更新
	m_machine->Update(0);
	//ビュー行列作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}


