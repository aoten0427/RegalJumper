// ================================================================ 
// �t�@�C���� : SpiderAction.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̋󒆋@���f�[�^
// ================================================================

#pragma once
#include<random>

struct SpiderAction
{
	virtual ~SpiderAction() = default;	
	//��
	DirectX::SimpleMath::Vector3 m_axis;
	//�X���b�g�ԍ�
	int m_slot = 0;
	//�D��x
	int m_priority = 0;
	//��]����
	virtual bool RotationConditions(DirectX::SimpleMath::Vector3 direction,DirectX::SimpleMath::Vector3 velocity) = 0;

	float Dot(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
	float Cross(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};

////////////////////////
/////     X��
///////////////////////
struct Action1:public SpiderAction
{
	Action1();
	~Action1() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};

struct Action2 :public SpiderAction
{
	Action2();
	~Action2() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};

////////////////////////
/////     Y��
///////////////////////
struct Action3 :public SpiderAction
{
	Action3();
	~Action3() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};

struct Action4 :public SpiderAction
{
	Action4();
	~Action4() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};


////////////////////////
/////     X,Y��
///////////////////////
struct Action5 :public SpiderAction
{
	Action5();
	~Action5() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};

struct Action6 :public SpiderAction
{
	Action6();
	~Action6() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};


////////////////////////
/////     Z��
///////////////////////
struct Action7 :public SpiderAction
{
	Action7();
	~Action7() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};