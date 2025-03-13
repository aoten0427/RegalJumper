#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"
#include"Libraries/Microsoft/RenderTexture.h"
#include"Libraries/MyLib/DepthStencil.h"
#include"Base/Resource/DepthResources.h"

class Rigidbody;
class Camera;
class Model3D;
class Thread;
class Animator;
class UserInterface;
class Sphere;

class TestObject :public Object
{
	struct CBuff
	{
		DirectX::SimpleMath::Vector4 light_pos;         // �����̈ʒu
		DirectX::SimpleMath::Vector4 camera_pos;	    // �J�����̈ʒu
		float k_diffuse;							    // �g�U���ˌW��
		float k_ambient;							    // �����W��
		float k_specular;							    // ���ʔ��ˌW��
		float roughness;							    // �e��
		DirectX::SimpleMath::Vector4 _DiffuseColor;		// �g�U���ːF
		DirectX::SimpleMath::Vector4 _SpecularColor;	// ���ʔ��ːF
		float complex_refractive_index;				    // ���ܗ�
		float bonus[3];
	};

	// ���C�g�̒萔�o�b�t�@�p�\����
	struct cbLight
	{
		DirectX::XMMATRIX lightViewProjection;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightPosition;		// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDirection;		// ���C�g�̕���
		DirectX::XMVECTOR lightAmbient;			// ���C�g�̊���
	};
private:
	Model3D* m_player;
	Model3D* m_box;

	ShaderSet m_shadowMap;
	ShaderSet m_shadowDraw;

	// ���C�g�̍��W
	DirectX::SimpleMath::Vector3 m_lightPosition;

	// �V���h�E�}�b�v�̃T�C�Y
	static constexpr int SHADOWMAP_SIZE = 1024;

	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	std::unique_ptr<DX::RenderTexture> m_shadowMapRT;

	// �V���h�E�}�b�v�p�i�f�v�X�X�e���V���j
	std::unique_ptr<mylib::DepthStencil> m_shadowMapDS;

	// �T���v��
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;


	std::unique_ptr<DepthResources> m_depth;

	UserInterface* m_ui;
	DirectX::SimpleMath::Vector2 m_pos;

	std::vector<Sphere*> m_mainSphere;

	std::vector<Sphere*> m_subSphere;
public:
	TestObject(Scene* scene);
	~TestObject();

	void ObjectUpdate(float deltatime)override;

	//Trigger����
	void OnCollision(Collider* collider)override;
	//�����߂�(�����o����)
	virtual void PushBack(DirectX::SimpleMath::Vector3 pushback);

	void ModelRender(const Camera& camera);


private:
	/*void Move(float deltatime);*/

	void Test(int i);

	std::vector<float> ClampedKnotVector(int p, int n);

	float BasisFunction(const std::vector<float>& u, int j, int k, float t, std::vector<std::vector<float>>& memo);

	// B�X�v���C���Ȑ����v�Z
	std::vector<DirectX::SimpleMath::Vector3> ComputeBSplineCurve(const std::vector<DirectX::SimpleMath::Vector3>& P, int n, float step = 0.01f);
};
