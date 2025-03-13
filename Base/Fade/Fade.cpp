// ================================================================ 
// �t�@�C���� : Fade.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �t�F�[�h���N���X
// ================================================================

#include"pch.h"
#include"Fade.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas"></param>
/// <param name="fadeName"></param>
Fade::Fade(Canvas* canvas, std::string fadeName):UserInterface(canvas)
	,
	m_state{State::Out},
	m_name{fadeName}
{
	//�t�F�[�h�}�l�[�W���ɓo�^
	FadeManager::GetInstance()->AddFade(this);
	//�`��I�[�_�[�ݒ�
	SetRenderOrder(20);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Fade::~Fade()
{
}

