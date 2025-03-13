// ================================================================ 
// �t�@�C���� : SpiderModelParts.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �X�p�C�_�[���f���̊e�p�[�c
// ================================================================
#include"pch.h"
#include"SpiderModelParts.h"
#include"Base/Resource/GameResources.h"
#include"Base/Base.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="name">�p�[�c��</param>
/// <param name="modelname">�ǂݍ��݃��f����</param>
/// <param name="texturename">�ǂݍ��݉摜��</param>
SpiderModelParts::SpiderModelParts(Scene* scene, std::string name, std::string modelname, std::string texturename):Object(scene)
	,
	m_name{name}
{
	m_model = AddComponent<Model3D>(this, modelname);
	m_model->SetActive(false);
	//���f���摜���[�h
	m_modelTexture = GameResources::GetInstance()->GetTexture(texturename);
}



