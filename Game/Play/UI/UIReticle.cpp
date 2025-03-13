// ================================================================ 
// ファイル名 : UIReticle.cpp
// 作成者 : 景山碧天
// 説明 :  レティクル
// ================================================================
#include"pch.h"
#include"UIReticle.h"
#include"Base/Scene/Scene.h"
#include"Base/Screen.h"
#include"Base/Event/Observer.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
UIReticle::UIReticle(Canvas* canvas):UserInterface(canvas,"UIReticle",2)
{
	SetPosition(DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y + 10));
	SetSize(DirectX::SimpleMath::Vector2(360, 260));

	UserInterface* esc = GetScene()->AddObject<UserInterface>(canvas, "Escape", 2);
	esc->SetPosition(DirectX::SimpleMath::Vector2(30, 30));
	esc->SetSize(DirectX::SimpleMath::Vector2(35, 35));

	//ポーズに付随したオブザーバー
	//ポーズオープン
	Observer<>* pauseOpen = AddComponent<Observer<>>(this);
	pauseOpen->SetFunction([&]() {SetActive(false); });
	pauseOpen->RegistrationSubject("PauseOpen");
	//ポーズクローズ
	Observer<>* pauseClose = AddComponent<Observer<>>(this);
	pauseClose->SetFunction([&]() {SetActive(true); });
	pauseClose->RegistrationSubject("PauseClose");

	//レティクルが壁に当たる際の色変更
	Observer<bool>* hitObs = AddComponent<Observer<bool>>(this);
	hitObs->SetFunction(std::bind(&UIReticle::ChangeColor, this, std::placeholders::_1));
	hitObs->RegistrationSubject("Reticle");
}

/// <summary>
/// レティクルが壁に当たる際の色変更
/// </summary>
/// <param name="hit"></param>
void UIReticle::ChangeColor(bool hit)
{
	if (hit)
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 0.0, 1, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}
