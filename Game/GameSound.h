// ================================================================ 
// �t�@�C���� : GameSound.h
// �쐬�� : �i�R�ɓV
// ���� :  BGM�̊Ǘ�
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Sound;

class GameSound :public Object
{
private:
	//�^�C�g���T�E���h
	Sound* m_titileSound;
	//�v���C�T�E���h
	Sound* m_playSound;
public:
	//�R���X�g���N�^
	GameSound(Scene* scene);
	//�f�X�g���N�^
	~GameSound()override = default;
	//�V�[���؂�ւ����C�x���g
	void LoadScene(Scene* scene) override;
};