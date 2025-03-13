// ================================================================ 
// �t�@�C���� : SelectCenter.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[�����Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;

class SelectCenter :public Object
{
private:
	//�J�n�I�u�U�[�o�[
	Observer<>* m_begin;
	//�I���I�u�U�[�o�[
	Observer<>* m_finish;
public:
	//�R���X�g���N�^
	SelectCenter(Scene* scene);
	//�f�X�g���N�^
	~SelectCenter()override = default;
};
