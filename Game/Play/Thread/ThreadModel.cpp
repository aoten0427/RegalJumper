// ================================================================ 
// �t�@�C���� : ThreadModel.h
// �쐬�� : �i�R�ɓV
// ���� :  ���̃��f��
// ================================================================
#include"pch.h"
#include"ThreadModel.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Particle.h"

//������]��
constexpr DirectX::SimpleMath::Vector3 INITIAL_DIRECTION = DirectX::SimpleMath::Vector3(0, 0, 1);
//��{�̒���
constexpr float BASE_LENTH = 11.95;
//����
constexpr float THICKNESS = 2.5f;
//�X�v���C���̎���
constexpr int DEGREE = 3;
//�X�v���C���̃|�C���g��
constexpr int SPLINE_POINTS = 60;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene"></param>
/// <param name="thread"></param>
ThreadModel::ThreadModel(Scene* scene, Thread* thread):Object(scene)
	,
	m_thread{thread}
{
	using namespace DirectX;
	//���f���ǂݍ���
	m_model = AddComponent<Model3D>(this, "Thread");
	//�^�����ɂ���
	m_model->GetModel()->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �ʂ̃��C�g�����ׂĖ���������
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// ���f����������������
				basicEffect->SetEmissiveColor(XMVECTOR{ 1.0f,1.0f,1.0f,1 });
			}
		}
	);
	m_model->SetRender(std::bind(&ThreadModel::Render, this, std::placeholders::_1));
	//�N�����v�m�b�g���v�Z
	m_knot = ClampedKnotVector(SPLINE_POINTS, DEGREE);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera"></param>
void ThreadModel::Render(const Camera& camera)
{
	if (m_thread->GetThreadParticles().empty())return;

	using namespace DirectX::SimpleMath;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();


	std::vector<Vector3> positions;
	RopeSolver* rope = m_thread->GetRopeSolver();

	//�`��ꏊ�̈ʒu��ݒ�
	for (auto& particle : rope->GetParticles())
	{
		positions.push_back(particle->GetObject()->GetTransform()->GetPosition());
	}

	std::vector<Vector3> sprin = ComputeBSplineCurve(positions,3,1.0f / SPLINE_POINTS);
	sprin.push_back(positions.back());

	for (int i = 0; i <sprin.size() - 1; i++)
	{
		//���������߂�
		Vector3 distance = sprin[i + 1] - sprin[i];
		//���������߂�
		float lenth = distance.Length();
		//�g��l�����߂�
		float size = lenth / BASE_LENTH;

		distance.Normalize();
		//�����l����̊p�x�����߂�
		float dot = distance.Dot(INITIAL_DIRECTION);
		float angle = -acos(dot);
		//��]�������߂�
		Vector3 axis = distance.Cross(INITIAL_DIRECTION);
		if (axis.Length() == 0)continue;
		//�N�H�[�^�j�I���v�Z
		Quaternion roteto = Quaternion::CreateFromAxisAngle(axis, angle);
		//matrix
		Matrix mat = Matrix::CreateScale(Vector3(THICKNESS, THICKNESS, size));
		mat *= Matrix::CreateFromQuaternion(roteto);
		mat *= Matrix::CreateTranslation(sprin[i]);

		//���f���`��
		m_model->GetModel()->Draw(context, *states, mat, camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
}

/// <summary>
/// �m�b�g�x�N�g�����v�Z
/// </summary>
/// <param name="p">�|�C���g��</param>
/// <param name="n">����</param>
/// <returns></returns>
std::vector<float> ThreadModel::ClampedKnotVector(int p, int n)
{
	int m = p + n + 1;
	std::vector<float> u(m);

	// �ŏ��� n+1 �̃m�b�g�� 0 �ɌŒ�i�n�_���Œ�j
	for (int i = 0; i <= n; ++i) {
		u[i] = 0.0f;
	}

	// ���Ԃ̃m�b�g���ϓ��ɔz�u�iB�X�v���C���̃X���[�Y�ȑJ�ڂ��m�ہj
	for (int i = 1; i < p - n; ++i) {
		u[n + i] = (float)i / (p - n);
	}

	// �Ō�� n+1 �̃m�b�g�� 1 �ɌŒ�i�I�_���Œ�j
	for (int i = m - n - 1; i < m; ++i) {
		u[i] = 1.0f;
	}

	return u;
}


/// <summary>
/// B�X�v���C���̊��֐����v�Z
/// </summary>
/// <param name="u">�m�b�g�x�N�g��</param>
/// <param name="j">�Ώۂ̐���_�C���f�b�N�X</param>
/// <param name="k">�X�v���C���̎���</param>
/// <param name="t">�p�����[�^�l�i0.0 �` 1.0�j</param>
/// <returns>�w�肳�ꂽ����_�ɑ΂�����֐��̒l</returns>
float ThreadModel::BasisFunction(const std::vector<float>& u, int j, int k, float t)
{
	// 0�����֐��̒�`�i�Y����ԂȂ�1.0�A����ȊO��0.0�j
	if (k == 0) {
		return (u[j] <= t && t < u[j + 1]) ? 1.0f : 0.0f;
	}

	float w1 = 0.0f, w2 = 0.0f;

	// �����̊��֐��̏d�݌v�Z�it���m�b�g�Ԃɂ���ꍇ�j
	if ((u[j + k] - u[j]) != 0.0f) {
		w1 = ((t - u[j]) / (u[j + k] - u[j])) * BasisFunction(u, j, k - 1, t);
	}

	// �E���̊��֐��̏d�݌v�Z
	if ((u[j + k + 1] - u[j + 1]) != 0.0f) {
		w2 = ((u[j + k + 1] - t) / (u[j + k + 1] - u[j + 1])) * BasisFunction(u, j + 1, k - 1, t);
	}

	return w1 + w2;
}


/// <summary>
/// B�X�v���C���Ȑ����v�Z
/// </summary>
/// <param name="P">����_���X�g</param>
/// <param name="n">�X�v���C���̎���</param>
/// <param name="step">�v�Z����Ԋu</param>
/// <returns>�Ȑ����X�g</returns>
std::vector<DirectX::SimpleMath::Vector3> ThreadModel::ComputeBSplineCurve(
	const std::vector<DirectX::SimpleMath::Vector3>& P, int n, float step)
{
	std::vector<DirectX::SimpleMath::Vector3> S;

	// �X�v���C���͈̔́i�n�_�ƏI�_�j
	float t_start = m_knot[n];
	float t_end = m_knot[P.size()];

	// �w�肵���Ԋu�ŋȐ���̓_���v�Z
	for (float t = t_start; t <= t_end; t += step) {
		DirectX::SimpleMath::Vector3 point = { 0.0f, 0.0f, 0.0f };

		// �e����_�ɑ΂�����֐��̏d�ݕt�����v�Z���A�ŏI�I�ȍ��W�����߂�
		for (int j = 0; j < P.size(); ++j) {
			float b = BasisFunction(m_knot, j, n, t);
			point = point + P[j] * b;
		}

		S.push_back(point);
	}

	return S;
}
