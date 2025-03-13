// ================================================================ 
// �t�@�C���� : PlayCameranNormal.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���v���C���̃v���C�J�������
// ================================================================
#include"pch.h"
#include"PlayCameraNormal.h"
#include"Base/Base.h"
#include"Base/Event/Observer.h"
#include"Base/CommonManager/CollisonManager.h"
#include"Game/GameManager.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Player/Player.h"

//�v���C���[�Ƃ̋���
constexpr float CAMERA_LENTH = 40.0f;
//�J�����ʒu�̈ړ����x
constexpr float CAMERA_SPEED = 0.6f;
//�}�E�X�Œ�l
constexpr int MOUSE_POSITION = 400;
//�J������]�ő�l
constexpr float CAMERA_ROTETO_MAX = 89.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�X�e�[�g�}�V��</param>
/// <param name="camera">�J����</param>
PlayCameraNormal::PlayCameraNormal(PlayCameraStateMachine* machine, PlayCamera* camera) :PlayCameraState(machine, camera)
,
m_camera{ camera },
m_length{ CAMERA_LENTH },
m_rotationX{ 0 },
m_rotationY{ 0 }
{
	using namespace DirectX::SimpleMath;
	//���_�A�ڕW�_�̃Z�b�g
	m_camera->SetEyePosition(Vector3(0, 5, 5));
	m_camera->SetTargetPosition(Vector3::Zero);
	//�R���C�_�[����
	m_collider = m_camera->GetComponent<Segment>();
	//�I�u�U�[�o�[
	m_resetObserver = m_camera->AddComponent<Observer<>>(m_camera);
	m_resetObserver->SetFunction([&]() {Reset(); });
	m_resetObserver->RegistrationSubject("PlayReset");
}

/// <summary>
/// ���O�X�V
/// </summary>
void PlayCameraNormal::PreUpdate()
{
	SetCursorPos(MOUSE_POSITION, MOUSE_POSITION);
	Update(0.0f);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void PlayCameraNormal::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	if (m_camera->GetScene()->GetState() != Scene::State::PLAY)return;

	//�Œ苗�����Z����ΐL�΂�
	if (m_length < CAMERA_LENTH)
	{
		m_length += CAMERA_SPEED;
	}
	//�v���C���[�̏�����Ƀ^�[�Q�b�g���Z�b�g
	Vector3 target = m_camera->GetPlayer()->GetTransform()->GetWorldPosition();
	target += Vector3(0, 2.0f, 0);
	//�}�E�X����
	MouseControl();
	//���搧��
	if (m_rotationX >= CAMERA_ROTETO_MAX)m_rotationX = CAMERA_ROTETO_MAX;
	if (m_rotationX <= -CAMERA_ROTETO_MAX)m_rotationX = -CAMERA_ROTETO_MAX;
	//Y���̉�]���v�Z
	Quaternion rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(m_rotationY));
	//��]�����ɍ��킹�Ďn�_���ړ�
	Vector3 eye = Vector3::UnitZ * m_length;
	eye = DirectX::XMVector3Rotate(eye, rotate);
	//X���̉�]���v�Z
	Vector3 axisX = DirectX::XMVector3Rotate(Vector3::UnitX, rotate);
	rotate = Quaternion::CreateFromAxisAngle(axisX, DirectX::XMConvertToRadians(m_rotationX));
	//�n�_����]
	eye = DirectX::XMVector3Rotate(eye, rotate);
	//�^�[�Q�b�g����������
	eye += target;

	//�R���C�_�[�̎n�_�ƏI�_��ݒ�
	m_camera->GetTransform()->SetPosition(eye);
	m_collider->SetStartPos(Vector3::Zero);
	m_collider->SetEndPos(target - m_camera->GetTransform()->GetPosition());



	//�߂荞�݂悤�̓����蔻��
	m_camera->GetScene()->GetCollisionManager()->RayCollision(m_collider, CollisionType::COLLISION, &m_pushback);
	if (m_pushback.Length() != 0)
	{
		//�X�e�[�W�ɍ��킹�ĉ����߂�
		m_length -= m_pushback.Length();
		eye -= (m_pushback * 1.05f);
		m_pushback = Vector3::Zero;
	}

	m_camera->SetEyePosition(eye);
	m_camera->SetTargetPosition(target);
}

/// <summary>
/// ����X�V
/// </summary>
void PlayCameraNormal::PostUpdate()
{
}

/// <summary>
/// �}�E�X����
/// </summary>
void PlayCameraNormal::MouseControl()
{
	using namespace DirectX::SimpleMath;
	//�J�[�\���̈ʒu���擾
	POINT current;
	GetCursorPos(&current);
	//�O�t���[������̍������擾
	Vector2 value;
	value.x = MOUSE_POSITION - static_cast<float>(current.x);
	value.y = MOUSE_POSITION - static_cast<float>(current.y);
	//���x�擾
	float sensitivity = GameManager::GetInstance()->GetSensitivity() * 0.2f + 0.01f;
	//��]�ʂɉ��Z
	m_rotationY += value.x * sensitivity;
	m_rotationX += value.y * sensitivity;
	//�}�E�X�̈ʒu���Œ�
	SetCursorPos(MOUSE_POSITION, MOUSE_POSITION);
	m_camera->SetRotataionY(m_rotationY);
}

void PlayCameraNormal::Reset()
{
	m_rotationX = 0;
	m_rotationY = 0;
}
