// ================================================================ 
// �t�@�C���� : PlayerIdle
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�ҋ@���
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"
#include"Game/Parameter/PlayerParameter.h"

class CommonResources;
class DirectXInputs;
class Rigidbody;

class PlayerIdle :public PlayerState
{
private:
	//�R�������\�[�X
	CommonResources* m_commonResources;
	//���͋@�\
	DirectXInputs* m_input;
	//�v���C���[
	Player* m_player;
	//�v���C���[���W�b�h�{�f�B
	Rigidbody* m_playerRigidbody;
	//�p�����[�^
	const PlayerParameter::Parameter* m_parameter;
public:
	//�R���X�g���N�^
	PlayerIdle(PlayerStateMachine* machine, Player* player);
	//�f�X�g���N�^
	~PlayerIdle() override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
private:
	//�ړ��x��
	void Operation();
	//����
	void Shot();
};