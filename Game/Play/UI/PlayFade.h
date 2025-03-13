// ================================================================ 
// �t�@�C���� : PlayFade.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[�����Z�b�g�p�t�F�[�h
// ================================================================

#pragma once
#include"Base/Fade/Fade.h"

class Sequence;


class PlayFade :public Fade
{
private:
	//�\���ʒu
	DirectX::SimpleMath::Vector2 m_position;
	//�ړ��Ɏg��Sequence
	Sequence* m_sequence;
	//�N���[�Y�����ۂ̏���
	std::function<void()> m_closeFunction;
public:
	//�R���X�g���N�^
	PlayFade(Canvas* canvas);
	//�f�X�g���N�^
	~PlayFade() override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//�t�F�[�h�J�n
	void Start(std::function<void()> function = nullptr);
};