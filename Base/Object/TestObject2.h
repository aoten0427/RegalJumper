#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"

class Rigidbody;
class Camera;
class Model3D;

class TestObject2 :public Object
{
	// ���C�g�̒萔�o�b�t�@�p�\����
	struct cbLight
	{
		DirectX::XMMATRIX lightViewProjection;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightPosition;		// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDirection;		// ���C�g�̕���
		DirectX::XMVECTOR lightAmbient;			// ���C�g�̊���
	};

	struct PlayerPosition
	{
		DirectX::SimpleMath::Vector4 Position;
	};
private:
	Rigidbody* m_rigidbody;

	ShaderSet m_shaderSet;

	Model3D* m_model;

	ShaderSet m_set;
	// �T���v��
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	cBuffer;
public:
	TestObject2(Scene* scene);
	~TestObject2();

	void ObjectUpdate(float deltatime)override;

	//Trigger����
	void OnTrigger(Collider* collider)override;
private:
	void ModelRender(const Camera& camera);

	void Move(float deltatime);

	void Test(int i);
};
