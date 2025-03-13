#include"pch.h"
#include"InputAxisFormat.h"

void InputAxisFormat::AddAxis(std::string axisname)
{
	m_axis.emplace(axisname);
}

void InputAxisFormat::Remove(std::string axisname)
{
	m_axis.erase(axisname);
}
