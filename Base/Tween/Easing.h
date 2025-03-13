// ================================================================ 
// ファイル名 : Easing.h
// 作成者 : 景山碧天
// 説明 :  イージング関数計算
// ================================================================
#pragma once

class Easing {
private:

public:
	//イージングタイプ
	enum class Ease
	{
		Normal,

		InSine, OutSine, InOutSine,

		InQuad, OutQuad, InOutQuad,

		InCubic, OutCubic, InOutCubic,

		InQuart, OutQuart, InOutQuart,

		InQuint, OutQuint, InOutQuint,

		InExpo, OutExpo, InOutExpo,

		InCirc, OutCirc, InOutCirc,

		InBack, OutBack, InOutBack,

		InElastic, OutElastic, InOutElastic,

		InBounce, OutBounce, InOutBounce
	};

public:
	Easing();
	~Easing() = default;

	//名前に対してタイプを返す
	static Ease GetEase(std::string name);

	//直線処理
	static float Normal(float& value);

	//Sine処理
	static float InSine(float& value);
	static float OutSine(float& value);
	static float InOutSine(float& value);

	//Quad処理
	static float InQuad(float& value);
	static float OutQuad(float& value);
	static float InOutQuad(float& value);

	//Cubic処理
	static float InCubic(float& value);
	static float OutCubic(float& value);
	static float InOutCubic(float& value);

	//Quart処理
	static float InQuart(float& value);
	static float OutQuart(float& value);
	static float InOutQuart(float& value);

	//Quint処理
	static float InQuint(float& value);
	static float OutQuint(float& value);
	static float InOutQuint(float& value);

	//Expo処理
	static float InExpo(float& value);
	static float OutExpo(float& value);
	static float InOutExpo(float& value);

	//Circ処理
	static float InCirc(float& value);
	static float OutCirc(float& value);
	static float InOutCirc(float& value);

	//Back処理
	static float InBack(float& value);
	static float OutBack(float& value);
	static float InOutBack(float& value);

	//Elastic処理
	static float InElastic(float& value);
	static float OutElastic(float& value);
	static float InOutElastic(float& value);

	//Bounce処理
	static float InBounce(float& value);
	static float OutBounce(float& value);
	static float InOutBounce(float& value);

	//対応イージング処理
	static float Selection(Ease easy, float& value);
private:

	static float Leap(float value);
};