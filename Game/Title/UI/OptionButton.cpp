// ================================================================ 
// ファイル名 : OptionButton.cpp
// 作成者 : 景山碧天
// 説明 :  タイトル画面でのオプションボタン
// ================================================================

#include"pch.h"
#include "OptionButton.h"
#include"Base/Scene/Scene.h"
#include"Base/Sound/Sound.h"
#include"Game/GameManager.h"


constexpr DirectX::SimpleMath::Vector2 INITIAL_SIZE = DirectX::SimpleMath::Vector2(400, 88);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
OptionButton::OptionButton(Canvas* canvas) :Button(canvas,"OptionButton",1)
{
	SetPosition(DirectX::SimpleMath::Vector2(990, 460));
	SetSize(INITIAL_SIZE);
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select1", false);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void OptionButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//サイズ変更
	if (within) { SetSize(INITIAL_SIZE * 1.2f); }
	else { SetSize(INITIAL_SIZE); }
}

/// <summary>
/// 左マウスクリックイベント オプションを開く
/// </summary>
/// <param name="within">範囲内か</param>
void OptionButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//オプションを開く
		GameManager::GetInstance()->OpenOption();
		SetSize(INITIAL_SIZE);
		m_sound->Play();
	}
}
