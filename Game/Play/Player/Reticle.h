// ================================================================ 
// �t�@�C���� : Reticle.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�̃��e�B�N��
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Player;
class Camera;
class Segment;
template<typename ...Args>
class Subject;

class Reticle :public Object
{
private:
	//�v���C���[
	Player* m_player;
	//�J����
	Camera* m_caemra;
	//����
	Segment* m_segment;
	//�q�b�g���̃T�u�W�F�N�g
	Subject<bool>* m_subject;
	//�����������ǂ���
	bool m_ishit;
	//�O�t���[���̓�����
	bool m_oldhit;
public:
	//�R���X�g���N�^
	Reticle(Scene* scene,Player* player);
	//�f�X�g���N�^
	~Reticle() override = default;
	//�X�V
	void ObjectUpdate(float deltatime)override;
	//Trigger�̎��s�L��
	bool IsTriggerAct(Collider* collider) override;
	//Trigger����
	void OnTrigger(Collider* collider) override;
};