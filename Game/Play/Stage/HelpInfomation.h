// ================================================================ 
// �t�@�C���� : HelpInfomation.h
// �쐬�� : �i�R�ɓV
// ���� :  �w���v���e
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Tween;

class HelpInfomation :public UserInterface
{
public:
	//�w���v���e
	enum class INFOMATION
	{
		SHOT,
		MOVE,
		JUMP,
		SHOT2
	};
private:
	//�w�i
	UserInterface* m_bg;
	//�傫��
	DirectX::SimpleMath::Vector2 m_size;
	//�ω��pTween
	Tween* m_tween;
public:
	//�R���X�g���N�^
	HelpInfomation(Canvas* canvas,INFOMATION infomation);
	//�f�X�g���N�^
	~HelpInfomation()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
	//�J��
	void Open();
	//����
	void Close();
};