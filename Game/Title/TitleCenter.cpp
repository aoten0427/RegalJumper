// ================================================================ 
// �t�@�C���� :TitleCenter.cpp 
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g���V�[�����Ǘ�
// ================================================================
#include"pch.h"
#include"TitleCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonResources.h"
#include"Base/Event/Observer.h"
#include"Base/Sound/Sound.h"
#include"Base/Input/DirectXInputs.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
TitleCenter::TitleCenter(Scene* scene) :Object(scene)
{
	m_begin = AddComponent<Observer<>>(this);
	m_begin->SetFunction([&]() {GetScene()->ChangeState(Scene::State::PLAY); });
	m_begin->RegistrationSubject("Reserve");
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void TitleCenter::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::Escape))
	{
		PostQuitMessage(0);
	}
}
