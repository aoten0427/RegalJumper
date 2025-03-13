// ================================================================ 
// �t�@�C���� : ResultStageData.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�ł̃X�e�[�W���\��
// ================================================================
#include"pch.h"
#include"ResultStageData.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
ResultStageData::ResultStageData(Canvas* canvas):UserInterface(canvas)
{
	using namespace DirectX::SimpleMath;
	SetActive(false);
	//�{�[�h����
	UserInterface* board = GetScene()->AddObject<UserInterface>(canvas, "ResultBoard",2);
	board->SetPosition(Vector2(330, 155));
	board->SetSize(Vector2(660, 150));
	//�X�e�[�W�ԍ����擾
	std::pair<int,int> stageNum = GameManager::GetInstance()->GetStageNum();
	//��ԍ�����
	UserInterface* number = GetScene()->AddObject<UserInterface>(canvas, "Numbers", 3);
	number->SetClipRange(Vector4(stageNum.first / 10.0f, 0, 0.1f, 1.0f));
	number->SetPosition(Vector2(180, 155));
	//���ԍ�����
	number = GetScene()->AddObject<UserInterface>(canvas, "Numbers", 3);
	number->SetClipRange(Vector4(stageNum.second / 10.0f, 0, 0.1f, 1.0f));
	number->SetPosition(Vector2(380, 155));
	//�n�C�t������
	UserInterface* hyphen = GetScene()->AddObject<UserInterface>(canvas, "Hyphen", 3);
	hyphen->SetPosition(Vector2(280, 155));
}
