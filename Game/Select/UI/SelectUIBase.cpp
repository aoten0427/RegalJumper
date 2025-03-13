// ================================================================ 
// ファイル名 : SelectUIBase.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーンUIのベース
// ================================================================

#include"pch.h"
#include"SelectUIBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
SelectUIBase::SelectUIBase(Canvas* canvas):UserInterface(canvas,"SelectBase")
{
	using namespace DirectX::SimpleMath;

	SetPosition(Vector2(960, 360));
	SetSize(Vector2(640, 720));
	
}
