// ================================================================ 
// �t�@�C���� : IState.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�g�̃C���^�[�t�F�[�X
// ================================================================

#pragma once

class IState
{
public:
	virtual ~IState() = default;
	// ���O�X�V����
	virtual void PreUpdate() = 0;
	// �X�V����
	virtual void Update(float deltaTime) = 0;
	// ����X�V����
	virtual void PostUpdate() = 0;
};