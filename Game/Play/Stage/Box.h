// ================================================================ 
// �t�@�C���� : Box.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�Ɏ�Ɏg���锠
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"

class Model3D;
class Camera;

class Box :public Object
{
public:
	//�^�O�擾
	ObjectTag GetTag() { return ObjectTag::Stage; };
private:
	Model3D* m_model;

	ShaderSet m_set;
public:
	//�R���X�g���N�^
	Box(Scene* scene);
	//�f�X�g���N�^
	~Box() override = default;

	void Render(const Camera& camera);
};
