#pragma once
#include"Base/Component/Collider/Collider.h"


class Collision
{
private:
	static const int AABB_AABB = static_cast<int>(Collider::ColliderTag::AABB) + static_cast<int>(Collider::ColliderTag::AABB);

	static std::unordered_map<int, std::function<bool(Collider&, Collider&, DirectX::SimpleMath::Vector3*)>> OnTriggerDictionary;
	static std::unordered_map<int, std::function<DirectX::SimpleMath::Vector3(Collider&, Collider&)>> OnCollisionDictionary;
public:
	//コライダー同士が当たっているか判断
	static bool OnTrigger(Collider& collider1, Collider& collider2);
	//collider2に対するcollider1のめり込み量を取得
	static DirectX::SimpleMath::Vector3 OnCollision(Collider& collider1, Collider& collider2);
private:
	//AABB・AABB
	static bool AABB_AABB_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 AABB_AABB_Collision(Collider& collider1, Collider& collider2);

	//AABB・Segment
	static bool AABB_Segment_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 AABB_Segment_Collision(Collider& collider1, Collider& collider2);

	//OBB・OBB
	static bool OBB_OBB_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 OBB_OBB_Collision(Collider& collider1, Collider& collider2);

	//OBB・Sphere
	static bool OBB_Sphere_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 OBB_Sphere_Collision(Collider& collider1, Collider& collider2);

	//OBB・Segment
	static bool OBB_Segment_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 OBB_Segment_Collision(Collider& collider1, Collider& collider2);

	//Sphere・Sphere
	static bool Sphere_Sphere_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 Sphere_Sphere_Collision(Collider& collider1, Collider& collider2);

	//Sphere・Segment
	static bool Sphere_Segment_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback = nullptr);
	static DirectX::SimpleMath::Vector3 Sphere_Segment_Collision(Collider& collider1, Collider& collider2);
	//計算用関数
	static float LenSegOnSeparateAxis3(DirectX::SimpleMath::Vector3 sep,
		DirectX::SimpleMath::Vector3 ex,
		DirectX::SimpleMath::Vector3 ey,
		DirectX::SimpleMath::Vector3 ez);

	static float LenSegOnSeparateAxis2(DirectX::SimpleMath::Vector3 sep,
		DirectX::SimpleMath::Vector3 ex,
		DirectX::SimpleMath::Vector3 ey);

	static DirectX::SimpleMath::Vector3 distancePointToSegment(DirectX::SimpleMath::Vector3 point,
		DirectX::SimpleMath::Vector3 sega,
		DirectX::SimpleMath::Vector3 segb);

	static float clamp(float value, float min, float max);

	static bool BoundingSpheres(Collider& collider1, Collider& collider2);
};
