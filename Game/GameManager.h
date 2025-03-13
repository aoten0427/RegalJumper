// ================================================================ 
// �t�@�C���� : GameManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[�����ʂ̏����Ǘ�
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"

class Option;
class Cursor;

class GameManager :public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
private:
	GameManager();
public:
	const int MAX_STAGE_MAIN = 1;
	const int MAX_STAGE_SUB = 4;
public:
	//�X�e�[�W�ԍ�����Ԃ�
	int GetStageNumber() const { return g_stageNumber; }
	//���U���g�^�C���Z�b�g
	void SetResultTimer(float timer) { m_resultTimer = timer; }
	//���U���g�^�C���擾
	float GetResultTime()const { return m_resultTimer; }
private:
	//�X�e�[�W�ԍ�
	int g_stageNumber;
	//�I�v�V����
	Option* g_option;
	//�J�[�\��
	Cursor* g_cursor;
	//���U���g�\���^�C��
	float m_resultTimer;
public:
	~GameManager();

	//�I�v�V�����Z�b�g
	void SetOption(Option* option);
	//�I�v�V�������J��
	void OpenOption();
	//���x���擾
	float GetSensitivity();
	//�J�[�\�����Z�b�g
	void SetCursor(Cursor* cursor);
	//�J�[�\���̕\����ς���
	void ViewCursor(bool view);

	//�X�e�[�W�ԍ����Z_�Z�̌`���ŕԂ�
	std::string GetStageName();
	//�X�e�[�W�ԍ����Z_�Z�̌`���ŕԂ�
	std::pair<int, int> GetStageNum();
	//�X�e�[�W�ԍ���ω�������
	bool ChangeStage(int add);
};
