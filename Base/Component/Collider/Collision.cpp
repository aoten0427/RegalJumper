#include"pch.h"
#include"Collision.h"

//�ɑ吔
const float INFINITIY = FLT_MAX;
//�ɏ���
const float INV_INFINITIY = FLT_MIN;


//�g���K�[�g�ݍ��킹
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

//�R���W�����g�ݍ��킹
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
	//�^�O���ɕ��ёւ�
	Collider& col1 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider1 : collider2;
	Collider& col2 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider2 : collider1;

	//�g�ݍ��킹���v�Z
	int CollisionPearNum = (int)col1.GetColliderTag() + (int)col2.GetColliderTag();

	//�֐�������
	auto func = OnTriggerDictionary.find(CollisionPearNum);
	//����ꍇ�͎��s
	if (func != OnTriggerDictionary.end())
	{
		return OnTriggerDictionary[CollisionPearNum](col1,col2, nullptr);
	}
	//�Ȃ��ꍇ��false
	return false;
}

/// <summary>
/// Collision����
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::OnCollision(Collider& collider1, Collider& collider2)
{
	//�^�O���ɕ��ёւ�
	Collider& col1 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider1 : collider2;
	Collider& col2 = (int)collider1.GetColliderTag() <= (int)collider2.GetColliderTag() ? collider2 : collider1;

	//�g�ݍ��킹���v�Z
	int CollisionPearNum = (int)col1.GetColliderTag() + (int)col2.GetColliderTag();

	//�֐�������
	auto func = OnCollisionDictionary.find(CollisionPearNum);
	//����ꍇ�͎��s
	if (func != OnCollisionDictionary.end())
	{
		return OnCollisionDictionary[CollisionPearNum](col1,col2);
	}
	//�Ȃ��ꍇ��Zero��Ԃ�
	return DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// AABB���m
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

	//�e�ő�A�ŏ����v�Z
	Vector3 Min1 = aabb1.GetWorldPosition() - aabb1.GetExtents();
	Vector3 Max1 = aabb1.GetWorldPosition() + aabb1.GetExtents();
	Vector3 Min2 = aabb2.GetWorldPosition() - aabb2.GetExtents();
	Vector3 Max2 = aabb2.GetWorldPosition() + aabb2.GetExtents();

	//�d�Ȃ肪�Ȃ��ꍇ�������ĂȂ�
	if (Min1.x > Max2.x)return false;
	if (Min1.y > Max2.y)return false;
	if (Min1.z > Max2.z)return false;
	if (Min2.x > Max1.x)return false;
	if (Min2.y > Max1.y)return false;
	if (Min2.z > Max1.z)return false;

	return true;
}

