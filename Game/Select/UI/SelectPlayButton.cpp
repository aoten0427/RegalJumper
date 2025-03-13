// ================================================================ 
// �t�@�C���� : SelectPlayButton.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���ڍs�{�^��
// ================================================================
#include"pch.h"
#include"SelectPlayButton.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Subject.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
SelectPlayButton::SelectPlayButton(Canvas* canvas):Button(canvas,"SPlayButton",1)
	,
	m_bg{nullptr},
	m_ClickSubject{nullptr}
{
	SetPosition(DirectX::SimpleMath::Vector2(950, 600));
	SetSize(DirectX::SimpleMath::Vector2(350, 150));

	//�F�ύX�����쐬
	m_bg = GetScene()->AddObject<UserInterface>(canvas,"Quad",2);
	m_bg->SetPosition(DirectX::SimpleMath::Vector2(950, 600));
	m_bg->SetSize(DirectX::SimpleMath::Vector2(290, 114));
	m_bg->SetColor(DirectX::SimpleMath::Vector4(0.078f, 0.156f, 0.552, 0.2f));

	//�ʒm�쐬
	m_ClickSubject = AddComponent<Subject<>>(this, "SelectPlay");
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void SelectPlayButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//�F�ύX
	if (within)
	{
		m_bg->SetColor(DirectX::SimpleMath::Vector4(0.33, 1, 0.8, 0.5f));

	}
	else
	{
		m_bg->SetColor(DirectX::SimpleMath::Vector4(0.078f, 0.156f, 0.552, 0.2f));
	}
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void SelectPlayButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//�ʒm
		m_ClickSubject->Notify();
	}
}
