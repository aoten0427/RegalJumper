// ================================================================ 
// �t�@�C���� : ITweenUpdate.h
// �쐬�� : �i�R�ɓV
// ���� :  TweenUpdate�C���^�[�t�F�[�X
// ================================================================

#pragma once
#include"Easing.h"

class ITweenUpdate
{
public:
	virtual ~ITweenUpdate() = default;
	//�A�b�v�f�[�g
	virtual bool Update(float deltatime) = 0;
	//�C�[�W���O��ސݒ�
	virtual void SetEase(const Easing::Ease& easy) = 0;
	//�l�ύX(�����߂�)
	virtual void Yoyo() = 0;
	//�l�ύX(�����ݒ�)
	virtual void ReStart() = 0;
	//�l�ύX(���Z)
	virtual void Incremental() = 0;
	//��������
	virtual void Kill() = 0;
	//�ω��ʂ𑊑Βl�Ƃ��ė��p
	virtual void Relative() = 0;
	//�I�_�͕ς����ɏ����l�ύX
	virtual void ReLoad() = 0;
};