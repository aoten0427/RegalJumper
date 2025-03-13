// ================================================================ 
// �t�@�C���� : SelectArrow.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�I����
// ================================================================
#include"pch.h"
#include"SelectArrow.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"
#include"Base/Event/Subject.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"
#include"Base/Sound/Sound.h"

constexpr float POSITION_Y = 130;
constexpr float NOMAL_X = 1110;
constexpr float INVERSION_X = 810;
constexpr float MOVEING = 10;
constexpr float MOVE_SPEED = 1.2f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="inversion">���]�t���O</param>
SelectArrow::SelectArrow(Canvas* canvas,bool inversion):Button(canvas,"Arrow",2)
	,
	m_inversion{inversion},
	m_position{},
	m_selectSubject{nullptr},
	m_observer{nullptr}
{
	using namespace DirectX::SimpleMath;
	//�T�C�Y�ݒ�
	SetSize(Vector2(45, 45));

	Tween* tween = AddComponent<Tween>(this,true);
	//�����ɂ�鏉���ݒ�
	if (inversion)
	{
		//�������]
		SetSize(GetSize() * -1);
		m_position = Vector2(INVERSION_X, POSITION_Y);
		//�ړ�Tween�쐬
		tween->DoVector2(m_position, Vector2(INVERSION_X - MOVEING, POSITION_Y), MOVE_SPEED).
			SetLoop(-1).SetEase(Easing::Ease::InOutQuad);
		//�ʒm�쐬
		m_selectSubject = AddComponent<Subject<>>(this, "LeftArrow");
	}
	else
	{
		m_position = Vector2(NOMAL_X, POSITION_Y);
		//�ړ�Tween�쐬
		tween->DoVector2(m_position, Vector2(NOMAL_X + MOVEING, POSITION_Y), MOVE_SPEED).
			SetLoop(-1).SetEase(Easing::Ease::InOutQuad);
		//�ʒm�쐬
		m_selectSubject = AddComponent<Subject<>>(this, "RightArrow");
	}

	//�I�u�U�[�o�[�쐬
	m_observer = AddComponent<Observer<>>(this);
	m_observer->SetFunction([&]() {CheckView(); });
	m_observer->RegistrationSubject("LeftArrow");
	m_observer->RegistrationSubject("RightArrow");

	//�T�E���h�쐬
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select3", false);

	//�\�����f
	CheckView();
}

/// <summary>
/// �ʒu���X�V
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void SelectArrow::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetPosition(m_position);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void SelectArrow::MouseWithinEvent(bool within)
{
	//�F�ύX
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0.33, 1, 0.8, 1.0f));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void SelectArrow::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (!GetActive())return;
	if (!within)return;
	m_sound->Play();
	if (m_inversion)
	{
		//�X�e�[�W�ԍ���1���炷
		if (GameManager::GetInstance()->ChangeStage(-1))
		{
			//�ʒm
			m_selectSubject->Notify();
		}
	}
	else
	{
		//�X�e�[�W�ԍ���1���₷
		if (GameManager::GetInstance()->ChangeStage(1))
		{
			//�ʒm
			m_selectSubject->Notify();
		}
	}
}

/// <summary>
/// �\�����f
/// </summary>
void SelectArrow::CheckView()
{
	SetActive(true);
	std::pair<int, int> stageNum = GameManager::GetInstance()->GetStageNum();

	if (m_inversion)
	{
		//�Œ�X�e�[�W�Ȃ�`�悵�Ȃ�
		if (stageNum.first * 10 + stageNum.second == 11)SetActive(false);
	}
	else
	{
		//�ō��X�e�[�W�Ȃ�`�悵�Ȃ�
		if (stageNum.first * 10 + stageNum.second >=
			GameManager::GetInstance()->MAX_STAGE_MAIN * 10 + GameManager::GetInstance()->MAX_STAGE_SUB)
			SetActive(false);
	}
}
