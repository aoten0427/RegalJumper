// ================================================================ 
// �t�@�C���� : SelectBestTime.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�Z���N�g�ł̃x�X�g�^�C��
// ================================================================
#include"pch.h"
#include"SelectBestTime.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"
#include"Base/Event/Observer.h"
#include"Game/Play/UI/Time.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>

constexpr float MAX_TIME = 99999;
constexpr int MARK_CLIPPING = 1200;
constexpr int SCORE_CLIPPING = 500;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
SelectBestTime::SelectBestTime(Canvas* canvas):UserInterface(canvas,"BestTime",2)
	,
	m_bestTime{nullptr},
	m_orderTimes{},
	m_scoreMarks{}
{
	using namespace DirectX::SimpleMath;


	SetPosition(Vector2(820, 220));
	SetSize(Vector2(300, 60));
	//�x�X�g�^�C���쐬
	m_bestTime = GetScene()->AddObject<Time>(canvas);
	m_bestTime->SetPositionY(310);
	m_bestTime->SetSize(Vector2(52, 91));
	m_bestTime->SetStartX(800);

	//�x�X�g�^�C���X�R�A�}�[�N�쐬
	m_scoreMarks[0] = GetScene()->AddObject<UserInterface>(canvas,"Score",2);
	m_scoreMarks[0]->SetPosition(Vector2(980, 220));
	m_scoreMarks[0]->SetSize(Vector2(40, 40));
	m_scoreMarks[1] = GetScene()->AddObject<UserInterface>(canvas,"ScoreMark",2);
	m_scoreMarks[1]->SetPosition(Vector2(980, 220));
	m_scoreMarks[1]->SetSize(Vector2(96, 96));


	//�I�[�_�[�^�C���쐬
	for (int i = 0; i < 3; i++)
	{
		m_orderTimes[i] = GetScene()->AddObject<Time>(canvas);
		m_orderTimes[i]->SetStartX(900.0f);
		m_orderTimes[i]->SetPositionY((float)(390 + i * 50));
		m_orderTimes[i]->SetSize(Vector2(30, 45));
	}
	//�I�[�_�[�^�C���X�R�A�쐬
	for (int i = 0; i < 3; i++)
	{
		auto score = GetScene()->AddObject<UserInterface>(canvas,"Score",2);
		score->SetClipRange(Vector4(i / 4.0f, 0, 1 / 4.0f, 1.0f));
		score->SetPosition(Vector2(850, (float)(390 + 50 * i)));
		score->SetSize(Vector2(40, 40));
	}

	//�I�u�U�[�o�[�ݒ�
	m_observer = AddComponent<Observer<>>(this);
	m_observer->SetFunction([&]() {DataUpdate(); });
	m_observer->RegistrationSubject("LeftArrow");
	m_observer->RegistrationSubject("RightArrow");

	//�f�[�^�ǂݍ���
	LoadData();
}

/// <summary>
/// �f�[�^�X�V
/// </summary>
void SelectBestTime::DataUpdate()
{
	LoadData();
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void SelectBestTime::LoadData()
{
	using namespace DirectX::SimpleMath;
	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/ClearData/" + GameManager::GetInstance()->GetStageName() + ".json";

	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		float besttime = m_json["BestTime"];
		if (besttime == MAX_TIME)
		{
			//�x�X�g�^�C����none��Ԃ�
			m_bestTime->SetNone(true);
			m_scoreMarks[0]->SetActive(false);
			m_scoreMarks[1]->SetActive(false);
		}
		else
		{
			m_bestTime->SetNone(false);
			m_bestTime->SetCount(besttime);
			m_scoreMarks[0]->SetActive(true);
			m_scoreMarks[1]->SetActive(true);

			const float ClipingX = 0.25f;

			//�x�X�g�^�C���̃X�R�A��ݒ�
			if (besttime <= m_json["OrderTime"]["S"])
			{
				m_scoreMarks[1]->SetClipRange(Vector4(0, 0, ClipingX, 1.0));
				m_scoreMarks[0]->SetClipRange(Vector4(0, 0, ClipingX, 1.0));
			}
			else if (besttime <= m_json["OrderTime"]["A"])
			{
				m_scoreMarks[1]->SetClipRange(Vector4(ClipingX, 0, ClipingX, 1.0));
				m_scoreMarks[0]->SetClipRange(Vector4(ClipingX, 0, ClipingX, 1.0));
			}
			else if (besttime <= m_json["OrderTime"]["B"])
			{
				m_scoreMarks[1]->SetClipRange(Vector4(ClipingX * 2, 0, ClipingX, 1.0));
				m_scoreMarks[0]->SetClipRange(Vector4(ClipingX * 2, 0, ClipingX, 1.0));
			}
			else
			{
				m_scoreMarks[1]->SetClipRange(Vector4(ClipingX * 3, 0, ClipingX, 1.0));
				m_scoreMarks[0]->SetClipRange(Vector4(ClipingX * 3, 0, ClipingX, 1.0));
			}
		}

		//�e�X�R�A�̃^�C����ݒ�
		m_orderTimes[0]->SetCount(m_json["OrderTime"]["S"]);
		m_orderTimes[1]->SetCount(m_json["OrderTime"]["A"]);
		m_orderTimes[2]->SetCount(m_json["OrderTime"]["B"]);
	}
}
