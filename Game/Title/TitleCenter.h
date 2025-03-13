// ================================================================ 
// �t�@�C���� :TitleCenter 
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g���V�[�����Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"

template<typename...Args>
class Observer;

class TitleCenter :public Object
{
private:
	//�J�n�I�u�U�[�o�[
	Observer<>* m_begin;
public:
	//�R���X�g���N�^
	TitleCenter(Scene* scene);
	//�f�X�g���N�^
	~TitleCenter()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
};
