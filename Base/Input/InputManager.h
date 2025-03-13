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

	// コレクタの名前とインスタンスを紐づけるコンテナ
	std::unordered_map<std::string, std::unique_ptr<InputCollector>> m_nameToCollector;
	// Workと結果を紐づけるコンテナ
	std::unordered_map<std::string, int> m_workToButtonResult;
	std::unordered_map<std::string, AxisState> m_workToAxisResult;

	std::unordered_map<InputData::KEY, std::string> m_keyToWork;
public:
	//デストラクタ
	~InputManager();

	void Update();

	template<typename InputDevice>
	InputDevice* AddDevice(std::string deviceName)
	{
		m_deviceFormats[deviceName] = std::make_unique<InputDevice>();
		return static_cast<InputDevice*>(m_deviceFormats[deviceName].get());
	}

	// コレクタを追加
	InputCollector* AddCollector(std::string collectorName);
	// コレクタを取得
	InputCollector* GetCollector(std::string collectorName) { return m_nameToCollector[collectorName].get(); }


	// ワークの状態を取得
	const int GetButtonWorkState(std::string work) { return m_workToButtonResult[work]; }
	// ボタンワークが何も押されてないならtrue
	const bool IsButtonWorkFree(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Free;
	}
	// ボタンワークが押された瞬間ならtrue
	const bool IsButtonWorkPress(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Press;
	}
	// ボタンワークが押されていればtrue
	const bool IsButtonWorkHold(std::string work)
	{
		return m_workToButtonResult[work] & KeyState::Hold;
	}
	// ボタンワークが離された瞬間ならtrue
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


	// 軸の状態を取得
	const AxisState GetAxisStatus(std::string work)
	{
		return m_workToAxisResult[work];
	}
private:
	void LoadDefaultData();
};