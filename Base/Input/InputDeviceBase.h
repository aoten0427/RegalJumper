#pragma once
#include"IInputDeviceBase.h"
#include"InputButtonFormat.h"
#include"InputAxisFormat.h"

template<typename KeyCord>
class InputDeviceBase :public IInputDeviceBase
{
private:
	std::unordered_map<std::string, std::unique_ptr<InputButtonFormat<KeyCord>>> m_buttonFormats;
	std::unordered_map<std::string, std::unique_ptr<InputAxisFormat>> m_axisFormats;

	// 入力の結果を格納するコンテナ
	std::unordered_map<std::string,int> m_buttonToResult;
	std::unordered_map<std::string,AxisState> m_axisToResult;
public:
	InputDeviceBase() = default;
	virtual ~InputDeviceBase() override = default;

	template<typename FormatType>
	void AddInputButtonFormat(std::string formatName)
	{
		m_buttonFormats[formatName] = std::make_unique<FormatType>();
	}

	template<typename FormatType>
	void AddInputAxisFormta(std::string formatName)
	{
		m_axisFormats[formatName] = std::make_unique<FormatType>();
	}

	void Update()override final
	{
		for (auto& format : m_buttonFormats)
		{
			for (auto& button : format.second->GetButtonNameToKeyCode())
			{
				int result = m_buttonToResult[button.first];
				// ボタンが押されていた時の処理
				if (format.second->CheckButtonState(button.second))
				{
					// 前フレームでボタンが押されて無ければ
					if (result & KeyState::Free)
					{
						// 結果にPressを追加
						result |= KeyState::Press;
					}
					// 前フレームでもボタンが押されていれば
					else
					{
						// 結果からPressを除外
						result &= ~KeyState::Press;
					}
					// 結果からFreeを除外
					result &= ~KeyState::Free;
					// 結果にHoldを追加
					result |= KeyState::Hold;
				}
				// ボタンが押されてないときの処理
				else
				{
					// 前フレームでボタンが押されていれば
					if (result & KeyState::Hold)
					{
						// 結果にReleaseを追加
						result |= KeyState::Release;
					}
					// 前フレームでもボタンが押されてなければ
					else
					{
						// 結果からReleaseを削除
						result &= ~KeyState::Release;
					}
					// 結果にHoldを追加
					result &= ~KeyState::Hold;
					// 結果からFreeを除外
					result |= KeyState::Free;
				}
				// ボタン入力の結果をコンテナに格納
				m_buttonToResult[button.first] = result;
			}
		}

		for (auto& format : m_axisFormats)
		{
			for (auto& axis : format.second->GetAllAxis())
			{
				m_axisToResult[axis] = format.second->CheckAxisState(axis);
			}
		}
	}

	int GetButtonState(std::string buttonName)override final
	{
		auto itr = m_buttonToResult.find(buttonName);
		if (itr != m_buttonToResult.end())
		{
			return itr->second;
		}
		return 0;
	}

	const bool IsButtonFree(std::string buttonName)override final
	{
		auto itr = m_buttonToResult.find(buttonName);
		if (itr != m_buttonToResult.end())
		{
			return itr->second & KeyState::Free;
		}
		return false;
	}

	const bool IsButtonPress(std::string buttonName)override final
	{
		auto itr = m_buttonToResult.find(buttonName);
		if (itr != m_buttonToResult.end())
		{
			return itr->second & KeyState::Press;
		}
		return false;
	}

	const bool IsButtonHold(std::string buttonName)override final
	{
		auto itr = m_buttonToResult.find(buttonName);
		if (itr != m_buttonToResult.end())
		{
			return itr->second & KeyState::Hold;
		}
		return false;
	}

	const bool IsButtonRelease(std::string buttonName)override final
	{
		auto itr = m_buttonToResult.find(buttonName);
		if (itr != m_buttonToResult.end())
		{
			return itr->second & KeyState::Release;
		}
		return false;
	}

	const std::unordered_map<std::string,int>& GetAllButtonResult()override final
	{
		return m_buttonToResult;
	}

	//軸の情報を返す
	const AxisState GetAxisState(std::string axisName)override final
	{
		auto itr = m_axisToResult.find(axisName);
		if (itr != m_axisToResult.end())
		{
			return itr->second;
		}
		return AxisState::Zero;
	}
	//全ての軸の情報を返す
	const std::unordered_map<std::string, AxisState>& GetAllAxisResult()override final
	{
		return m_axisToResult;
	}
};


