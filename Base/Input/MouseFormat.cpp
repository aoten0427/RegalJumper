#include"pch.h"
#include"MouseFormat.h"

MouseFormat::MouseFormat()
	:
	m_fixCursorPos{}
{
	// �O�t���[����Cursor���W�ɏ����l���Z�b�g
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	m_fixCursorPos = cursorPos;

	AddAxis("Mouse");
}

const DirectX::SimpleMath::Vector2 MouseFormat::CheckAxisState(std::string axisname)
{
	if (axisname == "Mouse")
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		AxisState result = { static_cast<float>(cursorPos.x) - m_fixCursorPos.x, static_cast<float>(cursorPos.y) - m_fixCursorPos.y };
		m_fixCursorPos = cursorPos;
		return result;
	}
	return AxisState::Zero;
}
