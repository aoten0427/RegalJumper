// ================================================================ 
// �t�@�C���� : PlayCameranNormal.h
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���v���C���̃v���C�J�������
// ================================================================
#pragma once
#include"Game/Play/Camera/CameraState/PlayCameraState.h"


class Segment;
template<typename...Args>
class Observer;

class PlayCameraNormal :public PlayCameraState
{
private:
	//�v���C�J����
	PlayCamera* m_camera;
	//����
	Segment* m_collider;
	//�v���C���[����̋���
	float m_length;
	//��]��
	float m_rotationY;
	float m_rotationX;
	//�߂荞�ݗ�
	DirectX::SimpleMath::Vector3 m_pushback;
	//
	Observer<>* m_resetObserver;
public:
	//�R���X�g���N�^
	PlayCameraNormal(PlayCameraStateMachine* machine, PlayCamera* camera);

	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
private:
	//�}�E�X�R���g���[��
	void MouseControl();
	//���Z�b�g
	void Reset();
};