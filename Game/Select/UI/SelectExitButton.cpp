// ================================================================ 
// �t�@�C���� : SelectExitButton.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[���ޏo�{�^��
// ================================================================
#include"pch.h"
#include"SelectExitButton.h"
#include"Base/Scene/Scene.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
SelectExitButton::SelectExitButton(Canvas* canvas):Button(canvas,"SelectQuit")
{
	using namespace DirectX::SimpleMath;
	SetSize(Vector2(150, 90));
	SetPosition(Vector2(75, 45));

	m_str = GetScene()->AddObject<UserInterface>(canvas, "SelectQuit2", 2);
	m_str->SetSize(Vector2(150, 90));
	m_str->SetPosition(Vector2(75, 45));
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void SelectExitButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//�F�ύX
	if (within)
	{
		m_str->SetColor(DirectX::SimpleMath::Vector4(0.33, 1, 0.8, 1.0f));
	}
	else
	{
		m_str->SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void SelectExitButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//�t�F�[�h���N�����^�C�g���V�[����
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::TITLE);
			});
	}
}
