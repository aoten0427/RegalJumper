// ================================================================ 
// ファイル名 : Fade.cpp
// 作成者 : 景山碧天
// 説明 :  フェード基底クラス
// ================================================================

#include"pch.h"
#include"Fade.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas"></param>
/// <param name="fadeName"></param>
Fade::Fade(Canvas* canvas, std::string fadeName):UserInterface(canvas)
	,
	m_state{State::Out},
	m_name{fadeName}
{
	//フェードマネージャに登録
	FadeManager::GetInstance()->AddFade(this);
	//描画オーダー設定
	SetRenderOrder(20);
}

/// <summary>
/// デストラクタ
/// </summary>
Fade::~Fade()
{
}

