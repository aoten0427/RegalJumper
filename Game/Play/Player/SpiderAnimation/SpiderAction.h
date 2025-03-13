// ================================================================ 
// ファイル名 : SpiderAction.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛の空中機動データ
// ================================================================

#pragma once
#include<random>

struct SpiderAction
{
	virtual ~SpiderAction() = default;	
	//軸
	DirectX::SimpleMath::Vector3 m_axis;
	//スロット番号
	int m_slot = 0;
	//優先度
	int m_priority = 0;
	//回転条件
	virtual bool RotationConditions(DirectX::SimpleMath::Vector3 direction,DirectX::SimpleMath::Vector3 velocity) = 0;

	float Dot(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
	float Cross(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};

////////////////////////
/////     X軸
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
/////     Y軸
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
/////     X,Y軸
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
/////     Z軸
///////////////////////
struct Action7 :public SpiderAction
{
	Action7();
	~Action7() = default;
	bool RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity);
};