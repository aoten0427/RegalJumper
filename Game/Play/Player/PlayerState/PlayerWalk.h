// ================================================================ 
// �t�@�C���� : PlayerWalk.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[���s���
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"
#include"Game/Parameter/PlayerParameter.h"

class CommonResources;
class DirectXInputs;
class Rigidbody;

class PlayerWalk :public PlayerState
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

	bool m_oldIsGraound;

	const PlayerParameter::Parameter* m_parameter;
public:
	//�R���X�g���N�^
	PlayerWalk(PlayerStateMachine* machine, Player* player);
	//�f�X�g���N�^
	~PlayerWalk() override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
private:
	void Move(float deltatime);
	void Shot();
};