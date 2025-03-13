// ================================================================ 
// ファイル名 : SoundManager.h
// 作成者 : 景山碧天
// 説明 :  サウンドを取りまとめる
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"
#include"Base/Sound/Sound.h"


namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

class SoundManager:public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;
private:
	//システム
	FMOD::System* m_system;
	//管理サウンド
	std::unordered_set<Sound*> m_sounds;
	//サウンド名とファイルを管理する
	std::unordered_map<std::string, std::string> m_soudnNamtToFile;
	//再生タイプごとのボリューム
	std::unordered_map<Sound::SoundType, float>  m_typeVolume;
public:
	//コンストラクタ
	SoundManager();
	//デストラクタ
	~SoundManager();
	//アップデート
	void Update();
	//サウンドを作成
	void MakeSound(Sound* sound,std::string name,FMOD::Sound** fmodsound);
	//サウンドを再生
	void PlaySound(FMOD::Channel** channel, FMOD::Sound** sound);
	//サウンドを削除
	void RemoveSound(Sound* sound);
	//再生タイプに応じて音量を調整
	void ChangeVolume(Sound::SoundType type,float volume);
	//再生タイプごとのボリューム取得
	float GetTypeVolume(Sound::SoundType type);
private:
	//データ読み込み
	void LoadData(int pathNum = 1);
};