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
	// ���C�g�̒萔�o�b�t�@�p�\����
	struct cbLight
	{
		DirectX::XMMATRIX lightViewProjection;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightPosition;		// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDirection;		// ���C�g�̕���
		DirectX::XMVECTOR lightAmbient;			// ���C�g�̊���
	};
private:
	//�R�������\�[�X
	CommonResources* m_commonResources;
	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	std::unique_ptr<DX::RenderTexture> m_shadowMapRT;
	//�[�x���\�[�X
	std::unique_ptr<DepthResources> m_depthResources;
	//�V���h�E�}�b�v�p�V�F�[�_�[
	ShaderSet m_shadowMapShader;
	// �T���v��
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;
	//
	ShadowMapData m_data;
public:
	ShadowMapManager(CommonResources* commonResources);
	~ShadowMapManager();

	ShadowMapData* GetShadowMapData();
	
	void Render(std::vector<Model3D*>& models, const Camera& camera);
};