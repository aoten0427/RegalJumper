// ================================================================ 
// �t�@�C���� : ThreadModel.h
// �쐬�� : �i�R�ɓV
// ���� :  ���̃��f��
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Thread;
class Model3D;
class Camera;

class ThreadModel :public Object
{
private:
	//��
	Thread* m_thread;
	//���f��
	Model3D* m_model;
	//
	std::vector<float> m_knot;
public:
	//�R���X�g���N�^
	ThreadModel(Scene* scene, Thread* thread);
	//�f�X�g���N�^
	~ThreadModel()override = default;
	//�`��
	void Render(const Camera& camera);

private:
	//�m�b�g�x�N�g�����v�Z
	std::vector<float> ClampedKnotVector(int p, int n);
	//B�X�v���C���̊��֐����v�Z
	float BasisFunction(const std::vector<float>& u, int j, int k, float t);
	// B�X�v���C���Ȑ����v�Z
	std::vector<DirectX::SimpleMath::Vector3> ComputeBSplineCurve(const std::vector<DirectX::SimpleMath::Vector3>& P, int n, float step = 0.01f);
};