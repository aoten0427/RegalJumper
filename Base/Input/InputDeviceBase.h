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

	// ���͂̌��ʂ��i�[����R���e�i
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
				// �{�^����������Ă������̏���
				if (format.second->CheckButtonState(button.second))
				{
					// �O�t���[���Ń{�^����������Ė������
					if (result & KeyState::Free)
					{
						// ���ʂ�Press��ǉ�
						result |= KeyState::Press;
					}
					// �O�t���[���ł��{�^����������Ă����
					else
					{
						// ���ʂ���Press�����O
						result &= ~KeyState::Press;
					}
					// ���ʂ���Free�����O
					result &= ~KeyState::Free;
					// ���ʂ�Hold��ǉ�
					result |= KeyState::Hold;
				}
				// �{�^����������ĂȂ��Ƃ��̏���
				else
				{
					// �O�t���[���Ń{�^����������Ă����
					if (result & KeyState::Hold)
					{
						// ���ʂ�Release��ǉ�
						result |= KeyState::Release;
					}
					// �O�t���[���ł��{�^����������ĂȂ����
					else
					{
						// ���ʂ���Release���폜
						result &= ~KeyState::Release;
					}
					// ���ʂ�Hold��ǉ�
					result &= ~KeyState::Hold;
					// ���ʂ���Free�����O
					result |= KeyState::Free;
				}
				// �{�^�����͂̌��ʂ��R���e�i�Ɋi�[
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

	//���̏���Ԃ�
	const AxisState GetAxisState(std::string axisName)override final
	{
		auto itr = m_axisToResult.find(axisName);
		if (itr != m_axisToResult.end())
		{
			return itr->second;
		}
		return AxisState::Zero;
	}
	//�S�Ă̎��̏���Ԃ�
	const std::unordered_map<std::string, AxisState>& GetAllAxisResult()override final
	{
		return m_axisToResult;
	}
};


