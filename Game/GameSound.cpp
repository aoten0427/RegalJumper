// ================================================================ 
// ファイル名 : GameSound.cpp
// 作成者 : 景山碧天
// 説明 :  BGMの管理
// ================================================================
#include"pch.h"
#include"GameSound.h"
#include"Base/Scene/Scene.h"
#include"Base/Sound/Sound.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
GameSound::GameSound(Scene* scene):Object(scene)
{
	m_titileSound = AddComponent<Sound>(this, Sound::SoundType::BGM, "Title", true);
	m_playSound = AddComponent<Sound>(this, Sound::SoundType::BGM, "Play", false);
}

/// <summary>
/// シーンの切り替えに応じてBGM切替
/// </summary>
/// <param name="scene">変更シーン</param>
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
