// ================================================================ 
// �t�@�C���� : SpiderActionAnimation.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̋󒆋@���A�j���[�V����
// ================================================================
#include"pch.h"
#include"SpiderActionAnimator.h"
#include"Base/Base.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"

//�f�t�H���g�̃N�H�[�^�j�I��
constexpr DirectX::SimpleMath::Quaternion DEFAULT_ROTATE = DirectX::SimpleMath::Quaternion(0, 1, 0, 0);
//��ɖ߂�܂ł̎���
constexpr float RESET_TIME = 0.8f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="name">�A�j���[�V������</param>
/// <param name="model">�w偃��f��</param>
SpiderActionAnimator::SpiderActionAnimator(std::string name, SpiderModels* model):Animator(name)
	,
	m_state{State::NORMAL},
	m_models{model},
	m_playerRigidbody{nullptr},
	m_rotate{DEFAULT_ROTATE},
	m_radian{0},
	m_resetTime{1},
	m_actions{},
	m_tween{nullptr}
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//����A�j���[�V�����ɂ���
	SetIsParallel(true);
	//���W�b�h�{�f�B�擾
	if (model->GetHolder())m_playerRigidbody = model->GetHolder()->GetComponent<Rigidbody>();
	//Tween����
	m_tween = model->AddComponent<Tween>(model, true);
	//�����Ȃ������ۂɌĂ΂��I�u�U�[�o�[
	auto obs = model->AddComponent<Observer<>>(model);
	obs->RegistrationSubject("PlayerThreadConect");
	obs->SetFunction([&]() {ToNormal(); });
	
	m_actions.push_back(std::make_unique<Action1>());
	m_actions.push_back(std::make_unique<Action2>());
	m_actions.push_back(std::make_unique<Action3>());
	m_actions.push_back(std::make_unique<Action4>());
	m_actions.push_back(std::make_unique<Action5>());
	m_actions.push_back(std::make_unique<Action6>());
	m_actions.push_back(std::make_unique<Action7>());
}

/// <summary>
/// �A�j���[�V�����Ăяo����
/// </summary>
void SpiderActionAnimator::Play()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//������
	m_axis = Vector3::Zero;
	m_axis = SelectAction();
	//���Ȃ��̓p�X
	if (m_axis == Vector3::Zero)return;

	//��]�ʂ�ω�
	m_radian = 0;
	m_tween->DoFloat(m_radian, 360, 1.4f).SetCompleteFunction([&]() {
		m_rotate = DEFAULT_ROTATE;
		ToNormal();
		}).SetEase(Easing::Ease::OutBack);
	//�X�e�[�g�ύX
	m_state = State::ROTATE;
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void SpiderActionAnimator::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	switch (m_state)
	{
	case SpiderActionAnimator::State::NORMAL:
		//��ɖ߂��Ă���
		m_rotate = Quaternion::Slerp(m_models->GetTransform()->GetRotate(), DEFAULT_ROTATE,m_resetTime);
		break;
	case SpiderActionAnimator::State::ROTATE:
		//���ɉ����ĉ�]
		m_rotate = DEFAULT_ROTATE;
		m_rotate *= Quaternion::CreateFromAxisAngle(m_axis, XMConvertToRadians(m_radian));
		break;
	default:
		break;
	}
	//�N�H�[�^�j�I�����X�V
	m_models->GetTransform()->SetRotate(m_rotate);
}


/// <summary>
/// ��ɖ߂�
/// </summary>
void SpiderActionAnimator::ToNormal()
{
	m_state = State::NORMAL;
	m_resetTime = 0;
	m_tween->DoFloat(m_resetTime, 1,RESET_TIME).SetCompleteFunction([&]() {
		//�A�j���[�V�������I�t��
		ActiveOff();
		});
}

/// <summary>
/// ��]�A�N�V������I��
/// </summary>
/// <returns>��]��</returns>
DirectX::SimpleMath::Vector3 SpiderActionAnimator::SelectAction()
{
	//���s�A�N�V����
	std::vector<SpiderAction*> execution;
	//���x
	DirectX::SimpleMath::Vector3 velocity = m_playerRigidbody->GetVelocity();
	//����
	DirectX::SimpleMath::Vector3 direction = m_models->GetTransform()->GetWorldAxisFromLocal(DirectX::SimpleMath::Vector3::UnitZ);
	//�A�N�V�����I��
	for (auto& action : m_actions)
	{
		//�A�N�V���������ɍ������𔻒f
		if (action->RotationConditions(direction,velocity))
		{
			//�X���b�g�擾
			int slot = action->m_slot;
			//�X���b�g�̃T�C�Y�Ɋg��
			if (execution.size() <= slot)
			{
				execution.resize(slot + 1, nullptr);
			}
			//�X���b�g�Ɋi�[
			if (execution[slot] == nullptr)
			{
				execution[slot] = action.get();
			}
			else//�D��x�m�F
			{
				if(execution[slot]->m_priority < action->m_slot)execution[slot] = action.get();
			}
		}
	}
	
	//���s�A�N�V�������Ȃ��ꍇ��0�ŕԂ�
	if (execution.empty())return DirectX::SimpleMath::Vector3::Zero;

	//�Ԃ���
	DirectX::SimpleMath::Vector3 axis;

	//�����v�Z
	for (auto& action : execution)
	{
		if (action == nullptr)continue;
		axis += action->m_axis;
	}

	axis.Normalize();

	return axis;
}

