// ================================================================ 
// �t�@�C���� : Thread.h
// �쐬�� : �i�R�ɓV
// ���� :  ��
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class ThreadStateMachine;
class RopeSolver;
class ThreadParticle;
class ThreadHolder;
class Target;

class Thread :public Object
{
public:
	//�����΂��ۂ̃f�[�^
	struct  ThreadData
	{
		Object* m_holder;//������             
		ThreadHolder* m_threadHolder;//�z���_�[�@�\
		DirectX::SimpleMath::Vector3 m_startPosition;//���ˈʒu
		DirectX::SimpleMath::Vector3 m_direction;//���˕���
		Target* m_target;//�^�[�Q�b�g

		void DataSet(Object* holder, DirectX::SimpleMath::Vector3 strpos, DirectX::SimpleMath::Vector3 dire)
		{
			m_holder = holder;
			m_startPosition = strpos;
			m_direction = dire;
			m_target = nullptr;
		}
	};
public:
	//�X�e�[�g�}�V����n��
	ThreadStateMachine* GetStateMachine() { return m_machine.get(); }
	//�p�[�e�B�N����n��
	std::vector<ThreadParticle*> GetThreadParticles() { return m_threadparticles; }
	//�p�[�e�B�N�����Z�b�g
	void SetThreadParticle(std::vector<ThreadParticle*> threadparticle) { m_threadparticles = threadparticle; }
	//���[�v�\���o�[��n��
	RopeSolver* GetRopeSolver() { return m_ropeSolver; }
	//���f�[�^��n��
	ThreadData& GetData() { return m_data; }
	//�������Z�b�g����
	void SetRopeDistance(float distance) { m_ropeDistance = distance; }
private:
	//�X�e�[�g�}�V��
	std::unique_ptr<ThreadStateMachine> m_machine;
	//���̂܂Ƃ܂�
	RopeSolver* m_ropeSolver;
	//�����\�����闱�q
	std::vector<ThreadParticle*> m_threadparticles;
	//���g�̃f�[�^
	ThreadData m_data;
	//����
	float m_ropeDistance;
public:
	//�R���X�g���N�^
	Thread(Scene* scene);
	//�f�X�g���N�^
	~Thread()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//����
	void Shot(Object* holder, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction, Target* target);
	//�f�[�^�N���A
	void Clear();
};
