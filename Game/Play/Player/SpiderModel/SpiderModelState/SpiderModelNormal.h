// ================================================================ 
// �t�@�C���� : SpiderModelNormal.h
// �쐬�� : �i�R�ɓV
// ���� :  Select��ʂł̒w偂̕`����
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"

class CommonResources;

class SpiderModelNormal :public SpiderModelState
{
private:
	//�R�������\�[�X
	CommonResources* m_resources;
	//�X�p�C�_�[���f��
	SpiderModels* m_spiderModel;
	//�V�F�[�_�[�֌W
	ShaderSet m_shaderSet;
public:
	//�R���X�g���N�^
	SpiderModelNormal(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//�f�X�g���N�^
	~SpiderModelNormal()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
	//�`�揈��
	void Render(const Camera& camera)override;
};