#pragma once
#include"InputData.h"

class InputAxisFormat
{
private:
	std::unordered_set<std::string> m_axis;

	std::unordered_map<std::string, AxisState> m_axisToResult;
public:
	InputAxisFormat() = default;
	virtual ~InputAxisFormat() = default;

	void AddAxis(std::string axisname);

	void Remove(std::string axisname);

	std::unordered_set<std::string>& GetAllAxis() { return m_axis; }

	//²‚Ìó‘Ô‚ğŠm”F‚·‚é
	virtual const DirectX::SimpleMath::Vector2 CheckAxisState(std::string axisname) = 0;
};