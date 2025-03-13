// ================================================================ 
// �t�@�C���� : GameFade.h
// �쐬�� : �i�R�ɓV
// ���� :  �Q�[���̊�{�t�F�[�h
// ================================================================

#pragma once
#include"Base/Fade/Fade.h"

class Sequence;
template<typename...Args>
class Subject;

class GameFade :public Fade
{
private:
	//�\���ʒu
	DirectX::SimpleMath::Vector2 m_position;
	//�ړ��Ɏg��Sequence
	Sequence* m_sequence;
	//�N���[�Y�����ۂ̏���
	std::function<void()> m_closeFunction;
	//�t�F�[�h�I���ʒm
	Subject<>* m_finishSubject;
public:
	//�R���X�g���N�^
	GameFade(Canvas* canvas);
	//�f�X�g���N�^
	~GameFade()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//�t�F�[�h�J�n
	void Start(std::function<void()> function = nullptr);
};