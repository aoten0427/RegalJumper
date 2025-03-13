// ================================================================ 
// ファイル名 : CursorEffect.cpp
// 作成者 : 景山碧天
// 説明 :  カーソルクリック時のエフェクト
// ================================================================

#include"pch.h"
#include"CursorEffect.h"
#include"Base/Tween/DoTween.h"

constexpr float INITIAL_SIZE = 20;
constexpr float TARGET_SIZE = 70;
constexpr float SPEED = 0.2f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="position">生成位置</param>
CursorEffect::CursorEffect(Canvas* canvas, DirectX::SimpleMath::Vector2 position):UserInterface(canvas,"CursorEffect",8)
	,
	m_size{INITIAL_SIZE}
{

	SetSize(DirectX::SimpleMath::Vector2(m_size,m_size));
	SetPosition(position);

	//変化Tween生成
	Tween* tween = AddComponent<Tween>(this);
	tween->DoFloat(m_size, TARGET_SIZE, SPEED).SetEase(Easing::Ease::Normal).SetCompleteFunction([&]() {
		Destroy();
		});
}

/// <summary>
/// アップデート　サイズ変更
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void CursorEffect::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetSize(DirectX::SimpleMath::Vector2(m_size, m_size));
}
