// ================================================================ 
// �t�@�C���� : RigidbodyManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  RIgidbody�̊Ǘ����s��
// ================================================================
#include"pch.h"
#include "RIgidbodyManager.h"
#include"Base/Component/Rigidbody/Rigidbody.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
RigidbodyManager::RigidbodyManager()
{

}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void RigidbodyManager::Update(float deltatime)
{
	for (auto rigidbody : m_rigidbodys)
	{
		if (!rigidbody->GetActive())continue;
		rigidbody->Compute(deltatime);
	}
}

/// <summary>
/// Rigidbody�ǉ�
/// </summary>
/// <param name="rigidbody">�ǉ�Rigidbody</param>
void RigidbodyManager::AddRigidbody(Rigidbody* rigidbody)
{
	m_rigidbodys.insert(rigidbody);
}

/// <summary>
/// Rigidbody�폜
/// </summary>
/// <param name="rigidbody">�폜Rigidbody</param>
void RigidbodyManager::RemoveRigidbody(Rigidbody* rigidbody)
{
	m_rigidbodys.erase(rigidbody);
}
