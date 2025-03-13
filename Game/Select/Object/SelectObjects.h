// ================================================================ 
// �t�@�C���� : SelectObjects.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[���ł̃I�u�W�F�N�g
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;
class SpiderModels;

class SelectObjects :public Object
{
private:
	//�w偃��f��
	SpiderModels* m_model;
	//�v���C�V�[���ڍs�I�u�U�[�o�[
	Observer<>* m_toPlayObserver;
public:
	//�R���X�g���N�^
	SelectObjects(Scene* scene);
	//�f�X�g���N�^
	~SelectObjects()override = default;
private:
	//�v���C�V�[���J�ڏ���
	void ToPlay();
};