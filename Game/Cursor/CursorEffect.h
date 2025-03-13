// ================================================================ 
// ファイル名 : CursorEffect.h
// 作成者 : 景山碧天
// 説明 :  カーソルクリック時のエフェクト
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class CursorEffect :public UserInterface
{
private:
	//大きさ
	float m_size;
public:
	//コンストラクタ
	CursorEffect(Canvas* canvas,DirectX::SimpleMath::Vector2 position);
	//デストラクタ
	~CursorEffect()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
};