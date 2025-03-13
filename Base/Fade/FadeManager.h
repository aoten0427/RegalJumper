// ================================================================ 
// ファイル名 : FadeManager
// 作成者 : 景山碧天
// 説明 :  フェードの管理を行う
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"
#include"Base/Fade/Fade.h"


class FadeManager :public Singleton<FadeManager>
{
	friend class Singleton<FadeManager>;
private:
	FadeManager();
private:
	//現在稼働中のフェード
	Fade* m_currentFade;
	//登録されているフェード
	std::unordered_map<std::string, Fade*> m_fades;
public:
	~FadeManager() = default;
	//フェードの開始(稼働するフェード,フェードアウト後の処理)
	void FadeStart(std::string fadeName, std::function<void()> function = nullptr);
	//稼働中のフェードの状態を得る
	Fade::State GetCurrentFadeState();
	//フェード登録
	void AddFade(Fade* fade);
};