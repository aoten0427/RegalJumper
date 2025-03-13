// ================================================================ 
// ファイル名 : Easing.cpp
// 作成者 : 景山碧天
// 説明 :  イージング関数計算
// ================================================================
#include<pch.h>
#include"easing.h"
#include<math.h>
#define M_PI        3.141592f

#include"pch.h"
#include"Easing.h"

Easing::Easing()
{
	
}

/// <summary>
/// イージングタイプ取得
/// </summary>
/// <param name="name">タイプ名</param>
/// <returns>イージング</returns>
Easing::Ease Easing::GetEase(std::string name)
{
	if (name == "Normal")return Ease::Normal;
	if (name == "InSine")return Ease::InSine;
	if (name == "OutSine")return Ease::OutSine;
	if (name == "InOutSine")return Ease::InOutSine;
	if (name == "InQuad")return Ease::InQuad;
	if (name == "OutQuad")return Ease::OutQuad;
	if (name == "InOutQuad")return Ease::InOutQuad;
	if (name == "InCubic")return Ease::InCubic;
	if (name == "OutCubic")return Ease::OutCubic;
	if (name == "InOutCubic")return Ease::InOutCubic;
	if (name == "InQuart")return Ease::InQuart;
	if (name == "OutQuart")return Ease::OutQuart;
	if (name == "InOutQuart")return Ease::InOutQuart;
	if (name == "InQuint")return Ease::InQuint;
	if (name == "OutQuint")return Ease::OutQuint;
	if (name == "InOutQuint")return Ease::InOutQuint;
	if (name == "InExpo")return Ease::InExpo;
	if (name == "OutExpo")return Ease::OutExpo;
	if (name == "InOutExpo")return Ease::InOutExpo;
	if (name == "InCirc")return Ease::InCirc;
	if (name == "OutCirc")return Ease::OutCirc;
	if (name == "InOutCirc")return Ease::InOutCirc;
	if (name == "InBack")return Ease::InBack;
	if (name == "OutBack")return Ease::OutBack;
	if (name == "InOutBack")return Ease::InOutBack;
	if (name == "InElastic")return Ease::InElastic;
	if (name == "OutElastic")return Ease::OutElastic;
	if (name == "InOutElastic")return Ease::InOutElastic;
	if (name == "InBounce")return Ease::InBounce;
	if (name == "OutBounce")return Ease::OutBounce;
	if (name == "InOutBounce")return Ease::InOutBounce;

	return Ease::Normal;
}

////////////////////////////////////////////////////////
//Nomal処理
////////////////////////////////////////////////////////
float Easing::Normal(float& value)
{
	value = Leap(value);
	return value;
}

////////////////////////////////////////////////////////
//Sine処理
////////////////////////////////////////////////////////
float Easing::InSine(float& value)
{
	value = Leap(value);
	return (1 - cosf((value * M_PI) / 2));
}

float Easing::OutSine(float& value)
{
	value = Leap(value);
	return (sinf((value * M_PI) / 2));
}

float Easing::InOutSine(float& value)
{
	value = Leap(value);
	return (-(cos(M_PI * value) - 1) / 2);
}

////////////////////////////////////////////////////////
//Quad処理
////////////////////////////////////////////////////////
float Easing::InQuad(float& value)
{
	value = Leap(value);
	return (value * value);
}

float Easing::OutQuad(float& value)
{
	value = Leap(value);
	return (1 - (1 - value) * (1 - value));
}

float Easing::InOutQuad(float& value)
{
	value = Leap(value);
	return (value < 0.5 ? 2 * value * value :
		1 - powf(-2 * value + 2, 2) / 2);
}

////////////////////////////////////////////////////////
//Cubic処理
////////////////////////////////////////////////////////
float Easing::InCubic(float& value)
{
	value = Leap(value);
	return (value * value * value);
}

float Easing::OutCubic(float& value)
{
	value = Leap(value);
	return (1 - powf(1 - value, 3));
}

float Easing::InOutCubic(float& value)
{
	value = Leap(value);
	return (value < 0.5 ? 4 * value * value * value :
		1 - powf(-2 * value + 2, 3) / 2);
}

////////////////////////////////////////////////////////
//Quart処理
////////////////////////////////////////////////////////
float Easing::InQuart(float& value)
{
	value = Leap(value);
	return (value * value * value * value);
}

float Easing::OutQuart(float& value)
{
	value = Leap(value);
	return (1 - powf(1 - value, 4));
}

float Easing::InOutQuart(float& value)
{
	value = Leap(value);
	return (value < 0.5 ? 8 * value * value * value * value :
		1 - powf(-2 * value + 2, 4) / 2);
}