/// <summary>
/// AABB���m
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::AABB_AABB_Collision(Collider& collider1, Collider& collider2)
{
	using namespace DirectX::SimpleMath;

	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);

	//�������Ă��邩����
	if (!AABB_AABB_Trigger(aabb1, aabb2))return DirectX::SimpleMath::Vector3::Zero;

	//�e�ő�A�ŏ����v�Z
	Vector3 Min1 = aabb1.GetWorldPosition() - aabb1.GetExtents();
	Vector3 Max1 = aabb1.GetWorldPosition() + aabb1.GetExtents();
	Vector3 Min2 = aabb2.GetWorldPosition() - aabb2.GetExtents();
	Vector3 Max2 = aabb2.GetWorldPosition() + aabb2.GetExtents();

	//�d�Ȃ�ʂ��v�Z
	float dx1 = Max2.x - Min1.x;
	float dx2 = Min2.x - Max1.x;
	float dy1 = Max2.y - Min1.y;
	float dy2 = Min2.y - Max1.y;
	float dz1 = Max2.z - Min1.z;
	float dz2 = Min2.z - Max1.z;

	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;
	// �����߂��x�N�g��
	Vector3 pushBackVec = Vector3::Zero;

	// �߂荞�݂���ԏ��������������߂��i�w�����ŏ��̏ꍇ�j
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

	//aabb��mix,max�̌v�Z
	Vector3 min = aabb.GetWorldPosition() - aabb.GetExtents();
	Vector3 max = aabb.GetWorldPosition() + aabb.GetExtents();
	//segment���
	Vector3 segmentStart = segment.GetWorldStartPos();
	Vector3 segmentEnd = segment.GetWorldEndPos();
	Vector3 segmentVector = segment.GetVector();

	// �e���ł̓����蔻����s�������_��
	auto checkAxis = [&](float segmentStart, float segmentEnd, float segmentVector, float min, float max, float& pushOut) -> bool {
		if (segmentVector == 0.0f) {
			//���ɑ΂��ĕ��s�Ŕ͈͓����m�F
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
			// �����o���ʂ̌v�Z
			float d1 = segmentEnd - min;
			float d2 = segmentStart - max;
			float overlap = abs(d1) < abs(d2) ? d1 : d2;
			if (std::abs(overlap) < std::abs(pushOut)) {
				pushOut = overlap; // ��菬���������o���ʂ�I��
			}
		}
		return true;
		};

	float pushX = INFINITIY;
	float pushY = INFINITIY;
	float pushZ = INFINITIY;

	// x���Ay���Az���̓����蔻��
	if (!checkAxis(segmentStart.x, segmentEnd.x, segmentVector.x, min.x, max.x, pushX)) return false;
	if (!checkAxis(segmentStart.y, segmentEnd.y, segmentVector.y, min.y, max.y, pushY)) return false;
	if (!checkAxis(segmentStart.z, segmentEnd.z, segmentVector.z, min.z, max.z, pushZ)) return false;

	if (pushback)
	{
		Vector3 back = Vector3::Zero;
		// �߂荞�݂���ԏ��������������߂��i�w�����ŏ��̏ꍇ�j
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
/// OBB���m
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

	// ����
	Vector3 distance = obb1.GetWorldPosition() - obb2.GetWorldPosition();

	// �e���̕����x�N�g�����擾
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

	// �����x�N�g���̑傫�����擾 (���O�Ɍv�Z)
	Vector3 extent1 = obb1.GetWorldScale();
	Vector3 extent2 = obb2.GetWorldScale();
	Vector3 Ae[3] = { NAe[0] * extent1.x, NAe[1] * extent1.y, NAe[2] * extent1.z };
	Vector3 Be[3] = { NBe[0] * extent2.x, NBe[1] * extent2.y, NBe[2] * extent2.z };

	//�ŒZ�����ƕ�����ۑ�
	/*Vector3 NearOffset;
	float depth = INFINITIY;*/

	auto projection = [&](Vector3 main, Vector3 line) -> DirectX::SimpleMath::Vector3 {
		float Dot = main.Dot(line);
		return main * Dot;
		};

	// obb1�e���ɑ΂��锻��
	for (int i = 0; i < 3; ++i) {
		float radiusA = DirectX::XMVectorGetByIndex(XMVector3Length(Ae[i]), i);
		float radiusB = LenSegOnSeparateAxis3(NAe[i], Be[0], Be[1], Be[2]);
		float L = fabs(distance.Dot(NAe[i]));
		if (L > radiusA + radiusB) return false; // �Փ˂��Ă��Ȃ�
	}
	// obb2�e���ɑ΂��锻��
	for (int i = 0; i < 3; ++i) {
		float radiusA = LenSegOnSeparateAxis3(NBe[i], Ae[0], Ae[1], Ae[2]);
		float radiusB = DirectX::XMVectorGetByIndex(XMVector3Length(Be[i]), i);
		float L = fabs(distance.Dot(NBe[i]));
		if (L > radiusA + radiusB) return false; // �Փ˂��Ă��Ȃ�
	}

	// �N���X�����g�p�����������̃`�F�b�N
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Vector3 Cross = NAe[i].Cross(NBe[j]);
			float radiusA = LenSegOnSeparateAxis2(Cross, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
			float radiusB = LenSegOnSeparateAxis2(Cross, Be[(j + 1) % 3], Be[(j + 2) % 3]);
			float L = fabs(distance.Dot(Cross));
			if (L > radiusA + radiusB) return false; // �Փ˂��Ă��Ȃ�
		}
	}

	// ���ׂĂ̎��ŏՓ˂��Ă���ꍇ�Atrue��Ԃ�
	return true;
}

