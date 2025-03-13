// ================================================================ 
// �t�@�C���� : PrimitiveRenderer.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���~�e�B�u�o�b�`�ł̕`����s��
// ================================================================

#pragma once
#include"Base/Component/Component.h"
#include"Base/Config.h"

class Camera;

class PrimitiveRenderer :public Component
{
public:
	//UI����擾
	bool GetisUiRender()const { return m_isUi; }
	//�`��I�[�_�[�擾
	const int& GetRenderOrder() const { return m_renderOrder; }
	//�摜�擾
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }
	//�ʕ`��Z�b�g
	void SetRender(std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> render) { m_render = render; }
private:
	//UI����
	bool m_isUi;
	//�`��I�[�_�[
	int m_renderOrder;
	//�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//�ʕ`��
	std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> m_render;
public:
	//�R���X�g���N�^
	PrimitiveRenderer(Object* object,std::string filename = Config::NONE_FILE ,int renderOrder = 0, bool ui = false);
	//�f�X�g���N�^
	~PrimitiveRenderer();

	//�`��
	virtual void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//�摜���[�h
	void Load(std::string filename);
	//�`��I�[�_�[�Z�b�g
	void SetRenderOrder(int order);
	//�V�[���؂�ւ��C�x���g
	void LoadScene(Scene* scene);
};
