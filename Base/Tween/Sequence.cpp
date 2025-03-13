// ================================================================ 
// ファイル名 : Sequence.cpp
// 作成者 : 景山碧天
// 説明 :  Tweenを複数管理する
// ================================================================

#include"pch.h"
#include"Sequence.h"
#include"TweenManager.h"
#include"TweenCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
Sequence::Sequence(Object* object):Component(object)
	,
	m_cores{},
	m_activeNumber{0}
{

}

/// <summary>
/// デストラクタ
/// </summary>
Sequence::~Sequence()
{
	//コアに削除要請
	for (auto& core : m_cores)
	{
		core->Destroy();
	}
	m_cores.clear();
}

/// <summary>
/// int追加
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>追加コア</returns>
TweenCore& Sequence::AppendInt(int& origin, int end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoInt(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// float追加
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>追加コア</returns>
TweenCore& Sequence::AppendFloat(float& origin, float end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoFloat(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Vector2追加
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>追加コア</returns>
TweenCore& Sequence::AppendVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoVector2(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Vector3追加
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>追加コア</returns>
TweenCore& Sequence::AppendVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoVector3(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Vector4追加
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>追加コア</returns>
TweenCore& Sequence::AppendVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DoVector4(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// Quaternion追加
/// </summary>
/// <param name="origin">変更する値</param>
/// <param name="end">終了値</param>
/// <param name="time">変更時間</param>
/// <returns>追加コア</returns>
TweenCore& Sequence::AppendQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time)
{
	TweenCore* newCore = TweenManager::GetInstance()->AddTween(*this);
	newCore->DOQuaternion(origin, end, time);
	newCore->SetReuse(true);
	AppendProcess(newCore);
	return *newCore;
}

/// <summary>
/// 完了
/// </summary>
void Sequence::Kill()
{
	for (auto& core : m_cores)
	{
		core->Kill();
	}
}

/// <summary>
/// 再開
/// </summary>
void Sequence::Play()
{
	m_cores[m_activeNumber]->Play();
}

/// <summary>
/// 一時停止
/// </summary>
void Sequence::Pause()
{
	m_cores[m_activeNumber]->Pause();
}

/// <summary>
/// ループ
/// </summary>
void Sequence::Loop()
{
	if (m_cores.empty())return;
	//最後尾の関数取得
	std::function<void()> function = m_cores.back()->GetFunction();
	m_cores.back()->SetCompleteFunction([&, function]() {
		//既存の関数を実行
		if (function)function();
		//リスタート処理実行
		ReStart();
		});
}

/// <summary>
/// 最初から始める
/// </summary>
void Sequence::ReStart()
{
	if (m_cores.empty())return;
	for (auto& core : m_cores)
	{
		core->ReStart();
		core->Pause();
	}
	m_cores[0]->Play();
	m_activeNumber = 0;
}

/// <summary>
/// 追加時の手続き
/// </summary>
/// <param name="newCore">追加コア</param>
void Sequence::AppendProcess(TweenCore* newCore)
{
	m_cores.push_back(newCore);
	//更新を止める
	newCore->Pause();
	//一つの場合は更新を開始して返す
	if (m_cores.size() == 1)
	{
		newCore->Play();
		return;
	}

	//現時点の最後尾の番号を取得
	int back = static_cast<int>(m_cores.size()) - 1;
	//現時点の最後尾 - 1の関数を取得
	std::function<void()> function = m_cores[back - 1]->GetFunction();
	//最後尾 - 1の終了関数に最後尾のPlay関数をセット
	m_cores[back - 1]->SetCompleteFunction([&, function,back]() {
		//既存の関数を実行
		if (function)function();
		//起動
		m_cores[back]->Play();
		m_activeNumber = back;
		});
}
