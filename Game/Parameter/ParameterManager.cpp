// ================================================================ 
// �t�@�C���� : ParameterManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �p�����[�^�ǂݍ��݃N���X
// ================================================================
#include"pch.h"
#include"ParameterManager.h"
#include"PlayerParameter.h"
#include"ThreadParameter.h"

/// <summary>
/// �e�p�����[�^�ǂݍ���
/// </summary>
void ParameterManager::LoadDaata()
{
	PlayerParameter::LOAD_DATA();
	ThreadParameter::LOAD_DATA();
}
