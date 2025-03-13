// ================================================================ 
// �t�@�C���� : Goal.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �S�[��
// ================================================================
#include"pch.h"
#include"Goal.h"
#include"Base/Base.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
Goal::Goal(Scene* scene):Object(scene)
{
	using namespace DirectX::SimpleMath;

	//���f������
	auto model = AddComponent<Model3D>(this,"Goal");
	model->SetPosition(Vector3(0, 0.02f, 0));
	model->SetScale(Vector3(24.0f, 24.0f, 24.0f));
	//�R���C�_�[����
	AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr, false,2.0f);
}
