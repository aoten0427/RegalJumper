#include"pch.h"
#include"InputCollector.h"


InputCollector::InputCollector(std::string name)
	:
	m_name{name},
	m_isActive{true},
	m_workToButton{}
{

}

void InputCollector::AddButtonWork(std::string work)
{
	m_workToButton[work];
}

void InputCollector::AddButtonToButtonWork(std::string work, std::string device, std::string button)
{
	m_workToButton[work][device].emplace(button);
}

void InputCollector::RemoveButtonWork(std::string work)
{
	m_workToButton.erase(work);
}

void InputCollector::RemoveButtonFromButtonWork(std::string work, std::string device, std::string button)
{
	m_workToButton[work][device].erase(button);
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& InputCollector::GetAllButtonWork()
{
	return m_workToButton;
}

void InputCollector::AddAxisWork(std::string work)
{
	m_workToAxises[work];
}

void InputCollector::AddAxisToAxisWork(std::string work, std::string device, std::string axis)
{
	m_workToAxises[work][device].emplace(axis);
}

void InputCollector::RemoveAxisWork(std::string work)
{
	m_workToAxises.erase(work);
}

void InputCollector::RemoveAxisFromAxisWork(std::string work, std::string device, std::string axis)
{
	m_workToAxises[work][device].erase(axis);
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& InputCollector::GetAllAxisWork()
{
	return m_workToAxises;
}


