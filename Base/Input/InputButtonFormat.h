#pragma once
#include"InputData.h"

template<typename KeyCord>
class InputButtonFormat
{
private:
	std::unordered_map<std::string, KeyCord> m_buttonNameToKeyCored;
public:
	InputButtonFormat() = default;
	virtual ~InputButtonFormat() = default;

	void AddButton(std::string name, KeyCord cord)
	{
		m_buttonNameToKeyCored[name] = cord;
	}

	void RemoveButton(std::string name)
	{
		m_buttonNameToKeyCored.erase(name);
	}

	// ボタンの状態を確認する関数を実装するための仮想関数
	virtual const bool CheckButtonState(KeyCord cord) = 0;

	const std::unordered_map<std::string, KeyCord>& GetButtonNameToKeyCode()
	{
		return m_buttonNameToKeyCored;
	}
};


