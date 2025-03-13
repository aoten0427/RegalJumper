// ================================================================ 
// �t�@�C���� : SoundManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �T�E���h�����܂Ƃ߂�
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
	//�V�X�e��
	FMOD::System* m_system;
	//�Ǘ��T�E���h
	std::unordered_set<Sound*> m_sounds;
	//�T�E���h���ƃt�@�C�����Ǘ�����
	std::unordered_map<std::string, std::string> m_soudnNamtToFile;
	//�Đ��^�C�v���Ƃ̃{�����[��
	std::unordered_map<Sound::SoundType, float>  m_typeVolume;
public:
	//�R���X�g���N�^
	SoundManager();
	//�f�X�g���N�^
	~SoundManager();
	//�A�b�v�f�[�g
	void Update();
	//�T�E���h���쐬
	void MakeSound(Sound* sound,std::string name,FMOD::Sound** fmodsound);
	//�T�E���h���Đ�
	void PlaySound(FMOD::Channel** channel, FMOD::Sound** sound);
	//�T�E���h���폜
	void RemoveSound(Sound* sound);
	//�Đ��^�C�v�ɉ����ĉ��ʂ𒲐�
	void ChangeVolume(Sound::SoundType type,float volume);
	//�Đ��^�C�v���Ƃ̃{�����[���擾
	float GetTypeVolume(Sound::SoundType type);
private:
	//�f�[�^�ǂݍ���
	void LoadData(int pathNum = 1);
};