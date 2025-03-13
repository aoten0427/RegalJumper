#pragma once
#include"InputData.h"
#include<string>
#include<unordered_map>

class IInputDeviceBase
{
public:
	virtual ~IInputDeviceBase() = default;

	virtual void Update() = 0;

	virtual int GetButtonState(std::string buttonName) = 0;
	virtual const bool IsButtonFree(std::string buttonName) = 0;
	virtual const bool IsButtonPress(std::string buttonName) = 0;
	virtual const bool IsButtonHold(std::string buttonName) = 0;
	virtual const bool IsButtonRelease(std::string buttonName) = 0;
	virtual const std::unordered_map<std::string, int>& GetAllButtonResult() = 0;
	virtual const AxisState GetAxisState(std::string axisName) = 0;
	virtual const std::unordered_map<std::string, AxisState>& GetAllAxisResult() = 0;
};