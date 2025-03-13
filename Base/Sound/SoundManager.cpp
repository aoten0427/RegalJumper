// ================================================================ 
// ファイル名 : SoundManager.h
// 作成者 : 景山碧天
// 説明 :  サウンドを取りまとめる
// ================================================================
#include"pch.h"
#include"SoundManager.h"
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Libraries/FMOD/inc/fmod_errors.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/Sound/Sound.h"

/// <summary>
/// コンストラクタ
/// </summary>
SoundManager::SoundManager()
{
	//システム作成
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	result = m_system->init(32, FMOD_INIT_NORMAL, nullptr);
	//初期データ読み込み
	LoadData();

	m_typeVolume.insert({ Sound::SoundType::BGM,1.0f });
	m_typeVolume.insert({ Sound::SoundType::SE,1.0f });
}

/// <summary>
/// デストラクタ
/// </summary>
SoundManager::~SoundManager()
{
	m_system->release();
}

/// <summary>
/// アップデート
/// </summary>
void SoundManager::Update()
{
	m_system->update();
}

/// <summary>
/// サウンドを作成
/// </summary>
/// <param name="sound">サウンドクラス</param>
/// <param name="name">サウンド名</param>
/// <param name="fmodsound">入れるポインタ</param>
void SoundManager::MakeSound(Sound* sound, std::string name, FMOD::Sound** fmodsound)
{
	//サウンドの検索
	auto soundfile = m_soudnNamtToFile.find(name);
	if (soundfile == m_soudnNamtToFile.end())return;
	//ファイル名設定
	std::string filename = "Resources/Sounds/" + (*soundfile).second;
	//BGM生成
	if (sound->GetType() == Sound::SoundType::BGM)
	{
		m_system->createSound(filename.c_str(), FMOD_LOOP_NORMAL, nullptr, fmodsound);
	}
	//SE生成
	else
	{
		m_system->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, fmodsound);
	}
	//サウンドを保存
	m_sounds.insert(sound);
}

/// <summary>
/// サウンドを再生
/// </summary>
/// <param name="channel">チャンネル</param>
/// <param name="sound">サウンド</param>
void SoundManager::PlaySound(FMOD::Channel** channel, FMOD::Sound** sound)
{
	//再生しているか確認
	bool isplay = true;
	(*channel)->getPaused(&isplay);
	//再生
	if (isplay)
	{
		//再生場所をはじめに移動
		(*channel)->setPosition(0, FMOD_TIMEUNIT_MS);
		//再生
		m_system->playSound((*sound), nullptr, false, channel);
	}
}

/// <summary>
/// 管理サウンドから削除
/// </summary>
/// <param name="sound">削除サウンド</param>
void SoundManager::RemoveSound(Sound* sound)
{
	m_sounds.erase(sound);
}

/// <summary>
/// 再生タイプに応じて音量を調整
/// </summary>
/// <param name="type">サウンドタイプ</param>
/// <param name="volume">ボリューム</param>
void SoundManager::ChangeVolume(Sound::SoundType type,float volume)
{
	m_typeVolume[type] = volume;
	for (auto& sound : m_sounds)
	{
		//タイプ検索
		if (sound->GetType() != type)return;
		//音量変更
		sound->ChangeVolume();
	}
}

/// <summary>
/// 再生タイプごとのボリューム取得
/// </summary>
/// <param name="type">再生タイプ</param>
/// <returns>タイプのボリューム</returns>
float SoundManager::GetTypeVolume(Sound::SoundType type)
{
	return m_typeVolume[type];
}


/// <summary>
/// データ読み込み
/// </summary>
/// <param name="pathNum">パス番号</param>
void SoundManager::LoadData(int pathNum)
{
	//JSONファイル選択
	std::string file = "Resources/JSON/GameResources/Path" + std::to_string(pathNum) + ".json";

	//読み込み
	std::ifstream ifs(file.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//サウンドデータの読み込み
		for (auto itr = m_json["Sound"]["BGM"].begin(); itr != m_json["Sound"]["BGM"].end(); itr++)
		{
			std::string name = itr.key();
			std::string fileName = itr.value();
			m_soudnNamtToFile.insert({ name,fileName });
		}
		//サウンドデータの読み込み
		for (auto itr = m_json["Sound"]["SE"].begin(); itr != m_json["Sound"]["SE"].end(); itr++)
		{
			std::string name = itr.key();
			std::string fileName = itr.value();
			m_soudnNamtToFile.insert({ name,fileName });
		}
	}
}
