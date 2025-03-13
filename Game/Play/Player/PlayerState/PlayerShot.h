// ================================================================ 
// �t�@�C���� : PlayerShot
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�V���b�g���
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"

class CommonResources;
class Sound;

class PlayerShot :public PlayerState
{
private:
	//�R�������\�[�X
	CommonResources* m_commonResources;
	//�v���C���[
	Player* m_player;
	//�V���b�g�T�E���h
	Sound* m_shotSound;
public:
	//�R���X�g���N�^
	PlayerShot(PlayerStateMachine* machine, Player* player);
	//�f�X�g���N�^
	~PlayerShot() override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
};