#include"pch.h"
#include"QuitButton.h"
#include"Base/Base.h"
#include"Base/Sound/Sound.h"

constexpr DirectX::SimpleMath::Vector2 POSITION = DirectX::SimpleMath::Vector2(910, 590);
constexpr DirectX::SimpleMath::Vector2 INITIAL_SIZE = DirectX::SimpleMath::Vector2(240, 88);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
QuitButton::QuitButton(Canvas* canvas):Button(canvas,"QuitButton",2)
{
	SetPosition(POSITION);
	SetSize(INITIAL_SIZE);
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select1", false);
}

/// <summary>
/// 左マウスクリックイベント
/// </summary>
/// <param name="within">範囲内か</param>
void QuitButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//サイズ変更
	if (within) { SetSize(INITIAL_SIZE * 1.2f); }
	else { SetSize(INITIAL_SIZE); }
}

/// <summary>
/// 左マウスクリックイベント 押されたらゲーム終了
/// </summary>
/// <param name="within">範囲内か</param>
void QuitButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		PostQuitMessage(0);
	}
}
