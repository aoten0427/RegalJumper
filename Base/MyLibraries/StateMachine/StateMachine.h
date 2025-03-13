// ================================================================ 
// �t�@�C���� : StateMachine.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�g�}�V��
// ================================================================

#pragma once
#include"Base/Component/Component.h"
#include"Base/MyLibraries/StateMachine/IState.h"


template<typename StateType, typename EnumType,
	std::enable_if_t<
	std::is_base_of_v<IState,StateType>,std::nullptr_t
	> = nullptr>
class StateMachine
{
private:
	//�ғ��X�e�[�g
	std::pair<EnumType, StateType*> m_currentState;
	//���̃X�e�[�g
	EnumType m_nextState;
	//�o�^�X�e�[�g
	std::unordered_map<EnumType, std::unique_ptr<StateType>> m_states;
private:
	//�o�^����Ă��邩����
	bool IsRegister(EnumType type)
	{
		auto itr = m_states.find(type);
		if (itr != m_states.end())return true;
		return false;
	}
public:
	StateMachine()
		:
		m_currentState{},
		m_nextState{},
		m_states{}
	{
		m_currentState.second = nullptr;
	}

	/// <summary>
	/// �X�e�[�g�̒ǉ�
	/// </summary>
	/// <param name="state">�ǉ��X�e�[�g</param>
	/// <param name="type">�o�^Enum</param>
	void AddState(std::unique_ptr<StateType> state,EnumType type)
	{
		if (IsRegister(type))return;
		//�ǉ�
		m_states.insert({ type,std::move(state) });
		DerivationAddState(m_states[type].get(), type);
	}

	/// <summary>
	/// �h����ł̃X�e�[�g�̕ۑ��Ɏg�p
	/// </summary>
	/// <param name="state"></param>
	/// <param name="type"></param>
	virtual void DerivationAddState(StateType* state, EnumType type)
	{
		UNREFERENCED_PARAMETER(state);
		UNREFERENCED_PARAMETER(type);
	}

	//�A�b�v�f�[�g
	void Update(float deltatime)
	{
		if (m_currentState.second == nullptr)return;
		m_currentState.second->Update(deltatime);
		ChangeState();
	}

	//�����X�e�[�g��ݒ�
	void SetStart(EnumType type)
	{
		if (!IsRegister(type))return;
		//�ғ��X�e�[�g�ɃZ�b�g
		m_currentState.first = type;
		m_currentState.second = m_states[type].get();
		m_nextState = type;
		m_currentState.second->PreUpdate();
		DerivationChangeState(type);
	}

	//�X�e�[�g��ύX
	void ChangeState(EnumType type)
	{
		if (m_currentState.second == nullptr)return;
		if (!IsRegister(type))return;
		//���݂Ɠ����Ȃ�p�X
		m_nextState = type;
		
	}

	//���݂̃X�e�[�g���擾
	EnumType GetCurrensState()
	{
		if (m_currentState.second == nullptr)
		{
			return EnumType();
		}
		return m_currentState.first;
	}

	/// <summary>
	/// �h����ɃX�e�[�g�̕ύX��`����
	/// </summary>
	virtual void DerivationChangeState(EnumType type)
	{
		UNREFERENCED_PARAMETER(type);
	}

	/// <summary>
	/// �X�e�[�g�̕ύX
	/// </summary>
	void ChangeState()
	{
		//���݂̃X�e�[�g�Ɠ����Ȃ�Ԃ�
		if (m_currentState.first == m_nextState)return;

		//���݂̃X�e�[�g�̏I������
		m_currentState.second->PostUpdate();
		//�X�e�[�g��ύX
		m_currentState.first = m_nextState;
		m_currentState.second = m_states[m_nextState].get();
		//�J�n����
		m_currentState.second->PreUpdate();
		DerivationChangeState(m_nextState);
	}
};


