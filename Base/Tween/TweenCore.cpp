// ================================================================ 
// ファイル名 : TweenCore.cpp
// 作成者 : 景山碧天
// 説明 :  Tweenの実行本体
// ================================================================

#include"pch.h"
#include"TweenCore.h"
#include"TweenManager.h"
#include"TweenUpdate.h"

/// <summary>
/// コンストラクタ
/// </summary>
TweenCore::TweenCore()
	:
	m_state{State::PLAY},
	m_update{nullptr},
	m_delayTime{0},
	m_function{nullptr},
	m_loopCount{0},
	m_loopType{LoopType::Yoyo},
	m_reuse{false}
{
}

/// <summary>
/// デストラクタ
/// </summary>
TweenCore::~TweenCore()
{
	m_update = nullptr;
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void TweenCore::Update(float deltatime)
{
	if (!m_update)return;
	//プレイ状態でないなら返す
	if (m_state != State::PLAY)return;

	//遅延時間が過ぎていないなら減少させ返す
	if (m_delayTime > 0)
	{
		m_delayTime -= deltatime;
		return;
	}
	//終了フラグを格納
	bool isFinish = m_update->Update(deltatime);

	//終了処理実行
	if (isFinish)
	{
		m_state = State::FINISH;
		//関数実行
		DoFunction();

		//終了判断
		if (m_loopCount == 0)
		{
			//再利用フラグがfalseの場合削除
			if (!m_reuse)
			{
				Destroy();
			}
			return;
		}

		//ループ処理
		Loop();
	}
}

/// <summary>
/// 関数実行
/// </summary>
void TweenCore::DoFunction()
{
	//関数実行
	if (m_function)m_function();
}

/// <summary>
/// ループ処理
/// </summary>
void TweenCore::Loop()
{
	//ループ設定がない場合返す
	if (m_loopCount == 0)return;
	//ループカウントを減少
	if (m_loopCount > 0)m_loopCount--;
	//ループタイプによって値を変更
	switch (m_loopType)
	{
	case TweenCore::LoopType::Yoyo:
		if (m_update)m_update->Yoyo();
		break;
	case TweenCore::LoopType::ReStart:
		if (m_update)m_update->ReStart();
		break;
	case TweenCore::LoopType::Incremental:
		if (m_update)m_update->Incremental();
		break;
	default:
		break;
	}
	m_state = State::PLAY;
}

/// <summary>
/// 削除
/// </summary>
void TweenCore::Destroy()
{
	//削除処理依頼
	TweenManager::GetInstance()->CoreDestroyOn();
	//破壊状態に
	m_state = State::DESTROY;
}


/// <summary>
/// Int処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::DoInt(int& origin, int end, float time)
{
	m_update = std::make_unique<TweenUpdate<int>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Float処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::DoFloat(float& origin, float end, float time)
{
	m_update = std::make_unique<TweenUpdate<float>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Vector2処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Vector2>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Vector3処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Vector3>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Vector4処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Vector4>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}

/// <summary>
/// Quaternion処理
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time)
{
	m_update = std::make_unique<TweenUpdate<DirectX::SimpleMath::Quaternion>>(origin, end, time);
	m_state = State::PLAY;
	m_function = nullptr;
	return *this;
}



/// <summary>
/// 遅延時間を設定
/// </summary>
/// <param name="delaytime">遅延時間</param>
/// <returns>自身</returns>
TweenCore& TweenCore::SetDelay(float delaytime)
{
	m_delayTime = delaytime;
	return *this;
}

/// <summary>
/// 終了時に呼び出す関数を設定
/// </summary>
/// <param name="action">呼び出し関数</param>
/// <returns>自身</returns>
TweenCore& TweenCore::SetCompleteFunction(std::function<void()> action)
{
	m_function = action;
	return *this;
}

/// <summary>
/// イージングの種類を設定
/// </summary>
/// <param name="easy">イージングタイプ</param>
/// <returns>自身</returns>
TweenCore& TweenCore::SetEase(Easing::Ease easy)
{
	if (m_update)m_update->SetEase(easy);
	return *this;
}

/// <summary>
/// ループを設定
/// </summary>
/// <param name="count">ループ回数 -1で無限</param>
/// <param name="looptype">ループタイプ</param>
/// <returns>自身</returns>
TweenCore& TweenCore::SetLoop(int count, LoopType looptype)
{
	m_loopCount = count;
	m_loopType = looptype;
	return *this;
}

/// <summary>
/// 変化タイプの変更
/// </summary>
/// <param name="type">変化タイプ</param>
/// <returns>自身</returns>
TweenCore& TweenCore::SetChangeType(ChangeType type)
{
	m_changeType = type;
	return *this;
}

/// <summary>
/// 相対移動に設定
/// </summary>
/// <returns>自身</returns>
TweenCore& TweenCore::Relative()
{
	if (m_update)m_update->Relative();
	return *this;
}

/// <summary>
/// 初期値を現在値に変更
/// </summary>
/// <returns>自身</returns>
TweenCore& TweenCore::ReLoad()
{
	if (m_update)m_update->ReLoad();
	return *this;
}

/// <summary>
/// 終了させる
/// </summary>
void TweenCore::Kill()
{
	if (m_update)m_update->Kill();
}

/// <summary>
/// 止める
/// </summary>
void TweenCore::Pause()
{
	m_state = State::PAUSE;
}

/// <summary>
/// 再開
/// </summary>
void TweenCore::Play()
{
	m_state = State::PLAY;
	switch (m_changeType)
	{
	case TweenCore::ChangeType::Default:
		break;
	case TweenCore::ChangeType::Relative:
		Relative();
		break;
	case TweenCore::ChangeType::ReLoad:
		ReLoad();
		break;
	default:
		break;
	}
}

/// <summary>
/// 再スタート処理
/// </summary>
void TweenCore::ReStart()
{
	if (!m_update)return;
	m_state = State::PLAY;
	m_delayTime = 0;
	m_update->ReStart();
}





