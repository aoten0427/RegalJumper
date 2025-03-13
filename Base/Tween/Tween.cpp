// ================================================================ 
// ファイル名 : Tween.h
// 作成者 : 景山碧天
// 説明 :  Tweenを扱うためのクラス
// ================================================================
#include"pch.h"
#include"Tween.h"
#include"TweenManager.h"
#include"TweenCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
Tween::Tween(Object* object,bool reuse):Component(object)
	,
	m_core{nullptr},
	m_reuse{reuse}
{
	m_core = TweenManager::GetInstance()->AddTween(*this);
}

/// <summary>
/// デストラクタ
/// </summary>
Tween::~Tween()
{
	//本体に削除要請
	if (m_core)m_core->Destroy();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過</param>
void Tween::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//コアがない場合返す
	if (!m_core)return;
	//コアが削除状態なら自身も削除
	if (m_core->GetState() == TweenCore::State::DESTROY)
	{
		Destroy();
	}
}

/// <summary>
/// Int処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>コア</returns>
TweenCore& Tween::DoInt(int& origin, int end, float time)
{
	m_core->DoInt(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Float処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>コア</returns>
TweenCore& Tween::DoFloat(float& origin, float end, float time)
{
	m_core->DoFloat(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Vector2処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>コア</returns>
TweenCore& Tween::DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time)
{
	m_core->DoVector2(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Vector3処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>コア</returns>
TweenCore& Tween::DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time)
{
	m_core->DoVector3(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Vector4処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>コア</returns>
TweenCore& Tween::DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time)
{
	m_core->DoVector4(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// Quaternion処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>コア</returns>
TweenCore& Tween::DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time)
{
	m_core->DOQuaternion(origin, end, time);
	m_core->SetReuse(m_reuse);
	return *m_core;
}

/// <summary>
/// 終了
/// </summary>
void Tween::Kill()
{
	//コアがない場合返す
	if (!m_core)return;
	m_core->Kill();
}

/// <summary>
/// 一時停止
/// </summary>
void Tween::Pause()
{
	//コアがない場合返す
	if (!m_core)return;
	m_core->Pause();
}

/// <summary>
/// 再開
/// </summary>
void Tween::Play()
{
	//コアがない場合返す
	if (!m_core)return;
	m_core->Play();
}
