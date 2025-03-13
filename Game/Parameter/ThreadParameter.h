#pragma once
#include"ParameterBase.h"

class ThreadParameter :public ParameterBase<ThreadParameter>
{
	friend class ParameterBase<ThreadParameter>;
public:
	struct Parameter
	{
		float INITIAL_POWER = 0;//糸の初期に与える力
		float INITIAL_POWER_TIP = 0;//発射時に糸の先端に与える力
		float EXTEND_SPEED = 0;//糸を伸ばすスピード
		float DELETE_TIME = 0;//糸が消える時間
		float ADD_POWER = 0;//発射中に与える力
		float SHRINK_VALUE_BEGIN = 0;//縮むスピードの初期値
		float SHRINK_VALUE_END = 0;//縮むスピードの最終値
		float SHRINK_SPEED = 0;//スピードが変化する早さ
		std::string SHRINK_EASING = "Normal";//変化時のイージング
	};
private:
	Parameter m_parameter;
private:
	void LoadData()override;
public:
	static const Parameter* PARAMETER();
};