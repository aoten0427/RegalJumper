// ================================================================ 
// �t�@�C���� : PlayCenter.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���̊Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;
template<typename...Args>
class Subject;

class PlayCenter :public Object
{
private:
	//���Z�b�g�֐��Ăяo���I�u�U�[�o�[
	Observer<>* m_resetObserver;
	// ���Z�b�g�֐��Ăяo���T�u�W�F�N�g
	Subject<>* m_resetSubject;
	//���U���g��ʈȍ~�I�u�U�[�o�[
	Observer<>* m_exitObserver;
public:
	//�R���X�g���N�^
	PlayCenter(Scene* scene);
	//�f�X�g���N�^
	~PlayCenter() override = default;
private:
	//�v���C�V�[�����Z�b�g����
	void Reset();
	//���U���g�V�[���J�ڏ���
	void ToResult();
};