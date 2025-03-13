// ================================================================ 
// �t�@�C���� : SelectObjects.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[���ł̃I�u�W�F�N�g
// ================================================================
#include"pch.h"
#include"SelectObjects.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"
#include"Game/Play/Stage/Skydome.h"
#include"Game/Play/Stage/Box.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
SelectObjects::SelectObjects(Scene* scene):Object(scene)
{
	using namespace DirectX::SimpleMath;
	//�v���C�V�[���J�ڃI�u�U�[�o�쐬
	m_toPlayObserver = AddComponent<Observer<>>(this);
	m_toPlayObserver->SetFunction([&]() {ToPlay(); });
	m_toPlayObserver->RegistrationSubject("SelectPlay");

	//�X�J�C�h�[������
	Skydome* dome = scene->AddObject<Skydome>(scene);
	dome->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//�v���C���[����
	m_model = scene->AddObject<SpiderModels>(scene);
	m_model->GetTransform()->SetPosition(Vector3(2.8f, -0.5f, 11));
	m_model->GetTransform()->TransRotate(Vector3::UnitY, -5);
	//�u���b�N����
	Box* box = scene->AddObject<Box>(scene);
	box->GetTransform()->SetPosition(Vector3(0, -7.5f, 0));
	box->GetTransform()->SetScale(Vector3(20.0f, 5.0f, 20.0f));
}

/// <summary>
/// �v���C�V�[���J�ڏ���
/// </summary>
void SelectObjects::ToPlay()
{
	m_model->ChangeState(SpiderModelState::RenderType::EXIT);
}
