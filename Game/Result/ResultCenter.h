// ================================================================ 
// �t�@�C���� : ResultCenter.h
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�V�[���̊Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;
template<typename...Args>
class Subject;

class ResultCenter :public Object
{
private:
	//�J�n�I�u�U�[�o�[
	Observer<>* m_beginObserver;
	//�X�L�b�v�Ăяo���T�u�W�F�N�g
	Subject<>* m_skipSubject;
public:
	//�R���X�g���N�^
	ResultCenter(Scene* scene);
	//�f�X�g���N�^
	~ResultCenter()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
};