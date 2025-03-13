// ================================================================ 
// �t�@�C���� : SpiderModelEnter.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偂��o������Ƃ��̕`����
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"
#include"Base/Scene/Scene.h"

class CommonResources;
template<typename...Args>
class Observer;
class Tween;
class Sound;

class SpiderModelEnter :public SpiderModelState
{
private:
	struct TCBuff
	{
		DirectX::SimpleMath::Vector4 Time;
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
	//�ω��Đ��A��~�I�u�U�[�o�[
	Observer<Scene::State>* m_playbackObserver;
	//�ω��pTween
	Tween* m_tween;
	//���[�v�T�E���h
	Sound* m_warpSound;
public:
	//�R���X�g���N�^
	SpiderModelEnter(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//�f�X�g���N�^
	~SpiderModelEnter()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
	//�`�揈��
	void Render(const Camera& camera)override;
private:
	void CheckPlayBack(Scene::State state);
};