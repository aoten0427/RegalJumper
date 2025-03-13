// ================================================================ 
// ファイル名 : FadeManager.cpp
// 作成者 : 景山碧天
// 説明 :  フェードの管理を行う
// ================================================================

#include"pch.h"
#include"FadeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
FadeManager::FadeManager()
	:
	m_currentFade{nullptr},
	m_fades{}
{
}

/// <summary>
/// フェードの開始
/// </summary>
/// <param name="fadeName">稼働するフェード</param>
/// <param name="function">フェードアウト後の処理</param>
void FadeManager::FadeStart(std::string fadeName, std::function<void()> function)
{
	//フェード検索
	if (m_fades.find(fadeName) != m_fades.end())
	{
		//稼働中か調べる
		if (m_fades[fadeName]->GetState() == Fade::State::Out)
		{
			//稼働フェードにセット
			m_currentFade = m_fades[fadeName];
			m_currentFade->Start(function);
		}
	}
}

/// <summary>
/// 稼働中のフェードの状態を得る
/// </summary>
/// <returns>稼働フェードの状態</returns>
Fade::State FadeManager::GetCurrentFadeState()
{
	//稼働フェードの状態を返す
	if (m_currentFade != nullptr)
	{
		return m_currentFade->GetState();
	}
	return Fade::State::Out;
}

/// <summary>
/// フェード追加
/// </summary>
/// <param name="fade">追加フェード</param>
void FadeManager::AddFade(Fade* fade)
{
	m_fades.insert({ fade->GetName(),fade });
}
