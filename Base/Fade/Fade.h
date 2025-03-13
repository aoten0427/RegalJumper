// ================================================================ 
// �t�@�C���� : Fade.h
// �쐬�� : �i�R�ɓV
// ���� :  �t�F�[�h���N���X
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Fade :public UserInterface
{
public:
	//�t�F�[�h���
	enum class State
	{
		Out,
		DoIn,
		In,
		DoOut
	};
public:
	//��ԃZ�b�g
	void SetState(const State& state) { m_state = state; }
	//��Ԏ擾
	State GetState()const { return m_state; }
	//���O�擾
	std::string GetName()const { return m_name; }
private:
	//���g�̏��
	State m_state;
	//���g�̖��O
	std::string m_name;
public:
	Fade(Canvas* canvas, std::string fadeName);
	~Fade();
	//�t�F�[�h�J�n
	virtual void Start(std::function<void()> function = nullptr) = 0;
};