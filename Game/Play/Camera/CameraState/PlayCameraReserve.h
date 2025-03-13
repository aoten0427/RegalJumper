// ================================================================ 
// �t�@�C���� : PlayCameraReserve.h
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���J�n���̃v���C�J�������
// ================================================================

#pragma once
#include"Game/Play/Camera/CameraState/PlayCameraState.h"
#include"Base/Scene/Scene.h"

class Tween;
template<typename...Args>
class Observer;



class PlayCameraReserve :public PlayCameraState
{
private:
	//�v���C�J����
	PlayCamera* m_camera;
	//���_
	DirectX::SimpleMath::Vector3 m_eyePotision;
	//������������
	DirectX::SimpleMath::Vector3 m_direction;
	//�ړ��pTween
	Tween* m_eyeTween;
	Tween* m_targetTween;
	//Tween�Đ���~�I�u�U�[�o�[
	Observer<Scene::State, Scene::State>* m_playbackObserver;
public:
	//�R���X�g���N�^
	PlayCameraReserve(PlayCameraStateMachine* machine, PlayCamera* camera);
	//�f�X�g���N�^
	~PlayCameraReserve()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
private:
	//�Đ����f
	void PlayBack(Scene::State type);
};