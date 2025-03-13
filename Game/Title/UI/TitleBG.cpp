// ================================================================ 
// �t�@�C���� : TitleBG.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g���̔w�i�A���S
// ================================================================
#include"pch.h"
#include"TitleBG.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
TitleBG::TitleBG(Canvas* canvas):UserInterface(canvas)
	,
	m_logo{nullptr},
	m_timer{}
{
	using namespace DirectX::SimpleMath;

	//�w�i�ݒ�
	SetTexture("TitleBG");
	SetSize(Vector2(Screen::WIDTH,Screen::HEIGHT));

	//���S�ݒ�
	m_logo = GetScene()->AddObject<UserInterface>(canvas,"Logo",1);
	m_logo->SetPosition(Vector2(400, 300));
	m_logo->SetSize(Vector2(900, 510));

	//�V�F�[�_�[��ύX
	SetPixelShader("TitleFramePS.cso");
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void TitleBG::ObjectUpdate(float deltatime)
{
	//�^�C�}�[��ύX
	m_timer += deltatime / 4;
	SetFreeElement(DirectX::SimpleMath::Vector4(m_timer, 0, 0, 0));
}
