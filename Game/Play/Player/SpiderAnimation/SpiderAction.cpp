// ================================================================ 
// ファイル名 : SpiderAction.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛の空中機動データ
// ================================================================

#include"pch.h"
#include"SpiderAction.h"


float SpiderAction::Dot(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	direction.Normalize();
	velocity.Normalize();
	return direction.x * velocity.x + direction.z * velocity.z;
}

float SpiderAction::Cross(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	direction.Normalize();
	velocity.Normalize();
	return direction.x * velocity.z - direction.z * velocity.x;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action1::Action1()
{
	m_axis = DirectX::SimpleMath::Vector3::UnitX;
	m_priority = 1;
}

/// <summary>
/// 速度Yが1.3以上でtrue
/// </summary>
/// <returns></returns>
bool Action1::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	UNREFERENCED_PARAMETER(direction);
	return velocity.y > 1.30f;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action2::Action2()
{
	m_axis = -DirectX::SimpleMath::Vector3::UnitX;
}

/// <summary>
/// Y軸を除いた速度が1.8以上かつ向きと速度の内積が0.8以上
/// </summary>
/// <returns></returns>
bool Action2::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	velocity.y = 0;
	if (velocity.Length() < 1.8f)return false;
	return Dot(direction,velocity) > 0.8f;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action3::Action3()
{
	m_axis = DirectX::SimpleMath::Vector3::UnitY;
	m_slot = 1;
	m_priority = 1;
}


/// <summary>
/// 向きと速度の内積が0以上かつ速度が(0.2,1.0,0.2)以上
/// </summary>
/// <returns></returns>
bool Action3::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	if (Cross(direction,velocity) > 0)return false;
	return abs(velocity.x) > 0.2f && velocity.y > 1.00f &&  abs(velocity.z) > 0.2f;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action4::Action4()
{
	m_axis = -DirectX::SimpleMath::Vector3::UnitY;
	m_slot = 1;
	m_priority = 1;
}

/// <summary>
/// 向きと速度の内積が0以下かつ速度が(0.2,1.0,0.2)以上
/// </summary>
/// <returns></returns>
bool Action4::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	if (Cross(direction, velocity) < 0)return false;
	return velocity.y > 1.00f && abs(velocity.x) > 0.2f && abs(velocity.z) > 0.2f;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action5::Action5()
{
	m_axis = DirectX::SimpleMath::Vector3(1, 0.2f, 0);
	m_axis.Normalize();
	m_slot = 1;
}

/// <summary>
/// 向きと速度の外積が0以上かつ速度x,zの大きさが0.3以上
/// </summary>
/// <returns></returns>
bool Action5::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	if (Cross(direction, velocity) > 0)return false;
	return abs(velocity.x) > 0.3f && abs(velocity.z) > 0.3f;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action6::Action6()
{
	m_axis = DirectX::SimpleMath::Vector3(1, -0.2f, 0);
	m_axis.Normalize();
	m_slot = 1;
}

/// <summary>
/// 向きと速度の外積が0以下かつ速度x,zの大きさが0.3以上
/// </summary>
/// <returns></returns>
bool Action6::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	if (Cross(direction, velocity) < 0)return false;
	return abs(velocity.x) > 0.3f && abs(velocity.z) > 0.3f;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Action7::Action7()
{
	m_axis = DirectX::SimpleMath::Vector3::UnitZ;
	m_slot = 2;
}

/// <summary>
/// 向きと速度の内積が0.85以上かつ速度x,zのどちらかが2.15以上
/// </summary>
/// <returns></returns>
bool Action7::RotationConditions(DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Vector3 velocity)
{
	if (Dot(direction, velocity) < 0.85f)return false;
	if (abs(velocity.x) > 2.15f || abs(velocity.z) > 2.15f)
	{
		m_axis = DirectX::SimpleMath::Vector3::UnitZ;
		if(Cross(direction,velocity) >= 0)m_axis = -DirectX::SimpleMath::Vector3::UnitZ;
		return true;
	}
	return false;
}