/// <summary>
/// OBB���m
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

	// �e���̕����x�N�g���ƃG�N�X�e���g��z��
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


	// �e���ɑ΂��铊�e�̋������v�Z
	for (int i = 0; i < 3; ++i) {
		float Da = LenSegOnSeparateAxis3(NAe[i], Ae[0], Ae[1], Ae[2]);
		float Db = LenSegOnSeparateAxis3(NAe[i], Be[0], Be[1], Be[2]);
		Vector3 offset = projection(NAe[i], distance);
		float overlap = (Da + Db) - offset.Length();

		// �ł��߂��I�[�o�[���b�v���L�^
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

	// �e�N���X���i�ɑ΂��镪�����̃`�F�b�N
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Vector3 Cross = NAe[i].Cross(NBe[j]);
			if (Cross.LengthSquared() < INV_INFINITIY) continue;  // ���s�ȏꍇ�̓X�L�b�v
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

	// �Փ˃x�N�g����Ԃ�
	NearOffset.Normalize();
	return depth * NearOffset;
}



/// <summary>
/// OBB�Ƌ�
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

	//�e���̍ŒZ���i�[
	float shortest[3]{};

	//���[�J������
	Vector3 NAe[3] = {
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent = obb.GetExtents();
	//obb�̊e��
	Vector3 Ae[3] = { NAe[0] * extent.x, NAe[1] * extent.y, NAe[2] * extent.z };


	//obb�̊e���Ōv�Z
	for (int i = 0; i < 3; i++)
	{
		//���ς�����O���f
		float s = (distance).Dot(NAe[i]) / Ae[i].Length();
		s = fabs(s);
		if (s > 1)
		{
			//��яo�������v�Z
			shortest[i] = (1 - s) * Ae[i].Length();
		}
	}

	//vector3�ɕϊ�
	Vector3 shortestVector3{ shortest[0],shortest[1] ,shortest[2] };
	//���a��蒷����Γ������Ă��Ȃ�
	if (shortestVector3.Length() > sphere.GetRadius())return false;

	//�����o���v�Z
	if (pushback)
	{
		distance.Normalize();
		distance *= -1;
		*pushback = distance * (sphere.GetRadius() - shortestVector3.Length());
	}
	return true;
}

