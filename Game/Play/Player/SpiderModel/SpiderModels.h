// ================================================================ 
// �t�@�C���� : SpiderModel.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̃��f�����Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"

class Camera;
class SpiderModelParts;
class SpiderModelStateMachine;
class SpiderAnimatorCenter;

class SpiderModels:public Object
{
public:
	//���C�g���
	struct CBLight
	{
		DirectX::SimpleMath::Vector4 LightPosition;         // �����̈ʒu
		DirectX::SimpleMath::Vector4 CameraPosition;	    // �J�����̈ʒu
		float Diffuse;									    // �g�U���ˌW��
		float Ambient;							            // �����W��
		float Specular;							            // ���ʔ��ˌW��
		float Roughness;							        // �e��
		DirectX::SimpleMath::Vector4 DiffuseColor;		    // �g�U���ːF
		DirectX::SimpleMath::Vector4 SpecularColor;	        // ���ʔ��ːF
		float complex_refractive_index;				        // ���ܗ�
		float bonus[3];
	};
public:
	//�S�Ẵp�[�c��n��
	std::vector<SpiderModelParts*>& GetModelParts() { return m_parts; }
	//���C�g�f�[�^��n��
	CBLight& GetLightData() { return m_lightdata; }
	//�A�j���[�^�[��Ԃ�
	SpiderAnimatorCenter* GetAnimator()const { return m_animation.get(); }
	//�z���_�[��Ԃ�
	Object* GetHolder() { return m_holder; }
private:
	Object* m_holder;
	//�p�[�c�S��
	std::vector<SpiderModelParts*> m_parts;
	//�e�p�[�c
	SpiderModelParts* m_body;
	SpiderModelParts* m_head;
	std::vector<SpiderModelParts*> m_legs;
	//�X�e�[�g�}�V��
	std::unique_ptr<SpiderModelStateMachine> m_machine;
	//���C�e�B���O���
	CBLight m_lightdata;
	//�A�j���[�V�����N���X
	std::unique_ptr<SpiderAnimatorCenter> m_animation;
public:
	//�R���X�g���N�^
	SpiderModels(Scene* scene,Object* holder = nullptr);
	//�f�X�g���N�^
	~SpiderModels()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//�`��
	void Render(const Camera& camera);
	//��ԕω�
	void ChangeState(SpiderModelState::RenderType state);
private:
	//�f�[�^�ǂݍ���
	void LoadData();
};