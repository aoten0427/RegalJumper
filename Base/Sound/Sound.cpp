// ================================================================ 
// ファイル名 : Sound.cpp
// 作成者 : 景山碧天
// 説明 :  サウンドを取り扱う
// ================================================================
#include"pch.h"
#include"Sound.h"
#include"Base/Sound/SoundManager.h"
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Libraries/FMOD/inc/fmod_errors.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="type">再生タイプ</param>
/// <param name="soundName">サウンド名</param>
/// <param name="isplay">作成後そのまま再生するか</param>
Sound::Sound(Object* object,SoundType type,std::string soundName,bool isplay):Component(object)
	,
	m_type{type},
	m_channel{nullptr},
	m_sound{nullptr},
	m_volum{1}
{
	//マネージャー取得
	m_manager = SoundManager::GetInstance();
	//音楽のロード
	if (soundName != Config::NONE_FILE)LoadSound(soundName);
	//ポーズ状態にする
	m_channel->setPaused(true);
	//再生する必要がある場合再生
	if (isplay)
	{
		Play();
	}
}

/// <summary>
/// デストラクタ
/// </summary>
Sound::~Sound()
{
	m_sound->release();
	m_manager->RemoveSound(this);
}

/// <summary>
/// 再生
/// </summary>
void Sound::Play()
{
	if (m_sound == nullptr)return;
	m_manager->PlaySound(&m_channel, &m_sound);
	//音量設定
	ChangeVolume();
}

/// <summary>
/// 止める
/// </summary>
void Sound::Pause()
{
	m_channel->setPaused(true);
}

/// <summary>
/// このクラス個別の音量変更
/// </summary>
/// <param name="volume">変更音量(0 ~ 1)</param>
void Sound::SetVolume(float volume)
{
	m_volum = volume;
	ChangeVolume();
}

/// <summary>
/// 音量変更
/// </summary>
void Sound::ChangeVolume()
{
	m_channel->setVolume(m_volum * m_manager->GetTypeVolume(m_type));
}

/// <summary>
/// 音楽ロード
/// </summary>
/// <param name="soundName">サウンド名</param>
void Sound::LoadSound(std::string soundName)
{
	m_manager->MakeSound(this, soundName,&m_sound);
}
