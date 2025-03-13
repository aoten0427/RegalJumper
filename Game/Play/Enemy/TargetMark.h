// ================================================================ 
// �t�@�C���� : TargetMark.h
// �쐬�� : �i�R�ɓV
// ���� :  �^�[�Q�b�g�\���}�[�N
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Camera;
class PrimitiveRenderer;
class Tween;

class TargetMark :public Object
{
private:
	//�`��f�[�^
	PrimitiveRenderer* m_renderer;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�傫��
	float m_size;
	//�ω��pTween
	Tween* m_tween;
public:
	//�R���X�g���N�^
	TargetMark(Scene* scene, Object* holder);
	//�f�X�g���N�^
	~TargetMark()override = default;
	//�`��
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//�J��
	void Open();
	//����
	void Close();
};