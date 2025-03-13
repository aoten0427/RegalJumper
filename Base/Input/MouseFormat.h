#pragma once
#include"InputAxisFormat.h"

class MouseFormat:public InputAxisFormat
{
private:
	POINT m_fixCursorPos;
public:
	MouseFormat();

	//²‚Ìó‘Ô‚ğŠm”F‚·‚é
	const DirectX::SimpleMath::Vector2 CheckAxisState(std::string axisname)override;
};