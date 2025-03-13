// ================================================================ 
// �t�@�C���� : SoundManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �T�E���h�����܂Ƃ߂�
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
/// �R���X�g���N�^
/// </summary>
SoundManager::SoundManager()
{
	//�V�X�e���쐬
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	result = m_system->init(32, FMOD_INIT_NORMAL, nullptr);
	//�����f�[�^�ǂݍ���
	LoadData();

	m_typeVolume.insert({ Sound::SoundType::BGM,1.0f });
	m_typeVolume.insert({ Sound::SoundType::SE,1.0f });
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundManager::~SoundManager()
{
	m_system->release();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
void SoundManager::Update()
{
	m_system->update();
}

/// <summary>
/// �T�E���h���쐬
/// </summary>
/// <param name="sound">�T�E���h�N���X</param>
/// <param name="name">�T�E���h��</param>
/// <param name="fmodsound">�����|�C���^</param>
void SoundManager::MakeSound(Sound* sound, std::string name, FMOD::Sound** fmodsound)
{
	//�T�E���h�̌���
	auto soundfile = m_soudnNamtToFile.find(name);
	if (soundfile == m_soudnNamtToFile.end())return;
	//�t�@�C�����ݒ�
	std::string filename = "Resources/Sounds/" + (*soundfile).second;
	//BGM����
	if (sound->GetType() == Sound::SoundType::BGM)
	{
		m_system->createSound(filename.c_str(), FMOD_LOOP_NORMAL, nullptr, fmodsound);
	}
	//SE����
	else
	{
		m_system->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, fmodsound);
	}
	//�T�E���h��ۑ�
	m_sounds.insert(sound);
}

/// <summary>
/// �T�E���h���Đ�
/// </summary>
/// <param name="channel">�`�����l��</param>
/// <param name="sound">�T�E���h</param>
void SoundManager::PlaySound(FMOD::Channel** channel, FMOD::Sound** sound)
{
	//�Đ����Ă��邩�m�F
	bool isplay = true;
	(*channel)->getPaused(&isplay);
	//�Đ�
	if (isplay)
	{
		//�Đ��ꏊ���͂��߂Ɉړ�
		(*channel)->setPosition(0, FMOD_TIMEUNIT_MS);
		//�Đ�
		m_system->playSound((*sound), nullptr, false, channel);
	}
}

/// <summary>
/// �Ǘ��T�E���h����폜
/// </summary>
/// <param name="sound">�폜�T�E���h</param>
void SoundManager::RemoveSound(Sound* sound)
{
	m_sounds.erase(sound);
}

/// <summary>
/// �Đ��^�C�v�ɉ����ĉ��ʂ𒲐�
/// </summary>
/// <param name="type">�T�E���h�^�C�v</param>
/// <param name="volume">�{�����[��</param>
void SoundManager::ChangeVolume(Sound::SoundType type,float volume)
{
	m_typeVolume[type] = volume;
	for (auto& sound : m_sounds)
	{
		//�^�C�v����
		if (sound->GetType() != type)return;
		//���ʕύX
		sound->ChangeVolume();
	}
}

/// <summary>
/// �Đ��^�C�v���Ƃ̃{�����[���擾
/// </summary>
/// <param name="type">�Đ��^�C�v</param>
/// <returns>�^�C�v�̃{�����[��</returns>
float SoundManager::GetTypeVolume(Sound::SoundType type)
{
	return m_typeVolume[type];
}


/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
/// <param name="pathNum">�p�X�ԍ�</param>
void SoundManager::LoadData(int pathNum)
{
	//JSON�t�@�C���I��
	std::string file = "Resources/JSON/GameResources/Path" + std::to_string(pathNum) + ".json";

	//�ǂݍ���
	std::ifstream ifs(file.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//�T�E���h�f�[�^�̓ǂݍ���
		for (auto itr = m_json["Sound"]["BGM"].begin(); itr != m_json["Sound"]["BGM"].end(); itr++)
		{
			std::string name = itr.key();
			std::string fileName = itr.value();
			m_soudnNamtToFile.insert({ name,fileName });
		}
		//�T�E���h�f�[�^�̓ǂݍ���
		for (auto itr = m_json["Sound"]["SE"].begin(); itr != m_json["Sound"]["SE"].end(); itr++)
		{
			std::string name = itr.key();
			std::string fileName = itr.value();
			m_soudnNamtToFile.insert({ name,fileName });
		}
	}
}
