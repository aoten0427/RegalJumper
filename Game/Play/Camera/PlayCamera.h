// ================================================================ 
// �t�@�C���� : PlayCamera.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���J����
// ================================================================

#pragma once
#include"Base/Camera/Camera.h"

class PlayCameraStateMachine;
class Player;
class Segment;

class PlayCamera :public Camera
{
public:
	//�v���W�F�N�V����matrix�擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const override { return m_projection; };
	//�r���[matrix�擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix()  const override { return m_view; }
	//�n�_�Z�b�g
	void SetEyePosition(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }
	//���_�擾
	const DirectX::SimpleMath::Vector3& GetEyePosition()  const override { return m_eye; }
	//�^�[�Q�b�g�Z�b�g
	void SetTargetPosition(DirectX::SimpleMath::Vector3 target) { m_target = target; }
	//�^�[�Q�b�g�擾
	const DirectX::SimpleMath::Vector3& GetTargetPosition()  const override { return m_target; }
	//�������擾
	const DirectX::SimpleMath::Vector3& GetUpPosition()  const override { return m_up; }
	void SetRotataionY(float rotation) { m_rotationY = rotation; }
	float GetRotationY()const { return m_rotationY; }
	//�v���C���[�Z�b�g
	void SetPlayer(Player* player) { m_player = player; }
	//�v���C���[�擾
	Player* GetPlayer()const { return m_player; }
private:
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// �J�����̓��̕���
	DirectX::SimpleMath::Vector3 m_up;
	//��]��Y
	float m_rotationY;
	//�X�e�[�g�}�V��
	std::unique_ptr<PlayCameraStateMachine> m_machine;
	//����
	Segment* m_collider;
	//
	Player* m_player;
public:
	//�R���X�g���N�^
	PlayCamera(Scene* scene);
	//�ł��Ɗy
	~PlayCamera()override = default;
	//���X�V
	void CalculationView() override;
};