// ================================================================ 
// �t�@�C���� : RenderManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �`����s��
// ================================================================

#pragma once
#include"Base/CommonManager/ShadowMapManager.h"
#include"Base/CommonManager/ShadowMapManager.h"

class CommonResources;
class Camera;
class Model3D;
class PrimitiveRenderer;


class RenderManager
{
private:
	CommonResources* m_commonResources;
	//�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
	//3D���f��
	std::vector<Model3D*>  m_model3Ds;
	//�����_���[
	std::vector<PrimitiveRenderer*> m_primitiveRenderer;
	//�V���h�E�}�b�v
	std::unique_ptr<ShadowMapManager> m_shadowMap;
public:
	//�R���X�g���N�^
	RenderManager(CommonResources* commonResources);
	//�f�X�g���N�^
	~RenderManager() = default;

	//3D���f���̒ǉ��ƍ폜
	void AddModel3D(Model3D* model3D);
	void RemoveModel3D(Model3D* model3D);
	//�`�揇�ύX
	void ChangeRenderOrder(Model3D* model3D);

	//�����_���[�ǉ��ƍ폜
	void AddPrimitiveRenderer(PrimitiveRenderer* render);
	void RemovePrimitiveRenderer(PrimitiveRenderer* render);
	//�`�揇�ύX
	void ChangeRenderOrder(PrimitiveRenderer* render);

	//�`��
	void Render(const Camera& camera);

	ShadowMapData* GetShadowData() { return m_shadowMap->GetShadowMapData(); }
};