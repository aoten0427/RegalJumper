// ================================================================ 
// �t�@�C���� : TargetBox.h
// �쐬�� : �i�R�ɓV
// ���� :  �ړ��Ɏg���^�[�Q�b�g�I�u�W�F�N�g
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Model3D;
class Camera;
class RenderPrimitive;
class Target;
class TargetMark;
class Tween;

class TargetBox :public Object
{
private:
	//���
	enum  class State
	{
		CLOSE,
		OPEN,
		MOVE
	};
public:
	//�^�O�擾
	ObjectTag GetTag() { return ObjectTag::TargetBox; };
private:
	//���C�����f��
	Model3D* m_mainModel;
	//�T�u���f��
	Object* m_subModels[8];
	//�^�[�Q�b�g
	Target* m_target;
	//�^�[�Q�b�g�}�[�N
	TargetMark* m_targetMark;
	//���
	State m_state;
	//�ړ���
	float m_movePar;
	//Tween
	Tween* m_tween;
public:
	//�R���X�g���N�^
	TargetBox(Scene* scene);
	//�f�X�g���N�^
	~TargetBox()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
private:
	//�J��
	void Open();
	//�Ƃ���
	void Close();
	//�J����
	void Move();
};