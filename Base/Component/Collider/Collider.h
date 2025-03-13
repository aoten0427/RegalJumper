// ================================================================ 
// �t�@�C���� : Collider.h
// �쐬�� : �i�R�ɓV
// ���� :  �e�����蔻��
// ================================================================
#pragma once
#include"Base/Component/Collider/Collider.h"
#include"Base/Component/Transform/Transform.h"

class Rigidbody;

//���莞�̃^�C�v
enum class CollisionType
{
	FIXED,
	COLLISION,
	TRIGGER,
	ORBIT
};

class Collider:public Component
{
public:
	//�R���C�_�[�^�C�v
	enum ColliderTag
	{
		AABB = 1 << 0,
		OBB = 1 << 2,
		SPHERE = 1 << 3,
		SEGMENT = 1 << 4,
		TRIANGLE = 1 << 5,
		QUAD = 1 << 6
	};
public:
	//�^�O�擾
	const ColliderTag& GetColliderTag() const { return m_colliderTag; }
	//�v�Z�p�g�����X�t�H�[��
	Transform GetTransform()const { return *m_transform; }
	//���W�b�g�{�f�B�擾
	Rigidbody* GetRigidbody() { return m_rigidbody; }
	//�|�W�V�����擾
	DirectX::SimpleMath::Vector3 GetPosition() const{ return m_position; }
	//�X�P�[���擾
	DirectX::SimpleMath::Vector3 GetScale()const { return m_scale; }
	//matrix�擾
	DirectX::SimpleMath::Matrix GetMatrix()const { return m_matrix; }
	//
	bool GetIsNotPas()const { return m_isNotPas; };
	void SetIsNotPas(const bool& isnotpas) { m_isNotPas = isnotpas; }
private:
	//�^�O
	ColliderTag m_colliderTag;
	//�g�����X�t�H�[��
	Transform* m_transform;
	//���W�b�h�{�f�B
	Rigidbody* m_rigidbody;
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//���g��matrix
	DirectX::SimpleMath::Matrix m_matrix;
	//���蔲������t���O(���蔲����h�~���鑤�̃t���O)
	bool m_isNotPas;
public:
	Collider(Object* object, ColliderTag tag, CollisionType type, Rigidbody* rigidbody = nullptr,bool view = false);
	virtual ~Collider();

	//�|�W�V�����Z�b�g
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//�X�P�[���Z�b�g
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//���[���h���W�擾
	DirectX::SimpleMath::Vector3 GetWorldPosition();
	//���[���h�X�P�[���擾
	DirectX::SimpleMath::Vector3 GetWorldScale();
	//���[���hmatrix�擾
	virtual DirectX::SimpleMath::Matrix GetWorldMatrix();
	//�o�E���f�B���O�X�t�B�A�p���a�擾
	virtual float GetRadius();
};

/// <summary>
/// AABB
/// </summary>
class AABB final: public Collider
{
private:
	
public:
	AABB(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false);
	~AABB()override = default;

	DirectX::SimpleMath::Matrix GetWorldMatrix()override;

	//�傫����Ԃ�
	DirectX::SimpleMath::Vector3 GetExtents();

	float GetRadius()override;
};

/// <summary>
/// OBB
/// </summary>
class OBB final :public Collider
{
private:
public:
	OBB(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false);
	~OBB()override = default;

	//�傫����Ԃ�
	DirectX::SimpleMath::Vector3 GetExtents();

	float GetRadius()override;
};

/// <summary>
/// ��
/// </summary>
class Sphere final :public Collider
{
private:
	float m_radius;
public:
	Sphere(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false,float radius = 1);
	~Sphere()override = default;
	void  SetRadius(float radius);
	float GetRadius() override;
};

/// <summary>
/// ����
/// </summary>
class Segment final :public Collider
{
private:
	//�n�_
	DirectX::SimpleMath::Vector3 m_strPos;
	//�I�_
	DirectX::SimpleMath::Vector3 m_endPos;
public:
	Segment(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false,
		DirectX::SimpleMath::Vector3 start = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3 end = DirectX::SimpleMath::Vector3::Zero);
	~Segment()override = default;

	//���[�J���n�_�擾
	DirectX::SimpleMath::Vector3 GetLocalStartPos();
	//���[�J���I�_�擾
	DirectX::SimpleMath::Vector3 GetLocalEndPos();
	//���[���h�n�_�擾
	DirectX::SimpleMath::Vector3 GetWorldStartPos();
	//���[���h�I�_�擾
	DirectX::SimpleMath::Vector3 GetWorldEndPos();
	//�n�_�ݒ�
	void SetStartPos(const DirectX::SimpleMath::Vector3& strpos) { m_strPos = strpos; }
	//�I�_�ݒ�
	void SetEndPos(const DirectX::SimpleMath::Vector3& endpos) { m_endPos = endpos; }
	//�x�N�g���擾
	DirectX::SimpleMath::Vector3 GetVector();
	//�����擾
	DirectX::SimpleMath::Vector3 GetDirection();
	//�����擾
	float GetLength();
	//���a�擾
	float GetRadius() override;
};