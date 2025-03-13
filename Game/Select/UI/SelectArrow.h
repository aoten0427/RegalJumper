// ================================================================ 
// �t�@�C���� : SelectArrow.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�I����
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

template<typename...Args>
class Subject;
template<typename...Args>
class Observer;
class Sound;

class SelectArrow :public Button
{
private:
	//���]�m�F
	bool m_inversion;
	//�|�W�V����
	DirectX::SimpleMath::Vector2 m_position;
	//�N���b�N���ʒm
	Subject<>* m_selectSubject;
	//�X�e�[�W�ύX�I�u�U�[�o�[
	Observer<>* m_observer;
	//�T�E���h
	Sound* m_sound;
public:
	//�R���X�g���N�^
	SelectArrow(Canvas* canvas, bool inversion = false);
	//�f�X�g���N�^
	~SelectArrow()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime);
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within);
	//���N���b�N�C�x���g
	void LeftClickEvent(bool within);
private:
	//�\���𔻒f
	void CheckView();
};