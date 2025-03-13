// ================================================================ 
// �t�@�C���� : ResultOrderTime.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �ڕW���Ԃ̕\��
// ================================================================
#include"pch.h"
#include"ResultOrderTime.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/GameManager.h"
#include"Game/Play/UI/Time.h"

constexpr int SCORE_START_Y = 570;//�X�R�A�\���ʒu
constexpr int RANGE_Y = 50;//�X�R�A�\����

constexpr int SCORE_SIZE = 36;//�X�R�A�T�C�Y

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
ResultOrderTIme::ResultOrderTIme(Canvas* canvas):UserInterface(canvas)
	,
	m_score{},
	m_orderTimes{},
	m_tween{nullptr},
	m_alpha{0}
{
	using namespace DirectX::SimpleMath;
	//�{�̂̓I�t��
	SetActive(false);
	//�X�R�A�摜�̕�������
	const float ClipingX = 0.25f;
	//�e�X�R�A����
	for (int i = 0; i < 3; i++)
	{
		m_score[i] = GetScene()->AddObject<UserInterface>(canvas,"Score",3);
		m_score[i]->SetClipRange(Vector4(i * ClipingX, 0, ClipingX, 1));
		m_score[i]->SetPosition(Vector2(1070, (float)(SCORE_START_Y + RANGE_Y * i)));
		m_score[i]->SetSize(Vector2(SCORE_SIZE, SCORE_SIZE));
		m_score[i]->SetColor(Vector4(1, 1, 1, m_alpha));
	}
	//�e�X�R�A�^�C������
	for (int i = 0; i < 3; i++)
	{
		m_orderTimes[i] = GetScene()->AddObject<Time>(canvas);
		m_orderTimes[i]->SetStartX(1100.0f);
		m_orderTimes[i]->SetPositionY((float)(SCORE_START_Y + i * RANGE_Y));
		m_orderTimes[i]->SetSize(Vector2(24, 36));
		m_orderTimes[i]->SetTimeColor(Vector4(1, 1, 1, m_alpha));
	}
	//�N���A�f�[�^�ǂݍ���
	LoadData();
	//Tween����
	m_tween = AddComponent<Tween>(this,true);
	m_tween->DoFloat(m_alpha, 1, 0.3f).SetDelay(2.0f);

	//�I�u�U�[�o���� �X�L�b�v�����o�^
	Observer<>* skip = AddComponent<Observer<>>(this);
	skip->RegistrationSubject("ResultSkip");
	skip->SetFunction([&]() {Skip(); });

	m_mouse = GetScene()->AddObject<UserInterface>(canvas, "Mouse_left", 3);
	m_mouse->SetPosition(Vector2(830, 680));
	m_mouse->SetSize(Vector2(200, 50));
}

/// <summary>
/// �A�b�v�f�[�g�@�A���t�@�l�ω�
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void ResultOrderTIme::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	using namespace DirectX::SimpleMath;
	for (int i = 0; i < 3; i++)
	{
		m_score[i]->SetColor(Vector4(1, 1, 1, m_alpha));
		m_orderTimes[i]->SetTimeColor(Vector4(1, 1, 1, m_alpha));
	}
	m_mouse->SetColor(Vector4(1, 1, 1, m_alpha));
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void ResultOrderTIme::LoadData()
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

		//�e�X�R�A�̃^�C����ǂݍ���
		m_orderTimes[0]->SetCount(m_json["OrderTime"]["S"]);
		m_orderTimes[1]->SetCount(m_json["OrderTime"]["A"]);
		m_orderTimes[2]->SetCount(m_json["OrderTime"]["B"]);

		ifs.close();
	}
}

/// <summary>
/// �X�L�b�v
/// </summary>
void ResultOrderTIme::Skip()
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	m_tween->Kill();
}
