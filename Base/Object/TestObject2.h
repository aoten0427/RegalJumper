#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"

class Rigidbody;
class Camera;
class Model3D;

class TestObject2 :public Object
{
	// ライトの定数バッファ用構造体
	struct cbLight
	{
		DirectX::XMMATRIX lightViewProjection;	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightPosition;		// ライトの位置
		DirectX::XMVECTOR lightDirection;		// ライトの方向
		DirectX::XMVECTOR lightAmbient;			// ライトの環境光
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
	// サンプラ
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	cBuffer;
public:
	TestObject2(Scene* scene);
	~TestObject2();

	void ObjectUpdate(float deltatime)override;

	//Trigger処理
	void OnTrigger(Collider* collider)override;
private:
	void ModelRender(const Camera& camera);

	void Move(float deltatime);

	void Test(int i);
};
