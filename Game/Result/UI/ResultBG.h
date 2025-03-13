// ================================================================ 
// �t�@�C���� : ResultBG.h
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�w�i
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class ResultBG :public UserInterface
{
private:
	//�l�p
	std::vector<UserInterface*> m_quads;
	//�l�p�̐F
	std::vector<DirectX::SimpleMath::Vector4> m_quadsColor;
	//�l�p�̏o������
	std::vector<float> m_openTime;
	//�^�C�}�[
	float m_timer;
	//���[�v�Z�b�g�p�t���O
	bool m_flag;
public:
	//�R���X�g���N�^
	ResultBG(Canvas* canvas);
	//�f�X�g���N�^
	~ResultBG()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	//�f�[�^�ǂݍ���
	void LoadData();
	//���[�v���Z�b�g
	void LoopSet();

};