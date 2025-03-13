// ================================================================ 
// ファイル名 : SelectPlayButton.cpp
// 作成者 : 景山碧天
// 説明 :  プレイシーン移行ボタン
// ================================================================
#include"pch.h"
#include"SelectPlayButton.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Subject.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
SelectPlayButton::SelectPlayButton(Canvas* canvas):Button(canvas,"SPlayButton",1)
	,
	m_bg{nullptr},
	m_ClickSubject{nullptr}
{
	SetPosition(DirectX::SimpleMath::Vector2(950, 600));
	SetSize(DirectX::SimpleMath::Vector2(350, 150));

	//色変更部分作成
	m_bg = GetScene()->AddObject<UserInterface>(canvas,"Quad",2);
	m_bg->SetPosition(DirectX::SimpleMath::Vector2(950, 600));
	m_bg->SetSize(DirectX::SimpleMath::Vector2(290, 114));
	m_bg->SetColor(DirectX::SimpleMath::Vector4(0.078f, 0.156f, 0.552, 0.2f));

	//通知作成
	m_ClickSubject = AddComponent<Subject<>>(this, "SelectPlay");
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void SelectPlayButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//色変更
	if (within)
	{
		m_bg->SetColor(DirectX::SimpleMath::Vector4(0.33, 1, 0.8, 0.5f));

	}
	else
	{
		m_bg->SetColor(DirectX::SimpleMath::Vector4(0.078f, 0.156f, 0.552, 0.2f));
	}
}

/// <summary>
/// 左マウスクリックイベント
/// </summary>
/// <param name="within">範囲内か</param>
void SelectPlayButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//通知
		m_ClickSubject->Notify();
	}
}
