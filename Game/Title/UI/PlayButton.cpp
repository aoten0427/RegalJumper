// ================================================================ 
// ファイル名 : PlayButton.cpp
// 作成者 : 景山碧天
// 説明 :  タイトル画面でのプレイボタン
// ================================================================
#include"pch.h"
#include"Base/Scene/Scene.h"
#include"PlayButton.h"
#include"Base/Fade/FadeManager.h"
#include"Base/Sound/Sound.h"

constexpr DirectX::SimpleMath::Vector2 POSITION = DirectX::SimpleMath::Vector2(940, 330);
constexpr DirectX::SimpleMath::Vector2 INITIAL_SIZE = DirectX::SimpleMath::Vector2(240, 88);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
PlayButton::PlayButton(Canvas* canvas):Button(canvas,"PlayButton",1)
{
	using namespace DirectX::SimpleMath;

	SetPosition(POSITION);
	SetSize(INITIAL_SIZE);
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select1", false);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void PlayButton::MouseWithinEvent(bool within)
{
	using namespace DirectX::SimpleMath;
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//触れていたら大きくする
	if (within) { SetSize(INITIAL_SIZE * 1.2f); }
	else { SetSize(INITIAL_SIZE); }
}

/// <summary>
/// 左マウスクリックイベント ステージ選択画面の移動
/// </summary>
/// <param name="within">範囲内か</param>
void PlayButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//フェードを起動しセレクトシーンへ
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::SELECT);
			});
		m_sound->Play();
	}
}
