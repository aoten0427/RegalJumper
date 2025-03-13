#include"pch.h"
#include"Collision.h"

//極大数
const float INFINITIY = FLT_MAX;
//極小数
const float INV_INFINITIY = FLT_MIN;


//トリガー組み合わせ
std::unordered_map<int, std::function<bool(Collider&, Collider&, DirectX::SimpleMath::Vector3*)>> Collision::OnTriggerDictionary =
{
	{static_cast<int>(Collider::ColliderTag::AABB) + static_cast<int>(Collider::ColliderTag::AABB),Collision::AABB_AABB_Trigger},
	{static_cast<int>(Collider::ColliderTag::AABB) + static_cast<int>(Collider::ColliderTag::SEGMENT),Collision::AABB_Segment_Trigger},
	{static_cast<int>(Collider::ColliderTag::OBB) + static_cast<int>(Collider::ColliderTag::OBB),Collision::OBB_OBB_Trigger},
	{static_cast<int>(Collider::ColliderTag::OBB) + static_cast<int>(Collider::ColliderTag::SEGMENT),Collision::OBB_Segment_Trigger},
	{static_cast<int>(Collider::ColliderTag::OBB) + static_cast<int>(Collider::ColliderTag::SPHERE),Collision::OBB_Sphere_Trigger},
	{static_cast<int>(Collider::ColliderTag::SPHERE) + static_cast<int>(Collider::ColliderTag::SPHERE),Collision::Sphere_Sphere_Trigger},
	{static_cast<int>(Collider::ColliderTag::SPHERE) + static_cast<int>(Collider::ColliderTag::SEGMENT),Collision::Sphere_Segment_Trigger}
};

//コリジョン組み合わせ
std::unordered_map<int, std::function<DirectX::SimpleMath::Vector3(Collider&, Collider&)>> Collision::OnCollisionDictionary =
{
	{static_cast<int>(Collider::ColliderTag::AABB) + static_cast<int>(Collider::ColliderTag::AABB),Collision::AABB_AABB_Collision},
	{static_cast<int>(Collider::ColliderTag::AABB) + static_cast<int>(Collider::ColliderTag::SEGMENT),Collision::AABB_Segment_Collision},
	{static_cast<int>(Collider::ColliderTag::OBB) + static_cast<int>(Collider::ColliderTag::OBB),Collision::OBB_OBB_Collision},
	{static_cast<int>(Collider::ColliderTag::OBB) + static_cast<int>(Collider::ColliderTag::SEGMENT),Collision::OBB_Segment_Collision},
	{static_cast<int>(Collider::ColliderTag::OBB) + static_cast<int>(Collider::ColliderTag::SPHERE),Collision::OBB_Sphere_Collision},
	{static_cast<int>(Collider::ColliderTag::SPHERE) + static_cast<int>(Collider::ColliderTag::SPHERE),Collision::Sphere_Sphere_Collision},
	{static_cast<int>(Collider::ColliderTag::SPHERE) + static_cast<int>(Collider::ColliderTag::SEGMENT),Collision::Sphere_Segment_Collision}
};

bool Collision::OnTrigger(Collider& collider1, Collider& collider2)
{
	//タグ順に並び替え
	Collider& col1 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider1 : collider2;
	Collider& col2 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider2 : collider1;

	//組み合わせを計算
	int CollisionPearNum = (int)col1.GetColliderTag() + (int)col2.GetColliderTag();

	//関数を検索
	auto func = OnTriggerDictionary.find(CollisionPearNum);
	//ある場合は実行
	if (func != OnTriggerDictionary.end())
	{
		return OnTriggerDictionary[CollisionPearNum](col1,col2, nullptr);
	}
	//ない場合はfalse
	return false;
}

