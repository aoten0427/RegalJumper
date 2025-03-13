#include"pch.h"
#include"TweenManager.h"
#include"TweenCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
TweenManager::TweenManager()
	:
	m_tweens{},
	m_isCoreDestroy{false}
{
}

/// <summary>
/// デストラクタ
/// </summary>
TweenManager::~TweenManager()
{
}

/// <summary>
/// TweenCore作成(Tweenクラスから)
/// </summary>
/// <param name="tween">コアが所属するTween</param>
/// <returns>追加コア</returns>
TweenCore* TweenManager::AddTween(const Tween& tween)
{
	UNREFERENCED_PARAMETER(tween);
	//新しいTweenCoreの生成
	std::unique_ptr<TweenCore> newCore = std::make_unique<TweenCore>();
	TweenCore* returnCore = newCore.get();
	m_tweens.push_back(std::move(newCore));
	return returnCore;
}

/// <summary>
/// TweenCore作成(Sequenceクラスから)
/// </summary>
/// <param name="tween">コアが所属するSequence</param>
/// <returns>追加コア</returns>
TweenCore* TweenManager::AddTween(const Sequence& sequence)
{
	UNREFERENCED_PARAMETER(sequence);
	//新しいTweenCoreの生成
	std::unique_ptr<TweenCore> newCore = std::make_unique<TweenCore>();
	TweenCore* returnCore = newCore.get();
	m_tweens.push_back(std::move(newCore));
	return returnCore;
}

/// <summary>
/// Tween削除
/// </summary>
void TweenManager::RemoveTween()
{
	//削除要請がなければパス
	if (!m_isCoreDestroy)return;
	//削除要素を削除
	m_tweens.erase(std::remove_if(m_tweens.begin(), m_tweens.end(), [&]
	(std::unique_ptr<TweenCore>& core) {
			return core.get()->GetState() == TweenCore::State::DESTROY;
		}), m_tweens.end());
	//削除要請をオフに
	m_isCoreDestroy = false;
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void TweenManager::Update(float deltatime)
{
	for (auto& tween : m_tweens)
	{
		tween->Update(deltatime);
	}
	RemoveTween();
}


