// ================================================================ 
// �t�@�C���� : ResultTime.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�ł̃^�C���\��
// ================================================================
#include"pch.h"
#include"ResultTime.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"Game/Play/UI/Time.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
ResultTime::ResultTime(Canvas* canvas):UserInterface(canvas)
	,
	m_time{nullptr},
	m_timesize{ 80,0 },
	m_timeTween{nullptr},
	m_bar{nullptr},
	m_barsize{ 0,10 },
	m_barTween{nullptr}
{
	SetActive(false);
	using namespace DirectX::SimpleMath;
	//�^�C������
	m_time = GetScene()->AddObject<Time>(canvas);
	m_time->SetRenderOrder(3);
	m_time->SetStartX(100);
	m_time->SetPositionY(550);
	m_time->SetSize(m_timesize);
	m_time->SetTimeColor(Vector4(0.5f, 0.90f, 0.85f, 1));
	m_time->SetCount(GameManager::GetInstance()->GetResultTime());
	m_timeTween = AddComponent<Tween>(this,true);
	m_timeTween->DoVector2(m_timesize, Vector2(80, 120), 0.1f).SetDelay(0.9f);
	//�o�[����
	m_bar = GetScene()->AddObject<UserInterface>(canvas, "Quad", 3);
	m_bar->SetPosition(Vector2(320, 620));
	m_bar->SetSize(m_barsize);
	m_bar->SetColor(Vector4(0.4f, 0.90f, 0.85f, 1));
	m_barTween = AddComponent<Tween>(this,true);
	m_barTween->DoVector2(m_barsize, Vector2(500, 10), 0.5f).SetDelay(0.4f);

	//�I�u�U�[�o���� �X�L�b�v�����o�^
	Observer<>* skip = AddComponent<Observer<>>(this);
	skip->RegistrationSubject("ResultSkip");
	skip->SetFunction([&]() {Skip(); });
}

/// <summary>
/// �A�b�v�f�[�g�@�T�C�Y�ω�
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void ResultTime::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	m_time->SetSize(m_timesize);
	m_bar->SetSize(m_barsize);
}

/// <summary>
/// Tween�����X�L�b�v
/// </summary>
void ResultTime::Skip()
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	m_timeTween->Kill();
	m_barTween->Kill();
}
