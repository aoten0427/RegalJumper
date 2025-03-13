#include"pch.h"
#include"InputManager.h"
#include"WindowsFormat.h"
#include"nlohmann/json.hpp"

InputManager::InputManager()
{
	AddDevice<WindowsFormat>("Window");

	
	LoadDefaultData();

}

InputManager::~InputManager()
{
}

void InputManager::Update()
{

	for (auto& device : m_deviceFormats)
	{
		device.second->Update();
	}

	m_workToButtonResult.clear();
	m_workToAxisResult.clear();

	for (auto& collector : m_nameToCollector)
	{
		if (!collector.second->GetIsActive())continue;

		for (auto& work : collector.second->GetAllButtonWork())
		{
			for (auto& deviceToButtons : work.second)
			{
				for (auto& button : deviceToButtons.second)
				{
					m_workToButtonResult[work.first] |= m_deviceFormats[deviceToButtons.first]->GetButtonState(button);
				}
			}
		}


		for (auto& work : collector.second->GetAllAxisWork())
		{
			for (auto& deviceToAxis : work.second)
			{
				for (auto& axis : deviceToAxis.second)
				{
					m_workToAxisResult[work.first] = m_deviceFormats[deviceToAxis.first]->GetAxisState(axis);
				}
				
			}
		}
	}
}

InputCollector* InputManager::AddCollector(std::string collectorName)
{
	m_nameToCollector[collectorName] = std::make_unique<InputCollector>(collectorName);
	return m_nameToCollector[collectorName].get();
}

void InputManager::LoadDefaultData()
{
	//JSONファイル選択
	std::string file = "Resources/JSON/Input/Default.json";

	//デフォルト機構を作成
	InputCollector* defaultCollect = AddCollector("default");

	defaultCollect->AddAxisToAxisWork("Mouse", "Window", "Mouse");

	//読み込み
	std::ifstream ifs(file.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		size_t num = m_json["Default"].size();
		for (int i = 0; i < num; i++)
		{
			std::string work = m_json["Default"][i]["Work"];
			std::string device = m_json["Default"][i]["Device"];
			std::string button = m_json["Default"][i]["Button"];
			defaultCollect->AddButtonToButtonWork(work, device, button);
			m_keyToWork[static_cast<InputData::KEY>(i)] = work;
		}

	}
}
