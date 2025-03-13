#pragma once
#include"Base/Resource/ShaderManager.h"

class CommonResources;
namespace DX
{
	class RenderTexture;
}
class DepthResources;

class Model3D;
class Camera;

struct  ShadowMapData
{
	ID3D11ShaderResourceView* m_shaderResourcesView;
	ID3D11Buffer* m_cbuff;
	ID3D11SamplerState* m_sampler;
};

class ShadowMapManager
{
private:
	// ライトの定数バッファ用構造体
	struct cbLight
	{
		DirectX::XMMATRIX lightViewProjection;	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightPosition;		// ライトの位置
		DirectX::XMVECTOR lightDirection;		// ライトの方向
		DirectX::XMVECTOR lightAmbient;			// ライトの環境光
	};
private:
	//コモンリソース
	CommonResources* m_commonResources;
	// シャドウマップ用（レンダーテクスチャ）
	std::unique_ptr<DX::RenderTexture> m_shadowMapRT;
	//深度リソース
	std::unique_ptr<DepthResources> m_depthResources;
	//シャドウマップ用シェーダー
	ShaderSet m_shadowMapShader;
	// サンプラ
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;
	//
	ShadowMapData m_data;
public:
	ShadowMapManager(CommonResources* commonResources);
	~ShadowMapManager();

	ShadowMapData* GetShadowMapData();
	
	void Render(std::vector<Model3D*>& models, const Camera& camera);
};