// ================================================================ 
// �t�@�C���� : ThreadHolder.h
// �쐬�� : �i�R�ɓV
// ���� :  ����ێ�����@�\
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class ThreadHolder :public Component
{
public:
	//�ڑ����Ăяo���֐��Z�b�g
	void SetConect(std::function<void()> function) { m_conectFunction = function; }
	//�؂ꂽ�ۂɌĂяo���֐��Z�b�g
	void SetCut(std::function<void()> function) { m_cutFunction = function; }
private:
	//�Ȃ������ۂɌĂяo���֐�
	std::function<void()> m_conectFunction;
	//�؂ꂽ�ۂɌĂяo���֐�
	std::function<void()> m_cutFunction;
public:
	//�R���X�g���N�^
	ThreadHolder(Object* object);
	//�f�X�g���N�^
	~ThreadHolder()override = default;
	//�Ȃ�����
	void Conect();
	//�؂ꂽ
	void Cut();
};
