// ================================================================ 
// �t�@�C���� : Sound.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �T�E���h����舵��
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
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
/// <param name="type">�Đ��^�C�v</param>
/// <param name="soundName">�T�E���h��</param>
/// <param name="isplay">�쐬�セ�̂܂܍Đ����邩</param>
Sound::Sound(Object* object,SoundType type,std::string soundName,bool isplay):Component(object)
	,
	m_type{type},
	m_channel{nullptr},
	m_sound{nullptr},
	m_volum{1}
{
	//�}�l�[�W���[�擾
	m_manager = SoundManager::GetInstance();
	//���y�̃��[�h
	if (soundName != Config::NONE_FILE)LoadSound(soundName);
	//�|�[�Y��Ԃɂ���
	m_channel->setPaused(true);
	//�Đ�����K�v������ꍇ�Đ�
	if (isplay)
	{
		Play();
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sound::~Sound()
{
	m_sound->release();
	m_manager->RemoveSound(this);
}

/// <summary>
/// �Đ�
/// </summary>
void Sound::Play()
{
	if (m_sound == nullptr)return;
	m_manager->PlaySound(&m_channel, &m_sound);
	//���ʐݒ�
	ChangeVolume();
}

/// <summary>
/// �~�߂�
/// </summary>
void Sound::Pause()
{
	m_channel->setPaused(true);
}

/// <summary>
/// ���̃N���X�ʂ̉��ʕύX
/// </summary>
/// <param name="volume">�ύX����(0 ~ 1)</param>
void Sound::SetVolume(float volume)
{
	m_volum = volume;
	ChangeVolume();
}

/// <summary>
/// ���ʕύX
/// </summary>
void Sound::ChangeVolume()
{
	m_channel->setVolume(m_volum * m_manager->GetTypeVolume(m_type));
}

/// <summary>
/// ���y���[�h
/// </summary>
/// <param name="soundName">�T�E���h��</param>
void Sound::LoadSound(std::string soundName)
{
	m_manager->MakeSound(this, soundName,&m_sound);
}
