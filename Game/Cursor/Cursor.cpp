// ================================================================ 
// ファイル名 : Cursor.cpp
// 作成者 : 景山碧天
// 説明 :  カーソルを表示
// ================================================================
#include"pch.h"
#include"Cursor.h"
#include"Base/Base.h"
#include"Game/GameManager.h"
#include"Game/Cursor/CursorEffect.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
Cursor::Cursor(Canvas* canvas):UserInterface(canvas,"Cursor",10)
{
	GameManager::GetInstance()->SetCursor(this);
	SetSize(DirectX::SimpleMath::Vector2(20, 20));
	SetColor(DirectX::SimpleMath::Vector4(0.1f, 1.0f, 0.8f, 1.0f));
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Cursor::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (!GetActive())return;
	//位置を更新
	DirectXInputs* input = GetCommonResources()->GetInput();
	auto& mouse = input->GetMouseState();
	SetPosition(DirectX::SimpleMath::Vector2(static_cast<float>(mouse.x), static_cast<float>(mouse.y)));
	//クリックイベント
	if (input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		MakeEffect();
	}
}

/// <summary>
/// エフェクト生成
/// </summary>
void Cursor::MakeEffect()
{
	GetScene()->AddObject<CursorEffect>(GetCanvas(), GetPosition());
}
