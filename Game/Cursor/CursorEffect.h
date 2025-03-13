// ================================================================ 
// �t�@�C���� : CursorEffect.h
// �쐬�� : �i�R�ɓV
// ���� :  �J�[�\���N���b�N���̃G�t�F�N�g
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class CursorEffect :public UserInterface
{
private:
	//�傫��
	float m_size;
public:
	//�R���X�g���N�^
	CursorEffect(Canvas* canvas,DirectX::SimpleMath::Vector2 position);
	//�f�X�g���N�^
	~CursorEffect()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
};