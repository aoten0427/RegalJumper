// ================================================================ 
// ファイル名 : PlayCameraReserve.cpp
// 作成者 : 景山碧天
// 説明 :  ゲーム開始時のプレイカメラ状態
// ================================================================
#include"pch.h"
#include"PlayCameraReserve.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Player/Player.h"

//初期移動時間
constexpr float MOVE_TIME = 3.5f;
//カメラ初期位置
constexpr DirectX::SimpleMath::Vector3 START_POS{ 0,800,42 };
//カメラ目的地
constexpr DirectX::SimpleMath::Vector3 DESTINATION{ 0,4,40 };
//目線初期位置
constexpr DirectX::SimpleMath::Vector3 TARGET_START{ 0,-0.5f,-1.0f };
//目線目的地
constexpr DirectX::SimpleMath::Vector3 TARGET_DESTINATION{ 0, -0.0003f, -1 };

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">ステートマシン</param>
/// <param name="camera">カメラ</param>
PlayCameraReserve::PlayCameraReserve(PlayCameraStateMachine* machine, PlayCamera* camera) :PlayCameraState(machine, camera)
,
m_camera{ camera },
m_eyePotision{ START_POS },
m_direction{ TARGET_START }
{
	//Tween作成
	m_eyeTween = m_camera->AddComponent<Tween>(m_camera);
	m_targetTween = m_camera->AddComponent<Tween>(m_camera);
	//視点移動
	m_eyeTween->DoVector3(m_eyePotision, DESTINATION, MOVE_TIME).SetEase(Easing::Ease::OutCirc).SetCompleteFunction([&]() {
		m_camera->GetPlayer()->Entery();
		});
	m_eyeTween->Pause();
	//目標点移動
	m_targetTween->DoVector3(m_direction, TARGET_DESTINATION, MOVE_TIME).SetEase(Easing::Ease::OutQuad).SetDelay(0.5f);
	m_targetTween->Pause();
	//再生判断イベント作成
	m_playbackObserver = m_camera->AddComponent<Observer<Scene::State, Scene::State>>(m_camera);
	m_playbackObserver->RegistrationSubject("SceneStateChange");
	m_playbackObserver->SetFunction(std::bind(&PlayCameraReserve::PlayBack, this, std::placeholders::_1));
}

/// <summary>
/// 事前更新
/// </summary>
void PlayCameraReserve::PreUpdate()
{
	//視点と目標点を設定
	m_camera->SetEyePosition(START_POS);
	m_camera->SetTargetPosition(TARGET_START + START_POS);

}

/// <summary>
/// アップデート　視点、目標点更新
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void PlayCameraReserve::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_camera->SetEyePosition(m_eyePotision);
	m_camera->SetTargetPosition(m_direction + m_eyePotision);
}

/// <summary>
/// 事後更新
/// </summary>
void PlayCameraReserve::PostUpdate()
{

}

/// <summary>
/// 再生判断
/// </summary>
/// <param name="type">変化後のシーンの状態</param>
void PlayCameraReserve::PlayBack(Scene::State type)
{
	//開始状態ならTween再生
	if (type == Scene::State::RESERVE)
	{
		m_eyeTween->Play();
		m_targetTween->Play();
	}
	else if (type == Scene::State::PLAY)
	{
		ChangeState(State::NOMAL);
	}
	//以外なら止める
	else
	{
		m_eyeTween->Pause();
		m_targetTween->Pause();
	}
}
