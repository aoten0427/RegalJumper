// ================================================================ 
// ファイル名 : Animation.cpp
// 作成者 : 景山碧天
// 説明 :  位置と回転を変化させるアニメーション
// ================================================================
#include"pch.h"
#include"Animation.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="holder">所属オブジェクト</param>
Animation::Animation(Object* holder)
	:
	m_holder{holder},
	m_changePosition{false,DirectX::SimpleMath::Vector3::Zero},
	m_positionSequence{nullptr},
	m_changeRotate{false,DirectX::SimpleMath::Quaternion::Identity},
	m_rotateSequence{nullptr}
{
}

/// <summary>
/// アニメーションアップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Animation::AnimationUpdate()
{
	//ポジションアニメーション
	if (m_changePosition.first)
	{
		m_holder->GetTransform()->SetPosition(m_changePosition.second);
	}
	//回転アニメーション
	if (m_changeRotate.first)
	{
		m_holder->GetTransform()->SetRotate(m_changeRotate.second);
	}
}

/// <summary>
/// ポジションアニメーション追加
/// </summary>
/// <param name="position">変更後</param>
/// <param name="speed">変更スピード</param>
/// <param name="ease">イージングタイプ</param>
/// <param name="delay">ディレイ時間</param>
void Animation::AddPositionAnimation(DirectX::SimpleMath::Vector3 position, float speed, std::string ease, float delay)
{
	//有効フラグをセット
	m_changePosition.first = true;
	//シークエンス作成
	if (m_positionSequence == nullptr)m_positionSequence = m_holder->AddComponent<Sequence>(m_holder);
	//Tween設定
	m_positionSequence->AppendVector3(m_changePosition.second, position, speed).SetChangeType(TweenCore::ChangeType::ReLoad).SetDelay(delay);
}

/// <summary>
/// ポジションアニメーションループ設定
/// </summary>
void Animation::PositionLoop()
{
	if(m_positionSequence)m_positionSequence->Loop();
}

/// <summary>
/// 回転アニメーション追加
/// </summary>
/// <param name="rotate">変更後</param>
/// <param name="speed">変更スピード</param>
/// <param name="ease">イージングタイプ</param>
/// <param name="delay">ディレイ時間</param>
void Animation::AddRotateAnimation(DirectX::SimpleMath::Quaternion rotate, float speed, std::string ease, float delay)
{
	//有効フラグをセット
	m_changeRotate.first = true;
	//シークエンス作成
	if (m_rotateSequence == nullptr)m_rotateSequence = m_holder->AddComponent<Sequence>(m_holder);
	//Tween設定
	m_rotateSequence->AppendQuaternion(m_changeRotate.second, rotate, speed).SetChangeType(TweenCore::ChangeType::ReLoad).SetDelay(delay);
}

/// <summary>
/// 回転アニメーションループ設定
/// </summary>
void Animation::RotateLoop()
{
	if(m_rotateSequence)m_rotateSequence->Loop();
}

/// <summary>
/// 開始処理
/// </summary>
void Animation::Play()
{
	//開始位置を設定
	m_changePosition.second = m_holder->GetTransform()->GetPosition();
	m_changeRotate.second = m_holder->GetTransform()->GetRotate();
	//リスタート処理
	if (m_positionSequence)m_positionSequence->ReStart();
	if (m_rotateSequence)m_rotateSequence->ReStart();
}

/// <summary>
/// 終了処理
/// </summary>
void Animation::End()
{
	if(m_positionSequence)m_positionSequence->Pause();
	if(m_rotateSequence)m_rotateSequence->Pause();
}


