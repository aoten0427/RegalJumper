// ================================================================ 
// �t�@�C���� : Time.h
// �쐬�� : �i�R�ɓV
// ���� :  ���ԕ\��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time :public UserInterface
{
public:
	//�l��ύX
	void SetCount(float count) { m_count = count; }
	//���[��ݒ�
	void SetStartX(float startx) { m_startX = startx; SetView(); }
	//������ݒ�
	void SetPositionY(float positiony) { m_positionY = positiony; SetView(); }
	//�傫����ݒ�
	void SetSize(const DirectX::SimpleMath::Vector2& size) { m_size = size; SetView(); }
private:
	//����
	float m_count;
	//����
	UserInterface* m_numbers[6];
	//�R����
	UserInterface* m_colon;
	//�h�b�g
	UserInterface* m_dot;
	//�J�n�ʒu
	float m_startX;
	//Y���W
	float m_positionY;
	//�T�C�Y
	DirectX::SimpleMath::Vector2 m_size;
	//�l�Ȃ�����
	bool m_isNone;
public:
	//�R���X�g���N�^
	Time(Canvas* canvas);
	//�f�X�g���N�^
	~Time()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
	//�F�ݒ�
	void SetTimeColor(const DirectX::SimpleMath::Vector4 color);
	//�l�Ȃ���ݒ�
	void SetNone(bool none);
private:
	//�`��ʒu��ݒ�
	void SetView();
};