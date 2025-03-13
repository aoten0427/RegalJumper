// ================================================================ 
// �t�@�C���� : SelectScene.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[��
// ================================================================
#include"pch.h"
#include"SelectScene.h"
#include"Base/Camera/DebugCamera.h"
#include"Game/GameManager.h"
#include"Game/Select/UI/SelectCanvas.h"
#include"Game/Select/SelectCenter.h"
#include"Game/Select/Object/SelectObjects.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">�R�������\�[�X</param>
SelectScene::SelectScene(CommonResources* resources) :Scene(resources,"Select")
{
	//�J��������
	m_camera = AddObject<Camera>(this);
	//�L�����o�X����
	m_canvas = AddObject<SelectCanvas>(this);
	//�Ǘ��Ґ���
	AddObject<SelectCenter>(this);
	//�I�u�W�F�N�g����
	AddObject<SelectObjects>(this);

	//�J�[�\�����I���ɂ���
	GameManager::GetInstance()->ViewCursor(true);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void SelectScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

