#pragma once
#include"ParameterBase.h"

class PlayerParameter:public ParameterBase<PlayerParameter>
{
	friend class ParameterBase<PlayerParameter>;
public:
	struct Parameter
	{
		float MASS = 0;//体重
		DirectX::SimpleMath::Vector3 COLLIDER_SIZE = DirectX::SimpleMath::Vector3::Zero;//判定の大きさ
		DirectX::SimpleMath::Vector3 INITIAL_POSITION = DirectX::SimpleMath::Vector3::Zero;//初期位置
		float GRAVITY_GROUND = 0;//地上重力
		float GRAVITY_AIR = 0;//空中重力
		float GRAVITY_THREAD = 0;//糸重力
		float SPEED_GROUND = 0;//地上移動速度
		float SPEED_AIR = 0;//空中移動速度
		float SPEED_THREAD = 0;//糸移動速度
		float FRECTION_GROUND = 0;//地上摩擦
		float FRECTION_AIR = 0;//空中摩擦
		float FRECTION_THREAD = 0;//糸摩擦
		float JUMP_POWER = 0;//ジャンプ力
		float RESET_HEIGHT = 0;//リセットされる高度
		float SEARCH_RANGE = 0;//サーチ範囲
		float SEARCH_VISION = 0;//サーチ角度
	};
private:
	Parameter m_parameter;
private:
	void LoadData()override;
public:
	static const Parameter* PARAMETER();
};