////////////////////////////////////////////////////////
//Quint処理
////////////////////////////////////////////////////////
float Easing::InQuint(float& value)
{
	value = Leap(value);
	return (powf(value, 5));
}

float Easing::OutQuint(float& value)
{
	value = Leap(value);
	return (1 - powf(1 - value, 5));
}

float Easing::InOutQuint(float& value)
{
	value = Leap(value);
	return (value < 0.5 ? 16 * value * value * value * value * value :
		1 - powf(-2 * value + 2, 5) / 2);
}

////////////////////////////////////////////////////////
//Expo処理
////////////////////////////////////////////////////////
float Easing::InExpo(float& value)
{
	value = Leap(value);
	return (value == 0 ? 0 : powf(2, 10 * value - 10));
}

float Easing::OutExpo(float& value)
{
	value = Leap(value);
	return (value == 1 ? 1 : 1 - powf(2, -10 * value));
}

float Easing::InOutExpo(float& value)
{
	value = Leap(value);
	return (value == 0
		? 0
		: value == 1
		? 1
		: value < 0.5 ? powf(2, 20 * value - 10) / 2
		: (2 - powf(2, -20 * value + 10)) / 2);
}

////////////////////////////////////////////////////////
//Circ処理
////////////////////////////////////////////////////////
float Easing::InCirc(float& value)
{
	value = Leap(value);
	return (1 - sqrtf(1 - powf(value, 2)));
}

float Easing::OutCirc(float& value)
{
	value = Leap(value);
	return (sqrtf(1 - powf(value - 1, 2)));
}

float Easing::InOutCirc(float& value)
{
	value = Leap(value);
	return (value < 0.5
		? (1 - sqrt(1 - powf(2 * value, 2))) / 2
		: (sqrt(1 - powf(-2 * value + 2, 2)) + 1) / 2);
}

////////////////////////////////////////////////////////
//Back処理
////////////////////////////////////////////////////////
float Easing::InBack(float& value)
{
	value = Leap(value);

	float c1 = 1.70158f;
	float c3 = c1 + 1;
	return (c3 * value * value * value - c1 * value * value);
}

float Easing::OutBack(float& value)
{
	value = Leap(value);
	float c1 = 0.90158f;
	float c3 = c1 + 1;
	return (1 + c3 * powf(value - 1, 3) + c1 * powf(value - 1, 2));
}

float Easing::InOutBack(float& value)
{
	value = Leap(value);
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;
	return (value < 0.5
		? (powf(2 * value, 2) * ((c2 + 1) * 2 * value - c2)) / 2
		: (powf(2 * value - 2, 2) * ((c2 + 1) * (value * 2 - 2) + c2) + 2) / 2);
}

////////////////////////////////////////////////////////
//Elastic処理
////////////////////////////////////////////////////////
float Easing::InElastic(float& value)
{
	value = Leap(value);
	float c4 = static_cast<float>(2 * M_PI) / 3;
	return (value == 0
		? 0
		: value == 1
		? 1
		: -powf(2, 10 * value - 10) * sinf((value * 10 - 10.75f) * c4));
}

float Easing::OutElastic(float& value)
{
	value = Leap(value);
	float c4 = static_cast<float>(2 * M_PI) / 3;
	return (value == 0
		? 0
		: value == 1
		? 1
		: powf(2, -10 * value) * sinf((value * 10 - 0.75f) * c4) + 1);
}

float Easing::InOutElastic(float& value)
{
	value = Leap(value);
	float c5 = static_cast<float>(2 * M_PI) / 4.5;
	return (value == 0
		? 0
		: value == 1
		? 1
		: value < 0.5
		? -(powf(2, 20 * value - 10) * sinf((20 * value - 11.125f) * c5)) / 2
		: (powf(2, -20 * value + 10) * sinf((20 * value - 11.125f) * c5)) / 2 + 1);
}

////////////////////////////////////////////////////////
//Bounce処理
////////////////////////////////////////////////////////
float Easing::InBounce(float& value)
{
	value = Leap(value);
	float n1 = 7.5625f;
	float d1 = 2.75f;
	float value2 = 1 - value;
	if (value2 < 1 / d1) {
		return (1 - (n1 * value2 * value2));
	}
	else if (value2 < 2 / d1) {
		return (1 - (n1 * powf((value2 - 1.5f / d1), 2) + 0.75f));
	}
	else if (value2 < 2.5 / d1) {
		return (1 - (n1 * powf((value2 - 2.25f / d1), 2) + 0.9375f));
	}
	else {
		return (1 - (n1 * powf((value2 - 2.625f / d1), 2) + 0.984375f));
	}
}

