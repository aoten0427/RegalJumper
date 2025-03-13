// ================================================================ 
// �t�@�C���� : PlayerMoveThread.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[���ł̈ړ����
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"
#include"Game/Parameter/PlayerParameter.h"

class CommonResources;
class DirectXInputs;
class Rigidbody;
template<typename...Args>
class Subject;

class PlayerMoveThread :public PlayerState
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
	//���ˎ��T�u�W�F�N�g
	Subject<>* m_conectSubject;
	//�p�����[�^
	const PlayerParameter::Parameter* m_parameter;
public:
	//�R���X�g���N�^
	PlayerMoveThread(PlayerStateMachine* machine, Player* player);
	//�f�X�g���N�^
	~PlayerMoveThread() override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
private:
	//�ړ�
	void Move(float deltatime);
};