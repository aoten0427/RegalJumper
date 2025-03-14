#pragma once
#include"InputAxisFormat.h"

class MouseFormat:public InputAxisFormat
{
private:
	POINT m_fixCursorPos;
public:
	MouseFormat();

	//軸の状態を確認する
	const DirectX::SimpleMath::Vector2 CheckAxisState(std::string axisname)override;
};