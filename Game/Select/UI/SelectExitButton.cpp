// ================================================================ 
// ファイル名 : SelectExitButton.cpp
// 作成者 : 景山碧天
// 説明 :  セレクトシーン退出ボタン
// ================================================================
#include"pch.h"
#include"SelectExitButton.h"
#include"Base/Scene/Scene.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
SelectExitButton::SelectExitButton(Canvas* canvas):Button(canvas,"SelectQuit")
{
	using namespace DirectX::SimpleMath;
	SetSize(Vector2(150, 90));
	SetPosition(Vector2(75, 45));

	m_str = GetScene()->AddObject<UserInterface>(canvas, "SelectQuit2", 2);
	m_str->SetSize(Vector2(150, 90));
	m_str->SetPosition(Vector2(75, 45));
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void SelectExitButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//色変更
	if (within)
	{
		m_str->SetColor(DirectX::SimpleMath::Vector4(0.33, 1, 0.8, 1.0f));
	}
	else
	{
		m_str->SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// 左マウスクリックイベント
/// </summary>
/// <param name="within">範囲内か</param>
void SelectExitButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//フェードを起動しタイトルシーンへ
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::TITLE);
			});
	}
}
