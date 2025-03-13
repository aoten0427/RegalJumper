// ================================================================ 
// �t�@�C���� : SpiderModelExit.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偂���������Ƃ��̕`����
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"

class CommonResources;
template<typename...Args>
class Subject;
class Tween;
class Sound;

class SpiderModelExit :public SpiderModelState
{
public:
	struct CBuff
	{
		DirectX::SimpleMath::Vector2 Time;
		DirectX::SimpleMath::Vector2 CenterHeight;
	};
private:
	//�R�������\�[�X
	CommonResources* m_resources;
	//�X�p�C�_�[���f��
	SpiderModels* m_spiderModel;
	//�V�F�[�_�[�֌W
	ShaderSet m_shaderSet;
	//���U�C�N�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mosaicTexture;
	//�^�C�}�[�p�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_tcBuff;
	//�u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	//�ω��p�^�C�}�[
	float m_timer;
	//�I���ʒm
	Subject<>* m_finishSubject;
	//�ω��pTween
	Tween* m_tween;
	//���[�v�T�E���h
	Sound* m_warpSound;
public:
	//�R���X�g���N�^
	SpiderModelExit(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//�f�X�g���N�^
	~SpiderModelExit()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
	//�`�揈��
	void Render(const Camera& camera)override;
};