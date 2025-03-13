/*
	@file	CommonResources.cpp
	@brief	�V�[���֓n���A�Q�[�����Ŏg�p���鋤�ʃ��\�[�X
*/
#include "pch.h"
#include "CommonResources.h"
#include <cassert>

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
CommonResources::CommonResources()
	:
	m_stepTimer{ nullptr },
	m_deviceResources{ nullptr },
	m_commonStates{ nullptr },
	m_debugString{ nullptr }
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void CommonResources::Initialize(
	DX::StepTimer* timer,
	DX::DeviceResources* dr,
	DirectX::CommonStates* commonStates,
	mylib::DebugString* debugString,
	DirectXInputs* input
)
{
	assert(timer);
	assert(dr);
	assert(commonStates);
	assert(debugString);
	

	m_stepTimer = timer;
	m_deviceResources = dr;
	m_commonStates = commonStates;
	m_debugString = debugString;
	m_inputs = input;
}
