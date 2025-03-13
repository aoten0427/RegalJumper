// ================================================================ 
// �t�@�C���� : PlayCamera.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���J����
// ================================================================
#include"pch.h"
#include"PlayCamera.h"
#include"Base/Screen.h"
#include"Base/Component/Collider/Collider.h"
#include"Game/Play/Camera/CameraState/PlayCameraStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
PlayCamera::PlayCamera(Scene* scene):Camera(scene)
	,
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{},
	m_rotationY{},
	m_machine{},
	m_collider{nullptr},
	m_player{nullptr}
{
	using namespace DirectX::SimpleMath;

	//�ˉe�s����v�Z
	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.005f, 4500.0f
	);
	//����쐬
	AddComponent<Segment>(this, CollisionType::TRIGGER,nullptr,false);
	//�X�e�[�g�}�V���쐬
	m_machine = std::make_unique<PlayCameraStateMachine>(this);

	m_up = Vector3::UnitY;
}

/// <summary>
/// ���X�V
/// </summary>
void PlayCamera::CalculationView()
{
	//�X�e�[�g�}�V���X�V
	m_machine->Update(0);
	//�r���[�s��쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}


