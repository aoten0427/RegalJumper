// ================================================================ 
// �t�@�C���� : Option.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �I�v�V����
// ================================================================
#include"pch.h"
#include"Option.h"
#include"Base/Screen.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/Object/UnbreakableManager.h"
#include"Base/Event/Subject.h"
#include"Base/Tween/DoTween.h"
#include"Base/Sound/SoundManager.h"
#include"Game/GameManager.h"
#include"Game/Option/OptionContents.h"
#include"Game/Option/OptionExitButton.h"


constexpr float BGM_POSITION = 180.0f;//BGM�\���ʒu
constexpr float SE_POSITION = 350.0f;//SE�\���ʒu
constexpr float SENSITIVITY_POSITION = 520.0f;//���x�\���ʒu

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
Option::Option(Canvas* canvas):UserInterface(canvas,"Option",5)
	,
	m_oldSceneState{Scene::State::RESERVE},
	m_size{ Screen::WIDTH / 2,0 },
	m_openSubject{nullptr},
	m_closeSubject{nullptr}
{
	using namespace DirectX::SimpleMath;
	//�Q�[���}�l�W���[�ɓo�^
	GameManager::GetInstance()->SetOption(this);

	LoadData();

	//���ݒ�
	SetPosition(Vector2(Screen::CENTER_X, Screen::CENTER_Y));
	SetSize(m_size);
	//tween�쐬
	m_tween = AddComponent<Tween>(this,true);
	//Subject�쐬
	m_openSubject = AddComponent<Subject<>>(this, "OptionOpen");
	m_closeSubject = AddComponent<Subject<>>(this, "OptionClose");

	//�ύX���e�쐬
	//BGM
	m_contents[0] = UnbreakableManager::GetInstance()->AddObject<OptionContents>("BGM", canvas, "BGM",m_initialParcent[0]);
	m_contents[0]->SetPosition(Vector2(Screen::CENTER_X, BGM_POSITION));
	m_contents[0]->Close();
	m_contents[0]->SetFunction([&]() {
		SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::BGM, m_contents[0]->GetPearcent());
		});
	//SE
	m_contents[1] = UnbreakableManager::GetInstance()->AddObject<OptionContents>("SE", canvas, "SE",m_initialParcent[1]);
	m_contents[1]->SetPosition(Vector2(Screen::CENTER_X, SE_POSITION));
	m_contents[1]->Close();
	m_contents[1]->SetFunction([&]() {
		SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::SE, m_contents[1]->GetPearcent());
		});
	//���x
	m_contents[2] = UnbreakableManager::GetInstance()->AddObject<OptionContents>("Sensitivity", canvas, "Sensitivity", m_initialParcent[2]);
	m_contents[2]->SetPosition(Vector2(Screen::CENTER_X, SENSITIVITY_POSITION));
	m_contents[2]->Close();
	m_contents[2]->SetFunction([&]() {
		m_sensitivity = m_contents[2]->GetPearcent();
		});
	//�ޏo�{�^��
	m_exitButton = UnbreakableManager::GetInstance()->AddObject<OptionExit>("OptionExit", canvas, this);
	m_exitButton->SetFunction([&]() {Close(); });

	//�������ʐݒ�
	SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::BGM, m_initialParcent[0]);
	SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::SE, m_initialParcent[1]);
	m_sensitivity = m_initialParcent[2];
}



/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Option::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetSize(m_size);
}

/// <summary>
/// �I�������@�I�v�V�����f�[�^�̕ۑ�
/// </summary>
void Option::Finalize()
{
	WriteData();
}

/// <summary>
/// �J��
/// </summary>
void Option::Open()
{
	using namespace DirectX::SimpleMath;
	//�O�̏�Ԃ��擾
	m_oldSceneState = GetScene()->GetState();
	//�V�[���̏�ԕύX
	GetScene()->ChangeState(Scene::State::STOP);
	//�J��
	m_tween->DoVector2(m_size, Vector2(Screen::WIDTH / 2, Screen::HEIGHT), 0.2f).SetCompleteFunction([&]() {
		//�v�f���݂���悤�ɂ���
		for (int i = 0; i < SELECT_NUM; i++)
		{
			m_contents[i]->Open();
		}
		m_exitButton->SetActive(true);
		});
	//�J�����ʒm���o��
	m_openSubject->Notify();
}

/// <summary>
/// ����
/// </summary>
void Option::Close()
{
	using namespace DirectX::SimpleMath;
	//�J�n�O�̏�Ԃɕω�
	GetScene()->ChangeState(m_oldSceneState);
	//����
	m_tween->DoVector2(m_size, Vector2(Screen::WIDTH / 2, 0), 0.2f);
	//�v�f�������Ȃ�����
	for (int i = 0; i < SELECT_NUM; i++)
	{
		m_contents[i]->Close();
	}
	m_exitButton->SetActive(false);
	//�����ʒm���o��
	m_closeSubject->Notify();
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void Option::LoadData()
{
	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/Option/Option.json";

	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//�e�v�f�̃p�[�Z���g�����l���擾
		m_initialParcent[0] = m_json["BGM"];
		m_initialParcent[1] = m_json["SE"];
		m_initialParcent[2] = m_json["Sensitivity"];


		ifs.close();
	}
}

/// <summary>
/// �f�[�^��������
/// </summary>
void Option::WriteData()
{
	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/Option/Option.json";

	//�ǂݍ���
	std::ofstream close(filename.c_str());
	if (close.good())
	{
		nlohmann::json m_json;

		//�e�v�f�̃p�[�Z���g��ۑ�
		m_json["BGM"] = m_contents[0]->GetPearcent();
		m_json["SE"] = m_contents[1]->GetPearcent();
		m_json["Sensitivity"] = m_contents[2]->GetPearcent();

		close << m_json;

		close.close();
	}
}
