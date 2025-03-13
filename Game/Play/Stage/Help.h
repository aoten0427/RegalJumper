// ================================================================ 
// �t�@�C���� : Help.h
// �쐬�� : �i�R�ɓV
// ���� :  �w���v���
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Scene/Scene.h"

class Camera;
class PrimitiveRenderer;
class HelpInfomation;

class Help :public Object
{
public:
	ObjectTag GetTag() { return ObjectTag::Help; };
private:
	//�\���֌W
	PrimitiveRenderer* m_renderer;
	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//���_
	DirectX::VertexPositionTexture m_vertexs[4];
	//�ڐG�L���t���O
	bool m_isContactActive;
	//�C���t�H���[�V����
	HelpInfomation* m_infomation;
	//
	bool m_biginFinish;
public:
	//�R���X�g���N�^
	Help(Scene* scene, int infomationNum,bool begin = false);
	//�f�X�g���N�^
	~Help()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
	//�`��
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//Trigger���s�L��
	bool IsTriggerAct(Collider* collider)override;
	//Trigger����
	void OnTrigger(Collider* collider)override;

	void BeginOpen(Scene::State current, Scene::State old);
};