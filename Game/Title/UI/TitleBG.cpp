// ================================================================ 
// ファイル名 : TitleBG.cpp
// 作成者 : 景山碧天
// 説明 :  タイトルの背景、ロゴ
// ================================================================
#include"pch.h"
#include"TitleBG.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
TitleBG::TitleBG(Canvas* canvas):UserInterface(canvas)
	,
	m_logo{nullptr},
	m_timer{}
{
	using namespace DirectX::SimpleMath;

	//背景設定
	SetTexture("TitleBG");
	SetSize(Vector2(Screen::WIDTH,Screen::HEIGHT));

	//ロゴ設定
	m_logo = GetScene()->AddObject<UserInterface>(canvas,"Logo",1);
	m_logo->SetPosition(Vector2(400, 300));
	m_logo->SetSize(Vector2(900, 510));

	//シェーダーを変更
	SetPixelShader("TitleFramePS.cso");
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void TitleBG::ObjectUpdate(float deltatime)
{
	//タイマーを変更
	m_timer += deltatime / 4;
	SetFreeElement(DirectX::SimpleMath::Vector4(m_timer, 0, 0, 0));
}
