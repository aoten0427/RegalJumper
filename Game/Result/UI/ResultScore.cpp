// ================================================================ 
// �t�@�C���� : ResultScore.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�̃X�R�A�\��
// ================================================================
#include"pch.h"
#include"ResultScore.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/GameManager.h"

constexpr int MARK_CLIPPING = 1200;//�X�R�A�}�[�N��1���͈̔�
constexpr int SCORE_CLIPPING = 500;//�X�R�A�̂P���͈̔�

constexpr float DELAY_TIME = 2.3f;//�X�R�A�\���̂��߂̒x������

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
ResultScore::ResultScore(Canvas* canvas):UserInterface(canvas)
	,
	m_mark{nullptr},
	m_markSize{ 0,0 },
	m_markTween{nullptr},
	m_score{nullptr},
	m_scoreSize{ 1600,1600 },
	m_scoreTween{nullptr},
	m_timer{ 0 }
{
	using namespace DirectX::SimpleMath;
	//�X�R�A�g����
	m_mark = GetScene()->AddObject<UserInterface>(canvas,"ScoreMark",3);
	m_mark->SetPosition(Vector2(830, 380));
	m_mark->SetSize(m_markSize);
	m_markTween = AddComponent<Tween>(this,true);
	m_markTween->DoVector2(m_markSize,Vector2(600,600), 0.2f).SetEase(Easing::Ease::OutQuad).SetDelay(1.8f);
	//�X�R�A����
	m_score = GetScene()->AddObject<UserInterface>(canvas,"Score",3);
	m_score->SetPosition(Vector2(830, 380));
	m_score->SetSize(m_scoreSize);
	m_score->SetActive(false);
	m_scoreTween = AddComponent<Tween>(this,true);
	m_scoreTween->DoVector2(m_scoreSize, Vector2(260, 260), 0.8f).SetEase(Easing::Ease::OutBounce).SetDelay(DELAY_TIME).SetCompleteFunction([&]() {
		GetScene()->ChangeState(Scene::State::END);
		});

	//�f�[�^�ǂݍ���
	LoadJSON();
	//�f�[�^��������
	WriteJSON();

	//�I�u�U�[�o���� �X�L�b�v�����o�^
	Observer<>* skip = AddComponent<Observer<>>(this);
	skip->RegistrationSubject("ResultSkip");
	skip->SetFunction([&]() {Skip(); });
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void ResultScore::ObjectUpdate(float deltatime)
{
	m_timer += deltatime;
	m_mark->SetSize(m_markSize);
	if (m_timer > DELAY_TIME)
	{
		m_score->SetActive(true);
		m_score->SetSize(m_scoreSize);
	}
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void ResultScore::LoadJSON()
{
	using namespace DirectX::SimpleMath;

	//�X�e�[�W��
	std::string stageName = GameManager::GetInstance()->GetStageName();
	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/ClearData/" + stageName + ".json";

	const float ClipingX = 0.25f;
	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		float clearTime = GameManager::GetInstance()->GetResultTime();

		if (clearTime <= m_json["OrderTime"]["S"])
		{
			m_mark->SetClipRange(Vector4(0, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(0, 0, ClipingX, 1));
		}
		else if (clearTime <= m_json["OrderTime"]["A"])
		{
			m_mark->SetClipRange(Vector4(ClipingX, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(ClipingX, 0, ClipingX, 1));
		}
		else if (clearTime <= m_json["OrderTime"]["B"])
		{
			m_mark->SetClipRange(Vector4(ClipingX * 2, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(ClipingX * 2, 0, ClipingX, 1));
		}
		else
		{
			m_mark->SetClipRange(Vector4(ClipingX * 3, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(ClipingX * 3, 0, ClipingX, 1));
		}

		ifs.close();
	}

}

/// <summary>
/// �f�[�^��������
/// </summary>
void ResultScore::WriteJSON()
{
	//�X�e�[�W��
	std::string stageName = GameManager::GetInstance()->GetStageName();
	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/ClearData/" + stageName + ".json";

	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		float clearTime = GameManager::GetInstance()->GetResultTime();
		//����̃N���A�^�C���ƃx�X�g�^�C�����r
		if (m_json["BestTime"] >= clearTime)
		{
			//����̂ق����Z����Ώ㏑��
			m_json["BestTime"] = clearTime;
			std::ofstream file(filename.c_str());
			if (file.good())
			{
				file << m_json;
				file.close();
			}
		}
	}
}

/// <summary>
/// �X�L�b�v
/// </summary>
void ResultScore::Skip()
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	m_markTween->Kill();
	m_scoreTween->Kill();
	m_timer = DELAY_TIME;
}
