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
		DirectX::SimpleMath::Vector4 light_pos;         // 光源の位置
		DirectX::SimpleMath::Vector4 camera_pos;	    // カメラの位置
		float k_diffuse;							    // 拡散反射係数
		float k_ambient;							    // 環境光係数
		float k_specular;							    // 鏡面反射係数
		float roughness;							    // 粗さ
		DirectX::SimpleMath::Vector4 _DiffuseColor;		// 拡散反射色
		DirectX::SimpleMath::Vector4 _SpecularColor;	// 鏡面反射色
		float complex_refractive_index;				    // 屈折率
		float bonus[3];
	};

	// ライトの定数バッファ用構造体
	struct cbLight
	{
		DirectX::XMMATRIX lightViewProjection;	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightPosition;		// ライトの位置
		DirectX::XMVECTOR lightDirection;		// ライトの方向
		DirectX::XMVECTOR lightAmbient;			// ライトの環境光
	};
private:
	Model3D* m_player;
	Model3D* m_box;

	ShaderSet m_shadowMap;
	ShaderSet m_shadowDraw;

	// ライトの座標
	DirectX::SimpleMath::Vector3 m_lightPosition;

	// シャドウマップのサイズ
	static constexpr int SHADOWMAP_SIZE = 1024;

	// シャドウマップ用（レンダーテクスチャ）
	std::unique_ptr<DX::RenderTexture> m_shadowMapRT;

	// シャドウマップ用（デプスステンシル）
	std::unique_ptr<mylib::DepthStencil> m_shadowMapDS;

	// サンプラ
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

	//Trigger処理
	void OnCollision(Collider* collider)override;
	//押し戻し(押し出し量)
	virtual void PushBack(DirectX::SimpleMath::Vector3 pushback);

	void ModelRender(const Camera& camera);


private:
	/*void Move(float deltatime);*/

	void Test(int i);

	std::vector<float> ClampedKnotVector(int p, int n);

	float BasisFunction(const std::vector<float>& u, int j, int k, float t, std::vector<std::vector<float>>& memo);

	// Bスプライン曲線を計算
	std::vector<DirectX::SimpleMath::Vector3> ComputeBSplineCurve(const std::vector<DirectX::SimpleMath::Vector3>& P, int n, float step = 0.01f);
};
