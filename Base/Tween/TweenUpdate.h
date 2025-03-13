// ================================================================ 
// �t�@�C���� : TweenUpdate.h
// �쐬�� : �i�R�ɓV
// ���� :  �f�[�^�^�ɉ�����Tween�̏������s��
// ================================================================

#pragma once
#include"ITweenUpdate.h"


template<typename DataType>
class TweenUpdate :public ITweenUpdate
{
private:
	//�ω�����l�̃A�h���X
	DataType* m_origin;
	//�����l
	DataType m_startValue;
	//�I���l
	DataType m_endValue;
	//�ω��l
	DataType m_changeValue;
	//�ω�����(0�`1)
	float m_ratio;
	//�ω�����
	float m_targetTime;
	//�C�[�W���O�^�C�v
	Easing::Ease m_easeType;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="origin">�ύX�f�[�^</param>
	/// <param name="end">�ŏI�l</param>
	/// <param name="time">�ω�����</param>
	TweenUpdate(DataType& origin, DataType end, float time)
		:
		m_origin{&origin},
		m_startValue{origin},
		m_endValue{end},
		m_changeValue{},
		m_ratio{0},
		m_targetTime{ time },
		m_easeType{Easing::Ease::Normal}
	{
		//�ω��ʂ��v�Z
		m_changeValue = m_endValue - m_startValue;
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TweenUpdate()
	{
		m_origin = nullptr;
	}

	//�ω��A�h���X�̊m�F
	bool IsSurvival() { return m_origin; }

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="deltatime">�t���[���o�ߎ���</param>
	/// <returns>�ω��I����</returns>
	bool Update(float deltatime)override
	{
		//���g�m�F
		if (!IsSurvival())return false;
		//�ړI���Ԃɍ��킹�Ċ��������Z
		m_ratio += deltatime / m_targetTime;
		//1�𒴂����ꍇ�߂�
		if (m_ratio >= 1)m_ratio = 1;
		//�l�ϊ�
		*m_origin = static_cast<DataType>(m_startValue + m_changeValue * Easing::Selection(m_easeType, m_ratio));
		//m_ratio��1�̏ꍇ(�ω����I�����)�ꍇtrue��Ԃ�
		if (m_ratio >= 1)return true;
		return false;
	}

	//�C�[�W���O��ސݒ�
	void SetEase(const Easing::Ease& ease)override { m_easeType = ease; }
	//�l�ύX(�����߂�)
	void Yoyo()override
	{
		if (!IsSurvival())return;
		//�����l�ƏI���l�����ւ�
		std::swap(m_startValue, m_endValue);
		//�ω��l��ݒ�
		m_changeValue = m_endValue - m_startValue;
		//����0��
		m_ratio = 0;
	}
	//�l�ύX(�����ݒ�)
	void ReStart()override
	{
		if (!IsSurvival())return;
		//������0��
		m_ratio = 0;
	}
	//�l�ύX(���Z)
	void Incremental()override
	{
		if (!IsSurvival())return;
		//�����l�A�I���l�ɕω��l�����Z
		m_startValue += m_changeValue;
		m_endValue += m_changeValue;
		//������0��
		m_ratio = 0;
	}
	//��������
	void Kill()override
	{
		if (!IsSurvival())return;
		//������1��
		m_ratio = 1;
		//�l���I���l�ɕύX
		*m_origin = m_endValue;
	}
	//���Βl�ɕύX
	void Relative()
	{
		if (!IsSurvival())return;
		//�ω��l���I���l�ɕύX
		if (m_ratio != 0)return;
		m_changeValue = m_endValue;
		m_endValue = *m_origin + m_changeValue;
		m_startValue = *m_origin;
	}
	//�I�_�͕ς����ɏ����l�ύX
	void ReLoad()override
	{
		if (!IsSurvival())return;
		m_startValue = *m_origin;
		m_changeValue = m_endValue - m_startValue;
	}
};


