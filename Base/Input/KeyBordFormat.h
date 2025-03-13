#pragma once
#include"InputButtonFormat.h"

class KeyBordFormat :public InputButtonFormat<char>
{
private:
public:
	KeyBordFormat();
	~KeyBordFormat() = default;

	const bool CheckButtonState(char cord)override;
};