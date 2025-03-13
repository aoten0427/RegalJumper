// ================================================================ 
// �t�@�C���� : RigidbodyManager.h
// �쐬�� : �i�R�ɓV
// ���� :  RIgidbody�̊Ǘ����s��
// ================================================================

#pragma once

class Rigidbody;

class RigidbodyManager
{
private:
	//�Ǘ�Rigidbody
	std::unordered_set<Rigidbody*> m_rigidbodys;
public:
	//�R���X�g���N�^
	RigidbodyManager();
	//�f�X�g���N�^
	~RigidbodyManager() = default;
	//�A�b�v�f�[�g
	void Update(float deltatime);
	//Rigidbody�ǉ�
	void AddRigidbody(Rigidbody* rigidbody);
	//Rigidbody�폜
	void RemoveRigidbody(Rigidbody* rigidbody);
};