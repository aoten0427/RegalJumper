// ================================================================ 
// �t�@�C���� : ThreadHolder.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ����ێ�����@�\
// ================================================================
#include"pch.h"
#include"ThreadHolder.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object"></param>
ThreadHolder::ThreadHolder(Object* object) :Component(object)
	,
	m_conectFunction{ nullptr },
	m_cutFunction{ nullptr }
{
}

/// <summary>
/// �Ȃ�����
/// </summary>
void ThreadHolder::Conect()
{
	if (m_conectFunction)m_conectFunction();
}

/// <summary>
/// �؂ꂽ
/// </summary>
void ThreadHolder::Cut()
{
	if (m_cutFunction)m_cutFunction();
}
