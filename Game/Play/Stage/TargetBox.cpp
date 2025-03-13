// ================================================================ 
// �t�@�C���� : TargetBox.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �ړ��Ɏg���^�[�Q�b�g�I�u�W�F�N�g
// ================================================================
#include"pch.h"
#include"TargetBox.h"
#include"Base/Base.h"
#include"Base/Tween/DoTween.h"
#include"Game/Play/Enemy/Target.h"
#include"Game/Play/Enemy/TargetMark.h"

constexpr float INITAL_EXTENS = 2.7f;
constexpr int   MARK_SIZE = 10;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
TargetBox::TargetBox(Scene* scene):Object(scene)
	,
	m_state{State::CLOSE},
	m_movePar{0}
{
	using namespace DirectX::SimpleMath;

	//���C�����f���쐬
	m_mainModel = AddComponent<Model3D>(this, "TargetMain");
	m_mainModel->SetScale(Vector3(INITAL_EXTENS, INITAL_EXTENS, INITAL_EXTENS));
	//�T�u�쐬
	for (int i = 0; i < 8; i++)
	{
		auto object = scene->AddObject<Object>(scene);
		//�e�q�ݒ�
		object->GetTransform()->SetParent(GetTransform());
		//���f���쐬
		auto model = object->AddComponent<Model3D>(object,"TargetSub");
		//�X�P�[���A��]�ݒ�
		model->SetScale(Vector3(INITAL_EXTENS, INITAL_EXTENS, INITAL_EXTENS));
		object->GetTransform()->TransRotate(Vector3::UnitY, i / 2 * 90.0f);
		object->GetTransform()->TransRotate(Vector3::UnitZ, i % 2 * 180.0f);
		m_subModels[i] = object;

	}
	//�^�[�Q�b�g�쐬
	m_target = scene->AddObject<Target>(scene,this,Target::TargetType::Move);
	//����쐬
	AddComponent<Sphere>(this, CollisionType::FIXED, nullptr, false, INITAL_EXTENS);
	//Tween�쐬
	m_tween = AddComponent<Tween>(this, true);
	//�^�[�Q�b�g�}�[�N�쐬
	m_targetMark = scene->AddObject<TargetMark>(scene, this);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void TargetBox::ObjectUpdate(float deltatime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(deltatime);

	switch (m_state)
	{
	case TargetBox::State::CLOSE:
		//�^�[�Q�b�g����Ă�����J��
		if (m_target->GetIsTarget())Open();
		break;
	case TargetBox::State::OPEN:
		//�^�[�Q�b�g����Ă��Ȃ���Ε���
		if (!m_target->GetIsTarget())Close();
		break;
	case TargetBox::State::MOVE:
		Move();
		break;
	default:
		break;
	}
}

//�J��
void TargetBox::Open()
{
	//�J���������s
	m_state = State::MOVE;
	m_tween->DoFloat(m_movePar, 1, 0.3f).SetEase(Easing::Ease::OutCubic).SetCompleteFunction([&]() {
		m_state = State::OPEN;
		});
	m_targetMark->Open();
}

//�Ƃ���
void TargetBox::Close()
{
	//���鏈�����s
	m_state = State::MOVE;
	m_tween->DoFloat(m_movePar, 0, 0.3f).SetEase(Easing::Ease::OutCubic).SetCompleteFunction([&]() {
		m_state = State::CLOSE;
		});
	m_targetMark->Close();
}

/// <summary>
/// �J����
/// </summary>
void TargetBox::Move()
{
	using namespace DirectX::SimpleMath;
	//�|�W�V�����Z�b�g
	for (int i = 0; i < 8; i++)
	{
		Vector3 direction = m_subModels[i]->GetTransform()->GetWorldAxisFromLocal(Vector3(1, 1, -1));
		m_subModels[i]->GetTransform()->SetPosition(direction * m_movePar);
	}
}
