// ================================================================ 
// ファイル名 : OptionContents.cpp
// 作成者 : 景山碧天
// 説明 :  オプションでの変更内容
// ================================================================

#include"pch.h"
#include"OptionContents.h"
#include"Base/Base.h"
#include"Base/Object/UnbreakableManager.h"

constexpr int BAR_LENTH = 386;             //バーの長さ
constexpr int HARF_LENTH = BAR_LENTH / 2;  //バーの長さの半分

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="contentsname">名前(コンテンツ表示名の画像)</param>
/// <param name="initialPar">初期パーセント</param>
OptionContents::OptionContents(Canvas* canvas, std::string contentsname, float initialPar):Button(canvas)
	,
	m_buttonActive{ false },
	m_contents{ nullptr },
	m_contentsName{ contentsname },
	m_mainBar{ nullptr },
	m_subBar{ nullptr },
	m_point{ nullptr },
	m_percent{ initialPar }
{
	using namespace DirectX::SimpleMath;
	SetSize(Vector2(400, 80));
	SetColor(Vector4(0, 0, 0, 0));

	//本体バー生成
	m_mainBar = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "main",canvas,"Quad",7);
	m_mainBar->SetSize(Vector2(390, 14));
	m_mainBar->SetColor(Vector4(0.73f, 0.95f, 0.94f, 1.0f));
	m_mainBar->GetTransform()->SetParent(GetTransform());
	//サブバー生成
	m_subBar = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "sub", canvas, "Quad", 8);
	m_subBar->SetSize(Vector2(BAR_LENTH, 9));
	m_subBar->SetOffset(DirectX::SimpleMath::Vector2(0, 0.5f));
	m_subBar->SetColor(Vector4(0, 0.95f, 0.94f, 1.0f));
	m_subBar->GetTransform()->SetParent(GetTransform());
	//割合ポイント生成
	m_point = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "point", canvas, "BarPoint", 9);
	m_point->SetSize(Vector2(30, 60));
	m_point->GetTransform()->SetParent(GetTransform());
	//コンテンツ表示名生成
	m_contents = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "name",canvas,m_contentsName,7);
	m_contents->SetSize(Vector2(108, 72));
	m_contents->GetTransform()->SetParent(GetTransform());

	
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void OptionContents::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (!m_buttonActive)return;
	auto& mouseTrack = GetCommonResources()->GetInput()->GetMouseTracker();
	//ボタンが離されたらアクティブ状態解除
	if (mouseTrack->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::UP)
	{
		m_buttonActive = false;
		DoFunction();
		return;
	}

	using namespace DirectX::SimpleMath;

	auto& mouseState = GetCommonResources()->GetInput()->GetMouseState();
	//マウスの位置を取得
	Vector2 position(static_cast<float>(mouseState.x), GetPosition().y);
	//範囲内に抑える
	if (position.x > GetPosition().x + HARF_LENTH)position.x = GetPosition().x + HARF_LENTH;
	if (position.x < GetPosition().x - HARF_LENTH)position.x = GetPosition().x - HARF_LENTH;
	//ポイントの位置をセット
	m_point->SetPosition(position);

	//割合を計算
	m_percent = (position.x - (GetPosition().x - HARF_LENTH)) / BAR_LENTH;

	//サブバーの位置を調整
	m_subBar->SetSize(DirectX::SimpleMath::Vector2(BAR_LENTH * m_percent, 9));
}

/// <summary>
/// ポジションをセット
/// </summary>
/// <param name="position">変更ポジション</param>
void OptionContents::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	using namespace DirectX::SimpleMath;
	UserInterface::SetPosition(position);
	m_mainBar->SetPosition(position);
	m_contents->SetPosition(position + Vector2(0, -60));
	m_subBar->SetPosition(position + Vector2(-BAR_LENTH / 2, 0));
	m_subBar->SetSize(Vector2(BAR_LENTH * m_percent, 9));
	m_point->SetPosition(Vector2((position.x - HARF_LENTH) + BAR_LENTH * m_percent, position.y));
}

/// <summary>
/// 開く
/// </summary>
void OptionContents::Open()
{
	SetActive(true);
}

/// <summary>
/// 閉じる
/// </summary>
void OptionContents::Close()
{
	SetActive(false);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">自身の範囲内か</param>
void OptionContents::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	//表示名の色を変更
	if (within)
	{
		m_contents->SetColor(DirectX::SimpleMath::Vector4(0.1, 0.75f, 0.93f, 1));
	}
	else
	{
		m_contents->SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// 左マウスクリックイベント
/// </summary>
/// <param name="within">自身の範囲内か</param>
void OptionContents::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	if (within)m_buttonActive = true;
}
