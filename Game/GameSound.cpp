// ================================================================ 
// �t�@�C���� : GameSound.cpp
// �쐬�� : �i�R�ɓV
// ���� :  BGM�̊Ǘ�
// ================================================================
#include"pch.h"
#include"GameSound.h"
#include"Base/Scene/Scene.h"
#include"Base/Sound/Sound.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
GameSound::GameSound(Scene* scene):Object(scene)
{
	m_titileSound = AddComponent<Sound>(this, Sound::SoundType::BGM, "Title", true);
	m_playSound = AddComponent<Sound>(this, Sound::SoundType::BGM, "Play", false);
}

/// <summary>
/// �V�[���̐؂�ւ��ɉ�����BGM�ؑ�
/// </summary>
/// <param name="scene">�ύX�V�[��</param>
void GameSound::LoadScene(Scene* scene)
{
	switch (scene->GetSceneID())
	{
	case Scene::SceneID::TITLE:
		m_titileSound->Play();
		m_playSound->Pause();
		break;
	case Scene::SceneID::SELECT:
		m_titileSound->Play();
		m_playSound->Pause();
		break;
	case Scene::SceneID::PLAY:
		m_titileSound->Pause();
		m_playSound->Play();
		break;
	case Scene::SceneID::RESULT:
		m_playSound->Pause();
		break;
	default:
		break;
	}
}
