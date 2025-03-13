// ================================================================ 
// �t�@�C���� : Easing.h
// �쐬�� : �i�R�ɓV
// ���� :  �C�[�W���O�֐��v�Z
// ================================================================
#pragma once

class Easing {
private:

public:
	//�C�[�W���O�^�C�v
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

	//���O�ɑ΂��ă^�C�v��Ԃ�
	static Ease GetEase(std::string name);

	//��������
	static float Normal(float& value);

	//Sine����
	static float InSine(float& value);
	static float OutSine(float& value);
	static float InOutSine(float& value);

	//Quad����
	static float InQuad(float& value);
	static float OutQuad(float& value);
	static float InOutQuad(float& value);

	//Cubic����
	static float InCubic(float& value);
	static float OutCubic(float& value);
	static float InOutCubic(float& value);

	//Quart����
	static float InQuart(float& value);
	static float OutQuart(float& value);
	static float InOutQuart(float& value);

	//Quint����
	static float InQuint(float& value);
	static float OutQuint(float& value);
	static float InOutQuint(float& value);

	//Expo����
	static float InExpo(float& value);
	static float OutExpo(float& value);
	static float InOutExpo(float& value);

	//Circ����
	static float InCirc(float& value);
	static float OutCirc(float& value);
	static float InOutCirc(float& value);

	//Back����
	static float InBack(float& value);
	static float OutBack(float& value);
	static float InOutBack(float& value);

	//Elastic����
	static float InElastic(float& value);
	static float OutElastic(float& value);
	static float InOutElastic(float& value);

	//Bounce����
	static float InBounce(float& value);
	static float OutBounce(float& value);
	static float InOutBounce(float& value);

	//�Ή��C�[�W���O����
	static float Selection(Ease easy, float& value);
private:

	static float Leap(float value);
};