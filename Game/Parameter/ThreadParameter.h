#pragma once
#include"ParameterBase.h"

class ThreadParameter :public ParameterBase<ThreadParameter>
{
	friend class ParameterBase<ThreadParameter>;
public:
	struct Parameter
	{
		float INITIAL_POWER = 0;//���̏����ɗ^�����
		float INITIAL_POWER_TIP = 0;//���ˎ��Ɏ��̐�[�ɗ^�����
		float EXTEND_SPEED = 0;//����L�΂��X�s�[�h
		float DELETE_TIME = 0;//���������鎞��
		float ADD_POWER = 0;//���˒��ɗ^�����
		float SHRINK_VALUE_BEGIN = 0;//�k�ރX�s�[�h�̏����l
		float SHRINK_VALUE_END = 0;//�k�ރX�s�[�h�̍ŏI�l
		float SHRINK_SPEED = 0;//�X�s�[�h���ω����鑁��
		std::string SHRINK_EASING = "Normal";//�ω����̃C�[�W���O
	};
private:
	Parameter m_parameter;
private:
	void LoadData()override;
public:
	static const Parameter* PARAMETER();
};