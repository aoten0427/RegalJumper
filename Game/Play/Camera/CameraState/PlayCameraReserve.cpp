// ================================================================ 
// �t�@�C���� : PlayCameraReserve.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���J�n���̃v���C�J�������
// ================================================================
#include"pch.h"
#include"PlayCameraReserve.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Player/Player.h"

//�����ړ�����
constexpr float MOVE_TIME = 3.5f;
//�J���������ʒu
constexpr DirectX::SimpleMath::Vector3 START_POS{ 0,800,42 };
//�J�����ړI�n
constexpr DirectX::SimpleMath::Vector3 DESTINATION{ 0,4,40 };
//�ڐ������ʒu
constexpr DirectX::SimpleMath::Vector3 TARGET_START{ 0,-0.5f,-1.0f };
//�ڐ��ړI�n
constexpr DirectX::SimpleMath::Vector3 TARGET_DESTINATION{ 0, -0.0003f, -1 };

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�X�e�[�g�}�V��</param>
/// <param name="camera">�J����</param>
PlayCameraReserve::PlayCameraReserve(PlayCameraStateMachine* machine, PlayCamera* camera) :PlayCameraState(machine, camera)
,
m_camera{ camera },
m_eyePotision{ START_POS },
m_direction{ TARGET_START }
{
	//Tween�쐬
	m_eyeTween = m_camera->AddComponent<Tween>(m_camera);
	m_targetTween = m_camera->AddComponent<Tween>(m_camera);
	//���_�ړ�
	m_eyeTween->DoVector3(m_eyePotision, DESTINATION, MOVE_TIME).SetEase(Easing::Ease::OutCirc).SetCompleteFunction([&]() {
		m_camera->GetPlayer()->Entery();
		});
	m_eyeTween->Pause();
	//�ڕW�_�ړ�
	m_targetTween->DoVector3(m_direction, TARGET_DESTINATION, MOVE_TIME).SetEase(Easing::Ease::OutQuad).SetDelay(0.5f);
	m_targetTween->Pause();
	//�Đ����f�C�x���g�쐬
	m_playbackObserver = m_camera->AddComponent<Observer<Scene::State, Scene::State>>(m_camera);
	m_playbackObserver->RegistrationSubject("SceneStateChange");
	m_playbackObserver->SetFunction(std::bind(&PlayCameraReserve::PlayBack, this, std::placeholders::_1));
}

/// <summary>
/// ���O�X�V
/// </summary>
void PlayCameraReserve::PreUpdate()
{
	//���_�ƖڕW�_��ݒ�
	m_camera->SetEyePosition(START_POS);
	m_camera->SetTargetPosition(TARGET_START + START_POS);

}

/// <summary>
/// �A�b�v�f�[�g�@���_�A�ڕW�_�X�V
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void PlayCameraReserve::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_camera->SetEyePosition(m_eyePotision);
	m_camera->SetTargetPosition(m_direction + m_eyePotision);
}

/// <summary>
/// ����X�V
/// </summary>
void PlayCameraReserve::PostUpdate()
{

}

/// <summary>
/// �Đ����f
/// </summary>
/// <param name="type">�ω���̃V�[���̏��</param>
void PlayCameraReserve::PlayBack(Scene::State type)
{
	//�J�n��ԂȂ�Tween�Đ�
	if (type == Scene::State::RESERVE)
	{
		m_eyeTween->Play();
		m_targetTween->Play();
	}
	else if (type == Scene::State::PLAY)
	{
		ChangeState(State::NOMAL);
	}
	//�ȊO�Ȃ�~�߂�
	else
	{
		m_eyeTween->Pause();
		m_targetTween->Pause();
	}
}
