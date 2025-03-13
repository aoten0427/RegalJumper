#pragma once
#include"ParameterBase.h"

class PlayerParameter:public ParameterBase<PlayerParameter>
{
	friend class ParameterBase<PlayerParameter>;
public:
	struct Parameter
	{
		float MASS = 0;//�̏d
		DirectX::SimpleMath::Vector3 COLLIDER_SIZE = DirectX::SimpleMath::Vector3::Zero;//����̑傫��
		DirectX::SimpleMath::Vector3 INITIAL_POSITION = DirectX::SimpleMath::Vector3::Zero;//�����ʒu
		float GRAVITY_GROUND = 0;//�n��d��
		float GRAVITY_AIR = 0;//�󒆏d��
		float GRAVITY_THREAD = 0;//���d��
		float SPEED_GROUND = 0;//�n��ړ����x
		float SPEED_AIR = 0;//�󒆈ړ����x
		float SPEED_THREAD = 0;//���ړ����x
		float FRECTION_GROUND = 0;//�n�㖀�C
		float FRECTION_AIR = 0;//�󒆖��C
		float FRECTION_THREAD = 0;//�����C
		float JUMP_POWER = 0;//�W�����v��
		float RESET_HEIGHT = 0;//���Z�b�g����鍂�x
		float SEARCH_RANGE = 0;//�T�[�`�͈�
		float SEARCH_VISION = 0;//�T�[�`�p�x
	};
private:
	Parameter m_parameter;
private:
	void LoadData()override;
public:
	static const Parameter* PARAMETER();
};