/// <summary>
/// Collision処理
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::OnCollision(Collider& collider1, Collider& collider2)
{
	//タグ順に並び替え
	Collider& col1 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider1 : collider2;
	Collider& col2 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider2 : collider1;

	//組み合わせを計算
	int CollisionPearNum = (int)col1.GetColliderTag() + (int)col2.GetColliderTag();

	//関数を検索
	auto func = OnCollisionDictionary.find(CollisionPearNum);
	//ある場合は実行
	if (func != OnCollisionDictionary.end())
	{
		return OnCollisionDictionary[CollisionPearNum](col1,col2);
	}
	//ない場合はZeroを返す
	return DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// AABB同士
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <param name="pushback"></param>
/// <returns></returns>
bool Collision::AABB_AABB_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	UNREFERENCED_PARAMETER(pushback);
	using namespace DirectX::SimpleMath;

	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);

	//各最大、最小を計算
	Vector3 Min1 = aabb1.GetWorldPosition() - aabb1.GetExtents();
	Vector3 Max1 = aabb1.GetWorldPosition() + aabb1.GetExtents();
	Vector3 Min2 = aabb2.GetWorldPosition() - aabb2.GetExtents();
	Vector3 Max2 = aabb2.GetWorldPosition() + aabb2.GetExtents();

	//重なりがない場合当たってない
	if (Min1.x > Max2.x)return false;
	if (Min1.y > Max2.y)return false;
	if (Min1.z > Max2.z)return false;
	if (Min2.x > Max1.x)return false;
	if (Min2.y > Max1.y)return false;
	if (Min2.z > Max1.z)return false;

	return true;
}

/// <summary>
/// AABB同士
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::AABB_AABB_Collision(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;

	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);

	//当たっているか判定
	if (!AABB_AABB_Trigger(aabb1, aabb2))return DirectX::SimpleMath::Vector3::Zero;

	//各最大、最小を計算
	Vector3 Min1 = aabb1.GetWorldPosition() - aabb1.GetExtents();
	Vector3 Max1 = aabb1.GetWorldPosition() + aabb1.GetExtents();
	Vector3 Min2 = aabb2.GetWorldPosition() - aabb2.GetExtents();
	Vector3 Max2 = aabb2.GetWorldPosition() + aabb2.GetExtents();

	//重なり量を計算
	float dx1 = Max2.x - Min1.x;
	float dx2 = Min2.x - Max1.x;
	float dy1 = Max2.y - Min1.y;
	float dy2 = Min2.y - Max1.y;
	float dz1 = Max2.z - Min1.z;
	float dz2 = Min2.z - Max1.z;

	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;
	// 押し戻しベクトル
	Vector3 pushBackVec = Vector3::Zero;

	// めり込みが一番小さい軸を押し戻す（Ｘ軸が最小の場合）
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else
	if (abs(dy) <= abs(dx) && abs(dy) <= abs(dz))
	{
		pushBackVec.y += dy;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}

	return pushBackVec;
}



