#pragma once
#include"InputAxisFormat.h"

class MouseFormat:public InputAxisFormat
{
private:
	POINT m_fixCursorPos;
public:
	MouseFormat();

	//���̏�Ԃ��m�F����
	const DirectX::SimpleMath::Vector2 CheckAxisState(std::string axisname)override;
};