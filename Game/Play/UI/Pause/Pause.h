// ================================================================ 
// �t�@�C���� : Pause.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C��ʃ|�[�Y
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"
#include"Base/Scene/Scene.h"

template<typename...Args>
class Subject;
class PauseButton;
class QuitPage;

class Pause :public UserInterface
{
private:
	//open�t���O
	bool m_isOpen;
	//���w�i�ȊO��UI�̐e
	Object* m_UIBase;
	//�x�[�X
	UserInterface* m_base;
	//�ޏo�y�[�W
	QuitPage* m_quitPage;
	//�I�[�v���T�u�W�F�N�g
	Subject<>* m_openSubject;
	//�N���[�Y�T�u�W�F�N�g
	Subject<>* m_closeSubject;
	//�O��̃V�[���X�e�[�g
	Scene::State m_oldSceneState;
public:
	//�R���X�g���N�^
	Pause(Canvas* canvas);
	//�f�X�g���N�^
	~Pause()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	//�J��
	void Open();
	//����
	void Close();
};