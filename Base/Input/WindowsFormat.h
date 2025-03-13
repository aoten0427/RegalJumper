#pragma once
#include"InputDeviceBase.h"
#include"KeyBordFormat.h"
#include"MouseFormat.h"

class WindowsFormat final:public InputDeviceBase<char>
{
private:
public:
	WindowsFormat()
	{
		AddInputButtonFormat<KeyBordFormat>("KeyBord");
		AddInputAxisFormta<MouseFormat>("Mouse");
	}
};