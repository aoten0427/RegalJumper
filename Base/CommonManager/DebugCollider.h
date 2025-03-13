// ================================================================ 
// �t�@�C���� : DebugCollider.h
// �쐬�� : �i�R�ɓV
// ���� :  �R���C�_�[�f�o�b�O�\��
// ================================================================

#pragma once
#include"Base/Component/Collider/Collider.h"

class Camera;

class DebugCollider
{
private:
	//�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//�e�R���C�_�[
	std::unordered_set<AABB*> m_aabb;
	std::unordered_set<OBB*>  m_obb;
	std::unordered_set<Sphere*> m_sphere;
	std::unordered_set<Segment*> m_segment;
public:
	//�R���X�g���N�^
	DebugCollider(ID3D11Device* device, ID3D11DeviceContext* context);
	//�f�X�g���N�^
	~DebugCollider() = default;
	//�����_�[
	void Render(ID3D11DeviceContext* context,
		DirectX::CommonStates* commonStates,
		const Camera& camera,
		const DirectX::XMVECTOR& color = DirectX::Colors::White);
	//�R���C�_�[�ǉ�
	void AddCollider(Collider* collider);
	//�R���C�_�[�폜
	void RemoveCollider(Collider* collider);
};