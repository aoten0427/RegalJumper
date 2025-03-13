// ================================================================ 
// �t�@�C���� : Time.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���ԕ\��
// ================================================================
#include"pch.h"
#include"Time.h"
#include"Base/Scene/Scene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
Time::Time(Canvas* canvas):UserInterface(canvas)
	,
	m_count{0},
	m_numbers{},
	m_colon{nullptr},
	m_dot{},
	m_startX{},
	m_positionY{},
	m_size{},
	m_isNone{false}
{
	using namespace DirectX::SimpleMath;
	//�{�̂͏���
	SetActive(false);
	//�ԍ�����
	for (int i = 0; i < 6; i++)
	{
		m_numbers[i] = GetScene()->AddObject<UserInterface>(canvas, "Numbers", 4);
	}
	//�R��������
	m_colon = GetScene()->AddObject<UserInterface>(canvas, "Colon", 4);
	//�h�b�g����
	m_dot = GetScene()->AddObject<UserInterface>(canvas, "Dot", 4);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Time::ObjectUpdate(float deltatime)
{
	if (m_isNone)return;
	UNREFERENCED_PARAMETER(deltatime);
	float absValue = std::fabs(m_count);
	// �����_�ȉ��̌�������������������
	int integerPart = static_cast<int>(absValue);
	// �����������擾
	float decimalPart = absValue - static_cast<float>(integerPart);
	//�����擾
	int minutePart = integerPart / 60;
	//�b���擾
	integerPart %= 60;

	int digits[6];
	digits[0] = minutePart / 10;//10��
	digits[1] = minutePart % 10;//1��
	digits[2] = integerPart / 10;//10�b
	digits[3] = integerPart % 10;//1�b
	decimalPart *= 10;
	digits[4] = static_cast<int>(decimalPart) % 10;//�������
	decimalPart *= 10;
	digits[5] = static_cast<int>(decimalPart) % 10;//�������

	//�l�ɍ��킹�Đ؂���͈͐ݒ�
	for (int i = 0; i < 6; i++)
	{
		m_numbers[i]->SetClipRange(DirectX::SimpleMath::Vector4(digits[i] / 10.0f, 0, 0.1f, 1.0f));
	}
}

/// <summary>
/// �F�ݒ�
/// </summary>
/// <param name="color">�F</param>
void Time::SetTimeColor(const DirectX::SimpleMath::Vector4 color)
{
	for (int i = 0; i < 6; i++)
	{
		m_numbers[i]->SetColor(color);
	}
	m_dot->SetColor(color);
	m_colon->SetColor(color);
}

/// <summary>
/// �l�Ȃ���ݒ�
/// </summary>
/// <param name="none"></param>
void Time::SetNone(bool none)
{
	m_isNone = none;
	if (m_isNone)
	{
		for (int i = 0; i < 6; i++)
		{
			m_numbers[i]->SetTexture("Hyphen");
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			m_numbers[i]->SetTexture("Numbers");
		}
	}
}

/// <summary>
/// �`��ʒu��ݒ�
/// </summary>
void Time::SetView()
{
	using namespace DirectX::SimpleMath;
	for (int i = 0; i < 6; i++)
	{
		//2���ƂɊԂ�������
		float addpos = (i / 2) * m_size.x / 4;
		m_numbers[i]->SetPosition(Vector2(m_startX + i * (m_size.x) + addpos, m_positionY));
		m_numbers[i]->SetSize(m_size);
	}
	//�R�����ʒu�ݒ�
	m_colon->SetPosition(Vector2(m_startX + (3.25f * m_size.x / 2), m_positionY));
	m_colon->SetSize(m_size);
	//�h�b�g�ʒu�ݒ�
	m_dot->SetPosition(Vector2(m_startX + (7.8f * m_size.x / 2), m_positionY));
	m_dot->SetSize(m_size);
}
