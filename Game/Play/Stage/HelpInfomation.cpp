// ================================================================ 
// �t�@�C���� : HelpInfomation.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w���v���e
// ================================================================
#include"pch.h"
#include"HelpInfomation.h"
#include"Base/Scene/Scene.h"
#include"Base/Screen.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="infomation">�C���t�H���[�V������</param>
HelpInfomation::HelpInfomation(Canvas* canvas,INFOMATION infomation):UserInterface(canvas)
	,
	m_size{DirectX::SimpleMath::Vector2::Zero}
{
	using namespace DirectX::SimpleMath;
	//�w�i����
	m_bg = GetScene()->AddObject<UserInterface>(canvas);
	m_bg->SetPosition(Vector2(Screen::CENTER_X, Screen::CENTER_Y));
	m_bg->SetSize(Vector2(Screen::WIDTH, Screen::HEIGHT));
	m_bg->SetColor(Vector4(1, 1, 1, 0.3f));
	m_bg->GetTransform()->SetParent(GetTransform());

	SetSize(m_size);
	SetRenderOrder(3);
	//�����摜�ǂݍ���
	switch (infomation)
	{
	case INFOMATION::SHOT:
		SetTexture("HelpInfomation1");
		break;
	case INFOMATION::MOVE:
		SetTexture("HelpInfomation2");
		break;
	case INFOMATION::JUMP:
		SetTexture("HelpInfomation3");
		break;
	case INFOMATION::SHOT2:
		SetTexture("HelpInfomation4");
		break;
	default:
		break;
	}

	m_tween = AddComponent<Tween>(this, true);
	SetActive(false);
}

/// <summary>
///	�A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void HelpInfomation::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetSize(m_size);
}

/// <summary>
/// �J��
/// </summary>
void HelpInfomation::Open()
{
	SetActive(true);
	m_tween->DoVector2(m_size, DirectX::SimpleMath::Vector2(1000, 500), 0.3f).SetEase(Easing::Ease::OutQuart);
}

/// <summary>
/// ����
/// </summary>
void HelpInfomation::Close()
{
	m_tween->DoVector2(m_size, DirectX::SimpleMath::Vector2(0,0), 0.15f).SetEase(Easing::Ease::InQuart).SetCompleteFunction([&]() {
		SetActive(false);
		GetScene()->ChangeState(Scene::State::PLAY);
		});
}
