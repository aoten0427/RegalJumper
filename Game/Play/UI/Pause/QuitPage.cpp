// ================================================================ 
// ファイル名 : QuitPage.cpp
// 作成者 : 景山碧天
// 説明 :  退出ページ
// ================================================================
#include"pch.h"
#include"QuitPage.h"
#include"Base/Base.h"
#include"Base/Screen.h"
#include"Game/Play/UI/Pause/Pause.h"

constexpr DirectX::SimpleMath::Vector2 BUTTON_SIZE = DirectX::SimpleMath::Vector2(160, 80);
constexpr float BUTTON_X = 150.0f;
constexpr float BUTTON_Y = 500.0f;

/// <summary>
/// 退出選択ボタン　コンストラクタ
/// </summary>
/// <param name="canvas"></param>
QButton::QButton(Canvas* canvas) :Button(canvas)
{
	SetRenderOrder(6);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void QButton::MouseWithinEvent(bool within)
{
	//色変更
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0, 0.87f, 0.82f, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// 退出ページ　コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="pause">ポーズ</param>
QuitPage::QuitPage(Canvas* canvas, Pause* pause):UserInterface(canvas,"QuitBorad",5)
{
	using namespace DirectX::SimpleMath;

	
	SetSize(DirectX::SimpleMath::Vector2(640, 640));

	auto bg = GetScene()->AddObject<UserInterface>(canvas);
	bg->GetTransform()->SetParent(GetTransform());
	bg->SetSize(Vector2(Screen::WIDTH, Screen::HEIGHT));
	bg->SetColor(Vector4(1, 1, 1, 0.5));

	
	//終了はいボタン
	auto yes = GetScene()->AddObject<QButton>(canvas);
	yes->SetTexture("Yes");
	yes->SetPosition(Vector2(Screen::CENTER_X - BUTTON_X, BUTTON_Y));
	yes->SetSize(Vector2(160, 80));
	yes->GetTransform()->SetParent(GetTransform());
	yes->SetFunction([&]() {
		PostQuitMessage(0);
		});

	//終了いいえボタン
	auto no = GetScene()->AddObject<QButton>(canvas);
	no->SetTexture("No");
	no->SetPosition(Vector2(Screen::CENTER_X + BUTTON_X, BUTTON_Y));
	no->SetSize(Vector2(240, 80));
	no->GetTransform()->SetParent(GetTransform());
	no->SetFunction([&,pause]() {
		SetActive(false);
		pause->SetActive(true);
		});

	SetActive(false);
}


