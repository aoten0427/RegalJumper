// ================================================================ 
// ファイル名 : HelpInfomation.cpp
// 作成者 : 景山碧天
// 説明 :  ヘルプ内容
// ================================================================
#include"pch.h"
#include"HelpInfomation.h"
#include"Base/Scene/Scene.h"
#include"Base/Screen.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="infomation">インフォメーション名</param>
HelpInfomation::HelpInfomation(Canvas* canvas,INFOMATION infomation):UserInterface(canvas)
	,
	m_size{DirectX::SimpleMath::Vector2::Zero}
{
	using namespace DirectX::SimpleMath;
	//背景生成
	m_bg = GetScene()->AddObject<UserInterface>(canvas);
	m_bg->SetPosition(Vector2(Screen::CENTER_X, Screen::CENTER_Y));
	m_bg->SetSize(Vector2(Screen::WIDTH, Screen::HEIGHT));
	m_bg->SetColor(Vector4(1, 1, 1, 0.3f));
	m_bg->GetTransform()->SetParent(GetTransform());

	SetSize(m_size);
	SetRenderOrder(3);
	//説明画像読み込み
	switch (infomation)
	{
	case INFOMATION::SHOT:
		SetTexture("HelpInfomation1");
		break;
	case INFOMATION::MOVE:
		SetTexture("HelpInfomation2");
		break;
	case INFOMATION::JUMP:
		SetTexture("HelpInfomation3");
		break;
	case INFOMATION::SHOT2:
		SetTexture("HelpInfomation4");
		break;
	default:
		break;
	}

	m_tween = AddComponent<Tween>(this, true);
	SetActive(false);
}

/// <summary>
///	アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void HelpInfomation::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetSize(m_size);
}

/// <summary>
/// 開く
/// </summary>
void HelpInfomation::Open()
{
	SetActive(true);
	m_tween->DoVector2(m_size, DirectX::SimpleMath::Vector2(1000, 500), 0.3f).SetEase(Easing::Ease::OutQuart);
}

/// <summary>
/// 閉じる
/// </summary>
void HelpInfomation::Close()
{
	m_tween->DoVector2(m_size, DirectX::SimpleMath::Vector2(0,0), 0.15f).SetEase(Easing::Ease::InQuart).SetCompleteFunction([&]() {
		SetActive(false);
		GetScene()->ChangeState(Scene::State::PLAY);
		});
}
