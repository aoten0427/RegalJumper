// ================================================================ 
// �t�@�C���� : SelectStageData.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�ԍ���\��
// ================================================================
#include"pch.h"
#include"SelectStageData.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
SelectStageData::SelectStageData(Canvas* canvas):UserInterface(canvas)
	,
	m_numberSize{ 70,100 },
	m_stageNumber{}
{
	using namespace DirectX::SimpleMath;
	SetColor(Vector4(0, 0, 0, 0));

	//�n�C�t���쐬
	UserInterface* hyphen = GetScene()->AddObject<UserInterface>(canvas,"Hyphen",1);
	hyphen->SetPosition(Vector2(960, 175));
	hyphen->SetOffset(Vector2(0.5f, 1));

	//�X�e�[�W�ԍ��쐬
	for (int i = 0; i < 2; i++)
	{
		m_stageNumber[i] = GetScene()->AddObject<UserInterface>(canvas,"Numbers",1);
		m_stageNumber[i]->SetSize(m_numberSize);
		m_stageNumber[i]->SetOffset(Vector2(0.5f, 1));
	}
	//�ʒu����
	m_stageNumber[0]->SetPosition(Vector2(870, 175));
	m_stageNumber[1]->SetPosition(Vector2(1050, 175));
	//�X�e�[�W�ԍ��̃N���b�v
	std::pair<int, int> stageNum = GameManager::GetInstance()->GetStageNum();
	m_stageNumber[0]->SetClipRange(Vector4(stageNum.first / 10.0f, 0, 0.1f, 1.0f));
	m_stageNumber[1]->SetClipRange(Vector4(stageNum.second / 10.0f, 0, 0.1f, 1.0f));

	m_tween = AddComponent<Tween>(this,true);

	//�f�[�^�X�V�I�u�U�[�o�[�쐬
	m_observer = AddComponent<Observer<>>(this);
	m_observer->SetFunction([&]() {DataUpdate(); });
	m_observer->RegistrationSubject("LeftArrow");
	m_observer->RegistrationSubject("RightArrow");
}

/// <summary>
/// �ʒu�X�V
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void SelectStageData::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	m_stageNumber[0]->SetSize(m_numberSize);
	m_stageNumber[1]->SetSize(m_numberSize);
}

/// <summary>
/// �f�[�^�X�V
/// </summary>
void SelectStageData::DataUpdate()
{
	using namespace DirectX::SimpleMath;

	//�\��������
	m_tween->DoVector2(m_numberSize, Vector2(70, 0), 0.1f).SetCompleteFunction([&]() {
		//�X�e�[�W�ԍ��̃N���b�v
		std::pair<int, int> stageNum = GameManager::GetInstance()->GetStageNum();
		m_stageNumber[0]->SetClipRange(Vector4(stageNum.first / 10.0f, 0, 0.1f, 1.0f));
		m_stageNumber[1]->SetClipRange(Vector4(stageNum.second / 10.0f, 0, 0.1f, 1.0f));
		//�\��������
		m_tween->DoVector2(m_numberSize, Vector2(70, 100), 0.1f);
		});
}
