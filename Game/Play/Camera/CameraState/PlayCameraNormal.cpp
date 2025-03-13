// ================================================================ 
// ファイル名 : PlayCameranNormal.cpp
// 作成者 : 景山碧天
// 説明 :  ゲームプレイ時のプレイカメラ状態
// ================================================================
#include"pch.h"
#include"PlayCameraNormal.h"
#include"Base/Base.h"
#include"Base/Event/Observer.h"
#include"Base/CommonManager/CollisonManager.h"
#include"Game/GameManager.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Player/Player.h"

//プレイヤーとの距離
constexpr float CAMERA_LENTH = 40.0f;
//カメラ位置の移動速度
constexpr float CAMERA_SPEED = 0.6f;
//マウス固定値
constexpr int MOUSE_POSITION = 400;
//カメラ回転最大値
constexpr float CAMERA_ROTETO_MAX = 89.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">ステートマシン</param>
/// <param name="camera">カメラ</param>
PlayCameraNormal::PlayCameraNormal(PlayCameraStateMachine* machine, PlayCamera* camera) :PlayCameraState(machine, camera)
,
m_camera{ camera },
m_length{ CAMERA_LENTH },
m_rotationX{ 0 },
m_rotationY{ 0 }
{
	using namespace DirectX::SimpleMath;
	//視点、目標点のセット
	m_camera->SetEyePosition(Vector3(0, 5, 5));
	m_camera->SetTargetPosition(Vector3::Zero);
	//コライダー生成
	m_collider = m_camera->GetComponent<Segment>();
	//オブザーバー
	m_resetObserver = m_camera->AddComponent<Observer<>>(m_camera);
	m_resetObserver->SetFunction([&]() {Reset(); });
	m_resetObserver->RegistrationSubject("PlayReset");
}

/// <summary>
/// 事前更新
/// </summary>
void PlayCameraNormal::PreUpdate()
{
	SetCursorPos(MOUSE_POSITION, MOUSE_POSITION);
	Update(0.0f);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void PlayCameraNormal::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	if (m_camera->GetScene()->GetState() != Scene::State::PLAY)return;

	//固定距離より短ければ伸ばす
	if (m_length < CAMERA_LENTH)
	{
		m_length += CAMERA_SPEED;
	}
	//プレイヤーの少し上にターゲットをセット
	Vector3 target = m_camera->GetPlayer()->GetTransform()->GetWorldPosition();
	target += Vector3(0, 2.0f, 0);
	//マウス操作
	MouseControl();
	//可動域制限
	if (m_rotationX >= CAMERA_ROTETO_MAX)m_rotationX = CAMERA_ROTETO_MAX;
	if (m_rotationX <= -CAMERA_ROTETO_MAX)m_rotationX = -CAMERA_ROTETO_MAX;
	//Y軸の回転を計算
	Quaternion rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(m_rotationY));
	//回転方向に合わせて始点を移動
	Vector3 eye = Vector3::UnitZ * m_length;
	eye = DirectX::XMVector3Rotate(eye, rotate);
	//X軸の回転を計算
	Vector3 axisX = DirectX::XMVector3Rotate(Vector3::UnitX, rotate);
	rotate = Quaternion::CreateFromAxisAngle(axisX, DirectX::XMConvertToRadians(m_rotationX));
	//始点を回転
	eye = DirectX::XMVector3Rotate(eye, rotate);
	//ターゲット方向を見る
	eye += target;

	//コライダーの始点と終点を設定
	m_camera->GetTransform()->SetPosition(eye);
	m_collider->SetStartPos(Vector3::Zero);
	m_collider->SetEndPos(target - m_camera->GetTransform()->GetPosition());



	//めり込みようの当たり判定
	m_camera->GetScene()->GetCollisionManager()->RayCollision(m_collider, CollisionType::COLLISION, &m_pushback);
	if (m_pushback.Length() != 0)
	{
		//ステージに合わせて押し戻す
		m_length -= m_pushback.Length();
		eye -= (m_pushback * 1.05f);
		m_pushback = Vector3::Zero;
	}

	m_camera->SetEyePosition(eye);
	m_camera->SetTargetPosition(target);
}

/// <summary>
/// 事後更新
/// </summary>
void PlayCameraNormal::PostUpdate()
{
}

/// <summary>
/// マウス操作
/// </summary>
void PlayCameraNormal::MouseControl()
{
	using namespace DirectX::SimpleMath;
	//カーソルの位置を取得
	POINT current;
	GetCursorPos(&current);
	//前フレームからの差分を取得
	Vector2 value;
	value.x = MOUSE_POSITION - static_cast<float>(current.x);
	value.y = MOUSE_POSITION - static_cast<float>(current.y);
	//感度取得
	float sensitivity = GameManager::GetInstance()->GetSensitivity() * 0.2f + 0.01f;
	//回転量に加算
	m_rotationY += value.x * sensitivity;
	m_rotationX += value.y * sensitivity;
	//マウスの位置を固定
	SetCursorPos(MOUSE_POSITION, MOUSE_POSITION);
	m_camera->SetRotataionY(m_rotationY);
}

void PlayCameraNormal::Reset()
{
	m_rotationX = 0;
	m_rotationY = 0;
}