/// <summary>
/// OBB�Ƌ�
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
/// OBB�Ɛ���
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

	// 1. �����̒��S C �Ɣ��a�x�N�g�� D ���v�Z
	Vector3 segmentCenter = (segment.GetWorldStartPos() + segment.GetWorldEndPos()) * 0.5f;
	Vector3 SegmentVector = segment.GetVector() * 0.5f;
	Vector3 SegVecNormal = SegmentVector;
	SegVecNormal.Normalize();

	// 2. OBB �̒��S�Ǝ�
	Vector3 OC = obb.GetTransform().GetRotatePosition();
	Vector3 NAe[3] = {
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent = obb.GetExtents();
	Vector3 Ae[3] = { NAe[0] * extent.x, NAe[1] * extent.y, NAe[2] * extent.z };

	// 3. �����x�N�g��
	Vector3 distance = segmentCenter - OC;

	// 4. �e�������̃`�F�b�N
	float rA, rB, L;

	for (int i = 0; i < 3; i++)
	{
		rA = Ae[i].Length();
		rB = fabs(SegmentVector.Dot(NAe[i]));
		L = fabs(distance.Dot(NAe[i]));
		if (L > rA + rB) return false; // �Փ˂��Ă��Ȃ�
	}

	rA = LenSegOnSeparateAxis3(SegVecNormal, Ae[0], Ae[1], Ae[2]);
	rB = SegmentVector.Length();
	L = fabs(distance.Dot(SegVecNormal));
	if (L > rA + rB) return false; // �Փ˂��Ă��Ȃ�


	for (int i = 0; i < 3; ++i) {
		Vector3 Cross = NAe[i].Cross(SegmentVector);
		if (Cross.LengthSquared() < INV_INFINITIY) continue;
		float radiusA = LenSegOnSeparateAxis2(Cross, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
		float radiusB = fabs(SegmentVector.Dot(Cross));
		L = fabs(distance.Dot(Cross));
		if (L > radiusA + radiusB) return false; // �Փ˂��Ă��Ȃ�
	}

	return true; // �S�Ă̕������ŏd�Ȃ肪���邽�߁A�������Ă���
}

/// <summary>
/// OBB�Ɛ���
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

	// �����̒��S C �Ɣ��a�x�N�g�� D ���v�Z
	Vector3 segmentCenter = (segment.GetWorldStartPos() + segment.GetWorldEndPos()) * 0.5f;
	Vector3 SegmentVector = segment.GetVector() * 0.5f;
	Vector3 SegVecNormal = SegmentVector; // ���K������K�v�͌�ōl��
	SegVecNormal.Normalize();

	// OBB �̒��S�Ǝ�
	Vector3 OC = obb.GetTransform().GetRotatePosition();
	Vector3 NAe[3] = {
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitX),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitY),
		obb.GetTransform().GetWorldAxisFromLocal(Vector3::UnitZ)
	};
	Vector3 extent = obb.GetExtents();
	Vector3 Ae[3] = { NAe[0] * extent.x, NAe[1] * extent.y, NAe[2] * extent.z };

	// �����x�N�g��
	Vector3 distance = segmentCenter - OC;

	// �ŏ��߂荞�ݗʂ�ǐ�
	float minPenetration = FLT_MAX;
	Vector3 minAxis;

	// �������e�X�g
	auto TestAxis = [&](const Vector3& axis, float rA, float rB) -> void {
		float L = fabs(distance.Dot(axis));
		float penetration = rA + rB - L;
		if (penetration < 0) return; // �������Ă���
		if (penetration < minPenetration) {
			minPenetration = penetration;
			minAxis = axis;
		}
		};

	// OBB�̃��[�J�����Ńe�X�g
	for (int i = 0; i < 3; ++i) {
		float rA = Ae[i].Length();
		float rB = fabs(SegmentVector.Dot(NAe[i]));
		TestAxis(NAe[i], rA, rB);
	}

	// �����̎��Ńe�X�g
	float rA = LenSegOnSeparateAxis3(SegmentVector, Ae[0], Ae[1], Ae[2]);
	float rB = SegmentVector.Length();
	TestAxis(SegVecNormal, rA, rB);

	// �N���X���Ńe�X�g
	for (int i = 0; i < 3; ++i) {
		Vector3 Cross = SegmentVector.Cross(NAe[i]);
		Vector3 CrossNormal = Cross;
		CrossNormal.Normalize();
		if (Cross.LengthSquared() < 1e-6f) continue; // ���s�ȏꍇ�̓X�L�b�v
		rA = LenSegOnSeparateAxis2(CrossNormal, Ae[(i + 1) % 3], Ae[(i + 2) % 3]);
		rB = fabs(SegmentVector.Dot(CrossNormal));
		TestAxis(CrossNormal, rA, rB);
	}

	minAxis.Normalize();
	if (distance.Dot(-minAxis) < 0.0f) {
		minAxis = -minAxis; // �����𔽓]
	}
	return minAxis * minPenetration;
}

bool Collision::Sphere_Sphere_Trigger(Collider& collider1, Collider& collider2, DirectX::SimpleMath::Vector3* pushback)
{
	using namespace DirectX::SimpleMath;

	Sphere& sphere1 = static_cast<Sphere&>(collider1);
	Sphere& sphere2 = static_cast<Sphere&>(collider2);

	//���S���m�̋������v�Z
	Vector3 direction = sphere1.GetTransform().GetRotatePosition() - sphere2.GetTransform().GetRotatePosition();

	//���a�̍��v���v�Z
	float radius = sphere1.GetRadius() + sphere2.GetRadius();

	//���a���Z����Γ������Ă��Ȃ�
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

	//�������Ă��邩����
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

	// ���̔��ʎ�
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		// ��_�Ȃ�
		return false;
	}

	// 2�̉������߂� (t1 <= t2)
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

	//�������Ă��邩����
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
