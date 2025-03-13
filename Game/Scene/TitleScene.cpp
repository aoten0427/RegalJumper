// ================================================================ 
// �t�@�C���� : TitleScene.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g���V�[��
// ================================================================
#include"pch.h"
#include"TitleScene.h"
#include"Base/CommonResources.h"
#include"Base/Camera/DebugCamera.h"
#include"Game/Title/UI/TitleCanvas.h"
#include"Game/Title/TitleCenter.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">�R�������\�[�X</param>
TitleScene::TitleScene(CommonResources* resources):Scene(resources,"Title")
{
	//�J��������
	m_camera = AddObject<DebugCamera>(this);
	//�L�����o�X����
	m_canvas = AddObject<TitleCanvas>(this);
	//�Ǘ��Ґ���
	AddObject<TitleCenter>(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void TitleScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}