float Easing::OutBounce(float& value)
{
	value = Leap(value);
	float n1 = 7.5625f;
	float d1 = 2.75f;

	if (value < 1 / d1) {
		return (n1 * value * value);
	}
	else if (value < 2 / d1) {
		return (n1 * powf((value - 1.5f / d1), 2) + 0.75f);
	}
	else if (value < 2.5 / d1) {
		return (n1 * powf((value - 2.25f / d1), 2) + 0.9375f);
	}
	else {
		return (n1 * powf((value - 2.625f / d1), 2) + 0.984375f);
	}
}

float Easing::InOutBounce(float& value)
{
	value = Leap(value);
	float n1 = 7.5625f;
	float d1 = 2.75f;
	float value3 = 1 - 2 * value;
	float value4 = 2 * value - 1;
	float re1;
	if (value3 < 1 / d1) {
		re1 = ((1 - (n1 * value3 * value3)) / 2);
	}
	else if (value3 < 2 / d1) {
		re1 = ((1 - (n1 * powf((value3 - 1.5f / d1), 2) + 0.75f)) / 2);
	}
	else if (value3 < 2.5 / d1) {
		re1 = ((1 - (n1 * powf((value3 - 2.25f / d1), 2) + 0.9375f)) / 2);
	}
	else {
		re1 = ((1 - (n1 * powf((value3 - 2.625f / d1), 2) + 0.984375f)) / 2);
	}

	float re2;
	if (value4 < 1 / d1) {
		re2 = ((1 + (n1 * value4 * value4)) / 2);
	}
	else if (value4 < 2 / d1) {
		re2 = ((1 + (n1 * powf((value4 - 1.5f / d1), 2) + 0.75f)) / 2);
	}
	else if (value4 < 2.5 / d1) {
		re2 = ((1 + (n1 * powf((value4 - 2.25f / d1), 2) + 0.9375f)) / 2);
	}
	else {
		re2 = ((1 + (n1 * powf((value4 - 2.625f / d1), 2) + 0.984375f)) / 2);
	}

	return value < 0.5
		? re1
		: re2;
}

////////////////////////////////////////////////////////
//選択処理
////////////////////////////////////////////////////////
float Easing::Selection(Ease easy, float& value)
{
	switch (easy)
	{
	case Easing::Ease::Normal:
		return Normal(value);
		break;
	case Easing::Ease::InSine:
		return InSine(value);
		break;
	case Easing::Ease::OutSine:
		return OutSine(value);
		break;
	case Easing::Ease::InOutSine:
		return InOutSine(value);
		break;
	case Easing::Ease::InQuad:
		return InQuad(value);
		break;
	case Easing::Ease::OutQuad:
		return OutQuad(value);
		break;
	case Easing::Ease::InOutQuad:
		return InOutQuad(value);
		break;
	case Easing::Ease::InCubic:
		return InCubic(value);
		break;
	case Easing::Ease::OutCubic:
		return OutCubic(value);
		break;
	case Easing::Ease::InOutCubic:
		return InOutCubic(value);
		break;
	case Easing::Ease::InQuart:
		return InQuart(value);
		break;
	case Easing::Ease::OutQuart:
		return OutQuart(value);
		break;
	case Easing::Ease::InOutQuart:
		return InOutQuart(value);
		break;
	case Easing::Ease::InQuint:
		return InQuint(value);
		break;
	case Easing::Ease::OutQuint:
		return OutQuint(value);
		break;
	case Easing::Ease::InOutQuint:
		return InOutQuint(value);
		break;
	case Easing::Ease::InExpo:
		return InExpo(value);
		break;
	case Easing::Ease::OutExpo:
		return OutExpo(value);
		break;
	case Easing::Ease::InOutExpo:
		return InOutExpo(value);
		break;
	case Easing::Ease::InCirc:
		return InCirc(value);
		break;
	case Easing::Ease::OutCirc:
		return OutCirc(value);
		break;
	case Easing::Ease::InOutCirc:
		return InOutCirc(value);
		break;
	case Easing::Ease::InBack:
		return InBack(value);
		break;
	case Easing::Ease::OutBack:
		return OutBack(value);
		break;
	case Easing::Ease::InOutBack:
		return InOutBack(value);
		break;
	case Easing::Ease::InElastic:
		return InElastic(value);
		break;
	case Easing::Ease::OutElastic:
		return OutElastic(value);
		break;
	case Easing::Ease::InOutElastic:
		return InOutElastic(value);
		break;
	case Easing::Ease::InBounce:
		return InBounce(value);
		break;
	case Easing::Ease::OutBounce:
		return OutBounce(value);
		break;
	case Easing::Ease::InOutBounce:
		return InOutBounce(value);
		break;
	default:
		return 0;
		break;
	}
}


float Easing::Leap(float value)
{
	return std::min(1.0f, std::max(value, 0.0f));
}
