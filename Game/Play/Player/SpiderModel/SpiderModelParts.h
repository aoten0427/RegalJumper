// ================================================================ 
// �t�@�C���� : SpiderModelParts.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�p�C�_�[���f���̊e�p�[�c
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"

class Model3D;
class Camera;

class SpiderModelParts :public Object
{
public:
	//���O�擾
	std::string GetName()const { return m_name; }
	//���f���擾
	Model3D* GetModel() { return m_model; }
	//�e�N�X�`���擾
	ID3D11ShaderResourceView** GetTexture() { return m_modelTexture.GetAddressOf(); }
private:
	//���O
	std::string m_name;
	//���f��
	Model3D* m_model;
	//	�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_modelTexture;
public:
	//�R���X�g���N�^
	SpiderModelParts(Scene* scene, std::string name, std::string modelname, std::string texturename);
	//�f�X�g���N�^
	~SpiderModelParts()override = default;
};