bool Collision::AABB_Segment_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	using namespace DirectX::SimpleMath;

	AABB& aabb = static_cast<AABB&>(collider1);
	Segment& segment = static_cast<Segment&>(collider2);

	float t0 = 0.0f, t1 = 1.0f;

	//aabbのmix,maxの計算
	Vector3 min = aabb.GetWorldPosition() - aabb.GetExtents();
	Vector3 max = aabb.GetWorldPosition() + aabb.GetExtents();
	//segment情報
	Vector3 segmentStart = segment.GetWorldStartPos();
	Vector3 segmentEnd = segment.GetWorldEndPos();
	Vector3 segmentVector = segment.GetVector();

	// 各軸での当たり判定を行うラムダ式
	auto checkAxis = [&](float segmentStart, float segmentEnd, float segmentVector, float min, float max, float& pushOut) -> bool {
		if (segmentVector == 0.0f) {
			//軸に対して平行で範囲内か確認
			if (segmentStart < min || segmentStart > max) return false;
		}
		else {
			float invD = 1.0f / segmentVector;
			float tMin = (min - segmentStart) * invD;
			float tMax = (max - segmentStart) * invD;
			if (tMin > tMax) std::swap(tMin, tMax);

			t0 = std::max(t0, tMin);
			t1 = std::min(t1, tMax);
			if (t0 > t1) return false;
		}

		if (pushback)
		{
			if (segmentStart > segmentEnd)std::swap(segmentStart, segmentEnd);
			// 押し出し量の計算
			float d1 = segmentEnd - min;
			float d2 = segmentStart - max;
			float overlap = abs(d1) < abs(d2) ? d1 : d2;
			if (std::abs(overlap) < std::abs(pushOut)) {
				pushOut = overlap; // より小さい押し出し量を選択
			}
		}
		return true;
		};

	float pushX = INFINITIY;
	float pushY = INFINITIY;
	float pushZ = INFINITIY;

	// x軸、y軸、z軸の当たり判定
	if (!checkAxis(segmentStart.x, segmentEnd.x, segmentVector.x, min.x, max.x, pushX)) return false;
	if (!checkAxis(segmentStart.y, segmentEnd.y, segmentVector.y, min.y, max.y, pushY)) return false;
	if (!checkAxis(segmentStart.z, segmentEnd.z, segmentVector.z, min.z, max.z, pushZ)) return false;

	if (pushback)
	{
		Vector3 back = Vector3::Zero;
		// めり込みが一番小さい軸を押し戻す（Ｘ軸が最小の場合）
		if (abs(pushX) <= abs(pushY) && abs(pushX) <= abs(pushZ))
		{
			back.x += pushX;
		}
		else
		if (abs(pushY) <= abs(pushX) && abs(pushY) <= abs(pushZ))
		{
			back.y += pushY;
		}
		else if (abs(pushZ) <= abs(pushX) && abs(pushZ) <= abs(pushY))
		{
			back.z += pushZ;
		}
		*pushback = back;
	}

	return true;
}

DirectX::SimpleMath::Vector3 Collision::AABB_Segment_Collision(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;
	AABB& aabb = static_cast<AABB&>(collider1);
	Segment& segment = static_cast<Segment&>(collider2);
	Vector3 pushback = Vector3::Zero;
	if (!AABB_Segment_Trigger(aabb, segment, &pushback))return Vector3::Zero;
	return pushback;
}

/// <summary>
/// OBB同士
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <param name="pushback"></param>
/// <returns></returns>
bool Collision::OBB_OBB_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	UNREFERENCED_PARAMETER(pushback);
	using namespace DirectX::SimpleMath;

	OBB& obb1 = static_cast<OBB&>(collider1);
	OBB& obb2 = static_cast<OBB&>(collider2);

	if (!BoundingSpheres(obb1, obb2))return false;

	// 距離
	Vector3 distance = obb1.GetWorldPosition() - obb2.GetWorldPosition();

	// 各軸の方向ベクトルを取得
	Vector3 NAe[3] = {
		obb1.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb1.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb1.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 NBe[3] = {
		obb2.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb2.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb2.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};

	// 方向ベクトルの大きさを取得 (事前に計算)
	Vector3 extent1 = obb1.GetWorldScale();
	Vector3 extent2 = obb2.GetWorldScale();
	Vector3 Ae[3] = { NAe[0] * extent1.x, NAe[1] * extent1.y, NAe[2] * extent1.z };
	Vector3 Be[3] = { NBe[0] * extent2.x, NBe[1] * extent2.y, NBe[2] * extent2.z };

	//最短距離と方向を保存
	/*Vector3 NearOffset;
	float depth = INFINITIY;*/

	auto projection = [&](Vector3 main, Vector3 line) -> DirectX::SimpleMath::Vector3 {
		float Dot = main.Dot(line);
		return main * Dot;
		};

	// obb1各軸に対する判定
	for (int i = 0; i < 3; ++i) {
		float radiusA = DirectX::XMVectorGetByIndex(XMVector3Length(Ae[i]), i);
		float radiusB = LenSegOnSeparateAxis3(NAe[i], Be[0], Be[1], Be[2]);
		float L = fabs(distance.Dot(NAe[i]));
		if (L > radiusA + radiusB) return false; // 衝突していない
	}
	// obb2各軸に対する判定
	for (int i = 0; i < 3; ++i) {
		float radiusA = LenSegOnSeparateAxis3(NBe[i], Ae[0], Ae[1], Ae[2]);
		float radiusB = DirectX::XMVectorGetByIndex(XMVector3Length(Be[i]), i);
		float L = fabs(distance.Dot(NBe[i]));
		if (L > radiusA + radiusB) return false; // 衝突していない
	}

	// クロス軸を使用した分離軸のチェック
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Vector3 Cross = NAe[i].Cross(NBe[j]);
			float radiusA = LenSegOnSeparateAxis2(Cross, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
			float radiusB = LenSegOnSeparateAxis2(Cross, Be[(j + 1) % 3], Be[(j + 2) % 3]);
			float L = fabs(distance.Dot(Cross));
			if (L > radiusA + radiusB) return false; // 衝突していない
		}
	}

	// すべての軸で衝突している場合、trueを返す
	return true;
}

