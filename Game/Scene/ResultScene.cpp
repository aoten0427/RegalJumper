// ================================================================ 
// �t�@�C���� : ResultScene.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�V�[��
// ================================================================
#include"pch.h"
#include"ResultScene.h"
#include"Base/Camera/DebugCamera.h"
#include"Game/Result/UI/ResultCanvas.h"
#include"Game/Result/ResultCenter.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">�R�������\�[�X</param>
ResultScene::ResultScene(CommonResources* resources) :Scene(resources,"Result")
{
	//�J��������
	m_camera = AddObject<DebugCamera>(this);
	//�L�����o�X����
	m_canvas = AddObject<ResultCanvas>(this);
	//�Ǘ��Ґ���
	AddObject<ResultCenter>(this);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void ResultScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

