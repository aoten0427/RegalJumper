#pragma once
#include"Base/MyLibraries/Singleton.h"
#include"InputCollector.h"
#include"IInputDeviceBase.h"
#include"InputDeviceBase.h"

class InputManager :public Singleton<InputManager>
{
	friend class Singleton<InputManager>;
private:
	InputManager();
private:
	std::unordered_map<std::string, std::unique_ptr<IInputDeviceBase>> m_deviceFormats;

	// �R���N�^�̖��O�ƃC���X�^���X��R�Â���R���e�i
	std::unordered_map<std::string, std::unique_ptr<InputCollector>> m_nameToCollector;
	// Work�ƌ��ʂ�R�Â���R���e�i
	std::unordered_map<std::string, int> m_workToButtonResult;
	std::unordered_map<std::string, AxisState> m_workToAxisResult;

	std::unordered_map<InputData::KEY, std::string> m_keyToWork;
public:
	//�f�X�g���N�^
	~InputManager();

	void Update();

	template<typename InputDevice>
	InputDevice* AddDevice(std::string deviceName)
	{
		m_deviceFormats[deviceName] = std::make_unique<InputDevice>();
		return static_cast<InputDevice*>(m_deviceFormats[deviceName].get());
	}

	// �R���N�^��ǉ�
	InputCollector* AddCollector(std::string collectorName);
	// �R���N�^���擾
	InputCollector* GetCollector(std::string collectorName) { return m_nameToCollector[collectorName].get(); }


	// ���[�N�̏�Ԃ��擾
	const int GetButtonWorkState(std::string work) { return m_workToButtonResult[work]; }
	// �{�^�����[�N������������ĂȂ��Ȃ�true
	const bool IsButtonWorkFree(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Free;
	}
	// �{�^�����[�N�������ꂽ�u�ԂȂ�true
	const bool IsButtonWorkPress(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Press;
	}
	// �{�^�����[�N��������Ă����true
	const bool IsButtonWorkHold(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Hold;
	}
	// �{�^�����[�N�������ꂽ�u�ԂȂ�true
	const bool IsButtonWorkRelease(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Release;
	}

	const bool IsButtonFree(InputData::KEY key)
	{
		return IsButtonWorkFree(m_keyToWork[key]);
	}
	const bool IsButtonPress(InputData::KEY key)
	{
		return IsButtonWorkPress(m_keyToWork[key]);
	}
	const bool IsButtonHold(InputData::KEY key)
	{
		return IsButtonWorkHold(m_keyToWork[key]);
	}
	const bool IsButtonRelease(InputData::KEY key)
	{
		return IsButtonWorkRelease(m_keyToWork[key]);
	}


	// ���̏�Ԃ��擾
	const AxisState GetAxisStatus(std::string work)
	{
		return m_workToAxisResult[work];
	}
private:
	void LoadDefaultData();
};