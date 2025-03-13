// ================================================================ 
// �t�@�C���� : Sound.h
// �쐬�� : �i�R�ɓV
// ���� :  �T�E���h����舵��
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
	//�Đ��^�C�v
	enum class SoundType
	{
		BGM,
		SE
	};
public:
	SoundType GetType() { return m_type; }
private:
	//�}�l�[�W���[
	SoundManager* m_manager;
	//���g�̃^�C�v
	SoundType m_type;
	//�`�����l��
	FMOD::Channel* m_channel;
	//����
	FMOD::Sound* m_sound;
	//����
	float m_volum;
public:
	//�R���X�g���N�^
	Sound(Object* object,SoundType type,std::string soundName = Config::NONE_FILE,bool isplay = false);
	//�f�X�g���N�^
	~Sound()override;
	//�Đ�����
	void Play();
	//�~�߂�
	void Pause();
	//���ʒ���
	void SetVolume(float volume);
	void ChangeVolume();
private:
	//���y���[�h
	void LoadSound(std::string soundName);
};