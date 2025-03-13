// ================================================================ 
// �t�@�C���� : GameManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[�����ʂ̏����Ǘ�
// ================================================================
#include"pch.h"
#include"GameManager.h"
#include"Game/Option/Option.h"	
#include"Game/Cursor/Cursor.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameManager::GameManager()
	:
	g_stageNumber{11},
	g_option{nullptr},
	g_cursor{nullptr},
	m_resultTimer{0}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameManager::~GameManager()
{
	g_option = nullptr;
	g_cursor = nullptr;
}

/// <summary>
/// �I�v�V�������Z�b�g
/// </summary>
/// <param name="option">�I�v�V����</param>
void GameManager::SetOption(Option* option)
{
	if (g_option)return;
	g_option = option;
}

/// <summary>
/// �I�v�V�������J��
/// </summary>
void GameManager::OpenOption()
{
	if (!g_option)return;
	g_option->Open();
}

/// <summary>
/// ���x���擾
/// </summary>
/// <returns>���݂̊��x</returns>
float GameManager::GetSensitivity()
{
	if (!g_option) return 1.0;
	return g_option->GetSensitivity();
}

/// <summary>
/// �J�[�\�����Z�b�g
/// </summary>
/// <param name="cursor">�J�[�\��</param>
void GameManager::SetCursor(Cursor* cursor)
{
	if (g_cursor)return;
	g_cursor = cursor;
}

/// <summary>
/// �J�[�\���̕\����ς���
/// </summary>
/// <param name="view">�\���L��</param>
void GameManager::ViewCursor(bool view)
{
	if (!g_cursor)return;
	g_cursor->SetActive(view);
}

/// <summary>
/// �X�e�[�W�ԍ����Z_�Z�̌`���ŕԂ�
/// </summary>
/// <returns>�X�e�[�W��</returns>
std::string GameManager::GetStageName()
{
	int main = g_stageNumber / 10;
	int sub = g_stageNumber % 10;
	std::string stagename = std::to_string(main) + "_" + std::to_string(sub);
	return stagename;
}

/// <summary>
///�X�e�[�W�ԍ���Ԃ�
/// </summary>
/// <returns>�X�e�[�W�ԍ�</returns>
std::pair<int, int> GameManager::GetStageNum()
{
	int main = g_stageNumber / 10;
	int sub = g_stageNumber % 10;

	return std::pair<int, int>(main, sub);
}

/// <summary>
/// �X�e�[�W�ԍ���ω�������
/// </summary>
/// <param name="add">�ω���</param>
/// <returns>�ω��ł�����</returns>
bool GameManager::ChangeStage(int add)
{
	int main = g_stageNumber / 10;
	int sub = g_stageNumber % 10;

	sub += add;
	//�T�u�l�̋��E�m�F
	if (sub > MAX_STAGE_SUB)
	{
		main += 1;
		sub = sub - MAX_STAGE_SUB;
	}
	if (sub <= 0)
	{
		main -= 1;
		sub = sub + MAX_STAGE_SUB;
	}

	//�X�e�[�W���ߊm�F
	if (MAX_STAGE_MAIN * 10 + MAX_STAGE_SUB < main * 10 + sub)return false;
	//�X�e�[�W�����m�F
	if (main <= 0)return false;

	//�X�e�[�W�ԍ����X�V
	g_stageNumber = main * 10 + sub;
	return true;
}