/// <summary>
/// OBB同士
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::OBB_OBB_Collision(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;

	OBB& obb1 = static_cast<OBB&>(collider1);
	OBB& obb2 = static_cast<OBB&>(collider2);

	if (!OBB_OBB_Trigger(obb1, obb2)) return Vector3::Zero;

	Vector3 distance = obb1.GetWorldPosition() - obb2.GetWorldPosition();

	// 各軸の方向ベクトルとエクステントを配列化
	Vector3 NAe[3] = {
		obb1.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb1.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb1.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 NBe[3] = {
		obb2.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb2.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb2.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent1 = obb1.GetExtents();
	Vector3 extent2 = obb2.GetExtents();

	Vector3 Ae[3] = { NAe[0] * extent1.x, NAe[1] * extent1.y, NAe[2] * extent1.z };
	Vector3 Be[3] = { NBe[0] * extent2.x, NBe[1] * extent2.y, NBe[2] * extent2.z };

	Vector3 NearOffset;
	float depth = INFINITIY;

	auto projection = [&](Vector3 main, Vector3 line) -> DirectX::SimpleMath::Vector3 {
		float Dot = main.Dot(line);
		return main * Dot;
		};


	// 各軸に対する投影の距離を計算
	for (int i = 0; i < 3; ++i) {
		float Da = LenSegOnSeparateAxis3(NAe[i], Ae[0], Ae[1], Ae[2]);
		float Db = LenSegOnSeparateAxis3(NAe[i], Be[0], Be[1], Be[2]);
		Vector3 offset = projection(NAe[i], distance);
		float overlap = (Da + Db) - offset.Length();

		// 最も近いオーバーラップを記録
		if (overlap < depth) {
			depth = overlap;
			NearOffset = offset;
		}
	}

	for (int i = 0; i < 3; ++i) {
		float Da = LenSegOnSeparateAxis3(NBe[i], Ae[0], Ae[1], Ae[2]);
		float Db = LenSegOnSeparateAxis3(NBe[i], Be[0], Be[1], Be[2]);
		Vector3 offset = projection(NBe[i], distance);
		float overlap = (Da + Db) - offset.Length();

		if (overlap < depth) {
			depth = overlap;
			NearOffset = offset;
		}
	}

	// 各クロス製品に対する分離軸のチェック
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Vector3 Cross = NAe[i].Cross(NBe[j]);
			if (Cross.LengthSquared() < INV_INFINITIY) continue;  // 平行な場合はスキップ
			Cross.Normalize();

			float Da = LenSegOnSeparateAxis2(Cross, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
			float Db = LenSegOnSeparateAxis2(Cross, Be[(j + 1) % 3], Be[(j + 2) % 3]);
			Vector3 offset = projection(Cross, distance);
			float overlap = (Da + Db) - offset.Length();

			if (overlap < depth) {
				depth = overlap;
				NearOffset = offset;
			}
		}
	}

	// 衝突ベクトルを返す
	NearOffset.Normalize();
	return depth * NearOffset;
}



/// <summary>
/// OBBと球
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <param name="pushback"></param>
/// <returns></returns>
bool Collision::OBB_Sphere_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	using namespace DirectX::SimpleMath;

	OBB& obb = static_cast<OBB&>(collider1);
	Sphere& sphere = static_cast<Sphere&>(collider2);

	Vector3 sphereCenter = sphere.GetWorldPosition();
	Vector3 distance = sphereCenter - obb.GetWorldPosition();

	//各軸の最短を格納
	float shortest[3]{};

	//ローカル方向
	Vector3 NAe[3] = {
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent = obb.GetExtents();
	//obbの各辺
	Vector3 Ae[3] = { NAe[0] * extent.x, NAe[1] * extent.y, NAe[2] * extent.z };


	//obbの各軸で計算
	for (int i = 0; i < 3; i++)
	{
		//内積から内外判断
		float s = (distance).Dot(NAe[i]) / Ae[i].Length();
		s = fabs(s);
		if (s > 1)
		{
			//飛び出し分を計算
			shortest[i] = (1 - s) * Ae[i].Length();
		}
	}

	//vector3に変換
	Vector3 shortestVector3{ shortest[0],shortest[1] ,shortest[2] };
	//半径より長ければ当たっていない
	if (shortestVector3.Length() > sphere.GetRadius())return false;

	//押し出し計算
	if (pushback)
	{
		distance.Normalize();
		distance *= -1;
		*pushback = distance * (sphere.GetRadius() - shortestVector3.Length());
	}
	return true;
}

/// <summary>
/// OBBと球
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::OBB_Sphere_Collision(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;

	OBB& obb = static_cast<OBB&>(collider1);
	Sphere& sphere = static_cast<Sphere&>(collider2);

	Vector3 pushback{};

	if (!OBB_Sphere_Trigger(obb, sphere, &pushback))return Vector3::Zero;
	return pushback;
}



/// <summary>
/// OBBと線分
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <param name="pushback"></param>
/// <returns></returns>
bool Collision::OBB_Segment_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	UNREFERENCED_PARAMETER(pushback);
	using namespace DirectX::SimpleMath;

	
	OBB& obb = static_cast<OBB&>(collider1);
	Segment& segment = static_cast<Segment&>(collider2);

	if (!BoundingSpheres(obb, segment))return false;

	// 1. 線分の中心 C と半径ベクトル D を計算
	Vector3 segmentCenter = (segment.GetWorldStartPos() + segment.GetWorldEndPos()) * 0.5f;
	Vector3 SegmentVector = segment.GetVector() * 0.5f;
	Vector3 SegVecNormal = SegmentVector;
	SegVecNormal.Normalize();

	// 2. OBB の中心と軸
	Vector3 OC = obb.GetTransform().GetRotatePosition();
	Vector3 NAe[3] = {
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent = obb.GetExtents();
	Vector3 Ae[3] = { NAe[0] * extent.x, NAe[1] * extent.y, NAe[2] * extent.z };

	// 3. 距離ベクトル
	Vector3 distance = segmentCenter - OC;

	// 4. 各分離軸のチェック
	float rA, rB, L;

	for (int i = 0; i < 3; i++)
	{
		rA = Ae[i].Length();
		rB = fabs(SegmentVector.Dot(NAe[i]));
		L = fabs(distance.Dot(NAe[i]));
		if (L > rA + rB) return false; // 衝突していない
	}

	rA = LenSegOnSeparateAxis3(SegVecNormal, Ae[0], Ae[1], Ae[2]);
	rB = SegmentVector.Length();
	L = fabs(distance.Dot(SegVecNormal));
	if (L > rA + rB) return false; // 衝突していない


	for (int i = 0; i < 3; ++i) {
		Vector3 Cross = NAe[i].Cross(SegmentVector);
		if (Cross.LengthSquared() < INV_INFINITIY) continue;
		float radiusA = LenSegOnSeparateAxis2(Cross, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
		float radiusB = fabs(SegmentVector.Dot(Cross));
		L = fabs(distance.Dot(Cross));
		if (L > radiusA + radiusB) return false; // 衝突していない
	}

	return true; // 全ての分離軸で重なりがあるため、交差している
}

/// <summary>
/// OBBと線分
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::OBB_Segment_Collision(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;

	OBB& obb = static_cast<OBB&>(collider1);
	Segment& segment = static_cast<Segment&>(collider2);

	if (!OBB_Segment_Trigger(obb, segment)) return Vector3::Zero;

	// 線分の中心 C と半径ベクトル D を計算
	Vector3 segmentCenter = (segment.GetWorldStartPos() + segment.GetWorldEndPos()) * 0.5f;
	Vector3 SegmentVector = segment.GetVector() * 0.5f;
	Vector3 SegVecNormal = SegmentVector; // 正規化する必要は後で考慮
	SegVecNormal.Normalize();

	// OBB の中心と軸
	Vector3 OC = obb.GetTransform().GetRotatePosition();
	Vector3 NAe[3] = {
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent = obb.GetExtents();
	Vector3 Ae[3] = { NAe[0] * extent.x, NAe[1] * extent.y, NAe[2] * extent.z };

	// 距離ベクトル
	Vector3 distance = segmentCenter - OC;

	// 最小めり込み量を追跡
	float minPenetration = FLT_MAX;
	Vector3 minAxis;

	// 分離軸テスト
	auto TestAxis = [&](const Vector3& axis, float rA, float rB) -> void {
		float L = fabs(distance.Dot(axis));
		float penetration = rA + rB - L;
		if (penetration < 0) return; // 分離している
		if (penetration < minPenetration) {
			minPenetration = penetration;
			minAxis = axis;
		}
		};

	// OBBのローカル軸でテスト
	for (int i = 0; i < 3; ++i) {
		float rA = Ae[i].Length();
		float rB = fabs(SegmentVector.Dot(NAe[i]));
		TestAxis(NAe[i], rA, rB);
	}

	// 線分の軸でテスト
	float rA = LenSegOnSeparateAxis3(SegmentVector, Ae[0], Ae[1], Ae[2]);
	float rB = SegmentVector.Length();
	TestAxis(SegVecNormal, rA, rB);

	// クロス軸でテスト
	for (int i = 0; i < 3; ++i) {
		Vector3 Cross = SegmentVector.Cross(NAe[i]);
		Vector3 CrossNormal = Cross;
		CrossNormal.Normalize();
		if (Cross.LengthSquared() < 1e-6f) continue; // 平行な場合はスキップ
		rA = LenSegOnSeparateAxis2(CrossNormal, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
		rB = fabs(SegmentVector.Dot(CrossNormal));
		TestAxis(CrossNormal, rA, rB);
	}

	minAxis.Normalize();
	if (distance.Dot(-minAxis) < 0.0f) {
		minAxis = -minAxis; // 方向を反転
	}
	return minAxis * minPenetration;
}

bool Collision::Sphere_Sphere_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	using namespace DirectX::SimpleMath;

	Sphere& sphere1 = static_cast<Sphere&>(collider1);
	Sphere& sphere2 = static_cast<Sphere&>(collider2);

	//中心同士の距離を計算
	Vector3 direction = sphere1.GetTransform().GetRotatePosition() - sphere2.GetTransform().GetRotatePosition();

	//半径の合計を計算
	float radius = sphere1.GetRadius() + sphere2.GetRadius();

	//半径より短ければ当たっていない
	if (direction.Length() > radius)return false;

	if (pushback != nullptr)
	{
		float power = radius - direction.Length();
		direction.Normalize();
		*pushback = direction * power;
	}

	return true;
}

DirectX::SimpleMath::Vector3 Collision::Sphere_Sphere_Collision(Collider& collider1, Collider& collider2)
{
	Sphere& sphere1 = static_cast<Sphere&>(collider1);
	Sphere& sphere2 = static_cast<Sphere&>(collider2);

	DirectX::SimpleMath::Vector3 pushback;

	//当たっているか判定
	if (!Sphere_Sphere_Trigger(sphere1, sphere2, &pushback))return DirectX::SimpleMath::Vector3::Zero;

	return pushback;
}

bool Collision::Sphere_Segment_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{

	Sphere& sphere = static_cast<Sphere&>(collider1);
	Segment& segment = static_cast<Segment&>(collider2);

	if (!BoundingSpheres(collider1, collider2))return false;

	using namespace DirectX::SimpleMath;


	Vector3 str = segment.GetWorldStartPos();

	Vector3 vector = segment.GetVector();
	Vector3 length = segment.GetWorldStartPos() - sphere.GetTransform().GetWorldPosition();

	float a = vector.Dot(vector);
	float b = 2 * length.Dot(vector);
	float c = length.Dot(length) - sphere.GetRadius() * sphere.GetRadius();

	// 解の判別式
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		// 交点なし
		return false;
	}

	// 2つの解を求める (t1 <= t2)
	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	Vector3 intersection;

	if (0 <= t1 && t1 <= 1) {
		if (pushback != nullptr)
		{
			intersection = segment.GetWorldStartPos() + t1 * vector;
			*pushback = (segment.GetWorldEndPos() - intersection);
		}

		return true;
	}
	else if (0 <= t2 && t2 <= 1) {
		if (pushback != nullptr)
		{
			intersection = segment.GetWorldStartPos() + t2 * vector;
			*pushback = (segment.GetWorldEndPos() - intersection);
		}
		return true;
	}

	return false;
}

DirectX::SimpleMath::Vector3 Collision::Sphere_Segment_Collision(Collider& collider1, Collider& collider2)
{
	Sphere& sphere = static_cast<Sphere&>(collider1);
	Segment& segment = static_cast<Segment&>(collider2);

	using namespace DirectX::SimpleMath;

	Vector3 pushback;

	//当たっているか判定
	if (!Sphere_Segment_Trigger(sphere, segment, &pushback))return Vector3::Zero;

	return pushback;
}




float Collision::LenSegOnSeparateAxis3(DirectX::SimpleMath::Vector3 sep, DirectX::SimpleMath::Vector3 ex, DirectX::SimpleMath::Vector3 ey, DirectX::SimpleMath::Vector3 ez)
{
	
	float rx = fabs(sep.Dot(ex));
	float ry = fabs(sep.Dot(ey));
	float rz = fabs(sep.Dot(ez));
	return rx + ry + rz;
}

float Collision::LenSegOnSeparateAxis2(DirectX::SimpleMath::Vector3 sep, DirectX::SimpleMath::Vector3 ex, DirectX::SimpleMath::Vector3 ey)
{
	
	float rx = fabs(sep.Dot(ex));
	float ry = fabs(sep.Dot(ey));
	return rx + ry;
}

DirectX::SimpleMath::Vector3 Collision::distancePointToSegment(DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 sega, DirectX::SimpleMath::Vector3 segb)
{
	using namespace DirectX::SimpleMath;

	Vector3 ab = segb - sega;
	Vector3 ap = point - sega;
	float t = clamp(ap.Dot(ab) / ab.Dot(ab), 0.0f, 1.0f);
	Vector3 closestPoint = sega + ab * t;

	return closestPoint;
}


float Collision::clamp(float value, float min, float max)
{
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}

bool Collision::BoundingSpheres(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;

	Vector3 position1 = collider1.GetWorldPosition();
	Vector3 position2 = collider2.GetWorldPosition();
	float distance = Vector3::DistanceSquared(position1, position2);
	float scope = collider1.GetRadius() + collider2.GetRadius();
	if (distance> scope * scope)return false;
	return true;
}
