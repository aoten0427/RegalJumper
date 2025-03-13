#include"pch.h"
#include"PlayScene.h"
#include"Base/CommonResources.h"
#include"Game/GameManager.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/UI/PlayCanvas.h"
#include"Game/Play/PlayCenter.h"
#include"Game/Play/Player/PlayerCenter.h"
#include"Game/Play/Stage/StageCenter.h"
#include"Game/Parameter/ParameterManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">�R�������\�[�X</param>
PlayScene::PlayScene(CommonResources* resources) :Scene(resources,"Play")
{
	ParameterManager::LoadDaata();
	//�J��������
	m_camera = AddObject<PlayCamera>(this);
	//�L�����o�X����
	m_canvas = AddObject<PlayCanvas>(this);
	//�Ǘ��Ґ���
	AddObject<PlayCenter>(this);
	//�v���C���[����
	AddObject<PlayerCenter>(this);
	//�X�e�[�W����
	AddObject<StageCenter>(this);

	//�J�[�\�����I�t�ɂ���
	GameManager::GetInstance()->ViewCursor(false);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void PlayScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

