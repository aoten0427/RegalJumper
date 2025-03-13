// ================================================================ 
// �t�@�C���� : GameCanvas.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���Ŏg���L�����o�X��b
// ================================================================

#include"pch.h"
#include"GameCanvas.h"
#include"Base/Object/UnbreakableManager.h"
#include"Game/Title/UI/GameFade.h"
#include"Game/Option/Option.h"
#include"Game/Cursor/Cursor.h"
#include"Game/GameSound.h"
#include"Game/Play/UI/PlayFade.h"

/// <summary>
/// �R���X�g���N�^ �e��j��I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="scene">�����V�[��</param>
GameCanvas::GameCanvas(Scene* scene) :Canvas(scene)
{
	//�t�F�[�h�쐬
	UnbreakableManager::GetInstance()->AddObject<GameFade>("NormalFade", this);
	UnbreakableManager::GetInstance()->AddObject<PlayFade>("PlayFade", this);
	//�I�v�V�����쐬
	UnbreakableManager::GetInstance()->AddObject<Option>("Option", this);
	//�J�[�\���쐬
	UnbreakableManager::GetInstance()->AddObject<Cursor>("Cursor", this);
	//�T�E���h�쐬
	UnbreakableManager::GetInstance()->AddObject<GameSound>("GameSound", scene);
}
