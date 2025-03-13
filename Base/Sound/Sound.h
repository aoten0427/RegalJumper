// ================================================================ 
// ファイル名 : Sound.h
// 作成者 : 景山碧天
// 説明 :  サウンドを取り扱う
// ================================================================

#pragma once
#include"Base/Component/Component.h"
#include"Base/Config.h"

namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

class SoundManager;

class Sound :public Component
{
public:
	//再生タイプ
	enum class SoundType
	{
		BGM,
		SE
	};
public:
	SoundType GetType() { return m_type; }
private:
	//マネージャー
	SoundManager* m_manager;
	//自身のタイプ
	SoundType m_type;
	//チャンネル
	FMOD::Channel* m_channel;
	//音声
	FMOD::Sound* m_sound;
	//音量
	float m_volum;
public:
	//コンストラクタ
	Sound(Object* object,SoundType type,std::string soundName = Config::NONE_FILE,bool isplay = false);
	//デストラクタ
	~Sound()override;
	//再生する
	void Play();
	//止める
	void Pause();
	//音量調整
	void SetVolume(float volume);
	void ChangeVolume();
private:
	//音楽ロード
	void LoadSound(std::string soundName);
};