// ================================================================ 
// ファイル名 : UIManager.cpp
// 作成者 : 景山碧天
// 説明 :  UIの動作管理
// ================================================================

#include"pch.h"
#include"UIManager.h"
#include"Base/CommonResources.h"
#include"Base/Input/DirectXInputs.h"
#include"Base/Canvas/UserInterface/UserInterface.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="commonResources">コモンリソース</param>
UIManager::UIManager(CommonResources* commonResources)
	:
	m_userInterfaces{}
{
	//入力システム入手
	m_input = commonResources->GetInput();
}

/// <summary>
/// 更新
/// </summary>
void UIManager::Update()
{
	//マウスの座標を取得
	DirectX::SimpleMath::Vector2 mousePos(static_cast<float>(m_input->GetMouseState().x), static_cast<float>(m_input->GetMouseState().y));

	std::vector<UserInterface*> active;
	//現在アクティブのものを取得
	for (auto& ui : m_userInterfaces)
	{
		//イベントフラグがオフの場合スルー
		if (!ui->GetMouseEventFlag())continue;
		if (ui->GetActive())active.push_back(ui);
	}

	for (auto& ui : active)
	{
		//範囲に入っているか
		bool within = WithIn(mousePos, ui);
		//イベント実行
		ui->MouseWithinEvent(within);

		//左キーを押していたらクリックイベント実行
		if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
		{
			ui->LeftClickEvent(within);
		}
	}
}

/// <summary>
/// UI追加
/// </summary>
/// <param name="userinterfase">追加UI</param>
void UIManager::AddUserInterface(UserInterface* userinterfase)
{
	m_userInterfaces.push_back(userinterfase);
}

/// <summary>
/// UI削除
/// </summary>
/// <param name="userinterface">削除UI</param>
void UIManager::ReMoveUserInterface(UserInterface* userinterface)
{
	auto remove = std::find(m_userInterfaces.begin(), m_userInterfaces.end(), userinterface);
	if (remove != m_userInterfaces.end())
	{
		m_userInterfaces.erase(remove);
	}
}

/// <summary>
/// 内部判定取得
/// </summary>
/// <param name="pos">マウスポジション</param>
/// <param name="ui">UI</param>
/// <returns>内部にあるか</returns>
bool UIManager::WithIn(const DirectX::SimpleMath::Vector2& pos, UserInterface* ui)
{
	using namespace DirectX::SimpleMath;

	Vector2 position = ui->GetPosition();
	Vector2 size(abs(ui->GetSize().x), abs(ui->GetSize().y));
	Vector2 offsetPar = ui->GetOffset();

	//UIの四隅を取得
	RECT corner = RECT{
		static_cast<int>(position.x - size.x * offsetPar.x),
		static_cast<int>(position.y - size.y * offsetPar.y),
		static_cast<int>(position.x + size.x * (1 - offsetPar.x)),
		static_cast<int>(position.y + size.y * (1 - offsetPar.y)),
	};

	if (corner.left > pos.x)return false;
	if (corner.right < pos.x)return false;
	if (corner.top > pos.y)return false;
	if (corner.bottom < pos.y)return false;

	return true;
}
