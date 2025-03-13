// ================================================================ 
// ファイル名 : StateMachine.h
// 作成者 : 景山碧天
// 説明 :  ステートマシン
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
	//稼働ステート
	std::pair<EnumType, StateType*> m_currentState;
	//次のステート
	EnumType m_nextState;
	//登録ステート
	std::unordered_map<EnumType, std::unique_ptr<StateType>> m_states;
private:
	//登録されているか検索
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
	/// ステートの追加
	/// </summary>
	/// <param name="state">追加ステート</param>
	/// <param name="type">登録Enum</param>
	void AddState(std::unique_ptr<StateType> state,EnumType type)
	{
		if (IsRegister(type))return;
		//追加
		m_states.insert({ type,std::move(state) });
		DerivationAddState(m_states[type].get(), type);
	}

	/// <summary>
	/// 派生先でのステートの保存に使用
	/// </summary>
	/// <param name="state"></param>
	/// <param name="type"></param>
	virtual void DerivationAddState(StateType* state, EnumType type)
	{
		UNREFERENCED_PARAMETER(state);
		UNREFERENCED_PARAMETER(type);
	}

	//アップデート
	void Update(float deltatime)
	{
		if (m_currentState.second == nullptr)return;
		m_currentState.second->Update(deltatime);
		ChangeState();
	}

	//初期ステートを設定
	void SetStart(EnumType type)
	{
		if (!IsRegister(type))return;
		//稼働ステートにセット
		m_currentState.first = type;
		m_currentState.second = m_states[type].get();
		m_nextState = type;
		m_currentState.second->PreUpdate();
		DerivationChangeState(type);
	}

	//ステートを変更
	void ChangeState(EnumType type)
	{
		if (m_currentState.second == nullptr)return;
		if (!IsRegister(type))return;
		//現在と同じならパス
		m_nextState = type;
		
	}

	//現在のステートを取得
	EnumType GetCurrensState()
	{
		if (m_currentState.second == nullptr)
		{
			return EnumType();
		}
		return m_currentState.first;
	}

	/// <summary>
	/// 派生先にステートの変更を伝える
	/// </summary>
	virtual void DerivationChangeState(EnumType type)
	{
		UNREFERENCED_PARAMETER(type);
	}

	/// <summary>
	/// ステートの変更
	/// </summary>
	void ChangeState()
	{
		//現在のステートと同じなら返す
		if (m_currentState.first == m_nextState)return;

		//現在のステートの終了処理
		m_currentState.second->PostUpdate();
		//ステートを変更
		m_currentState.first = m_nextState;
		m_currentState.second = m_states[m_nextState].get();
		//開始処理
		m_currentState.second->PreUpdate();
		DerivationChangeState(m_nextState);
	}
};


