// ================================================================ 
// ファイル名 : SpiderActionAnimation.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛の空中機動アニメーション
// ================================================================
#include"pch.h"
#include"SpiderActionAnimator.h"
#include"Base/Base.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"

//デフォルトのクォータニオン
constexpr DirectX::SimpleMath::Quaternion DEFAULT_ROTATE = DirectX::SimpleMath::Quaternion(0, 1, 0, 0);
//基準に戻るまでの時間
constexpr float RESET_TIME = 0.8f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="name">アニメーション名</param>
/// <param name="model">蜘蛛モデル</param>
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

	//並列アニメーションにする
	SetIsParallel(true);
	//リジッドボディ取得
	if (model->GetHolder())m_playerRigidbody = model->GetHolder()->GetComponent<Rigidbody>();
	//Tween生成
	m_tween = model->AddComponent<Tween>(model, true);
	//糸がつながった際に呼ばれるオブザーバー
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
/// アニメーション呼び出し時
/// </summary>
void SpiderActionAnimator::Play()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//軸検索
	m_axis = Vector3::Zero;
	m_axis = SelectAction();
	//軸なしはパス
	if (m_axis == Vector3::Zero)return;

	//回転量を変化
	m_radian = 0;
	m_tween->DoFloat(m_radian, 360, 1.4f).SetCompleteFunction([&]() {
		m_rotate = DEFAULT_ROTATE;
		ToNormal();
		}).SetEase(Easing::Ease::OutBack);
	//ステート変更
	m_state = State::ROTATE;
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void SpiderActionAnimator::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	switch (m_state)
	{
	case SpiderActionAnimator::State::NORMAL:
		//基準に戻していく
		m_rotate = Quaternion::Slerp(m_models->GetTransform()->GetRotate(), DEFAULT_ROTATE,m_resetTime);
		break;
	case SpiderActionAnimator::State::ROTATE:
		//軸に沿って回転
		m_rotate = DEFAULT_ROTATE;
		m_rotate *= Quaternion::CreateFromAxisAngle(m_axis, XMConvertToRadians(m_radian));
		break;
	default:
		break;
	}
	//クォータニオンを更新
	m_models->GetTransform()->SetRotate(m_rotate);
}


/// <summary>
/// 基準に戻す
/// </summary>
void SpiderActionAnimator::ToNormal()
{
	m_state = State::NORMAL;
	m_resetTime = 0;
	m_tween->DoFloat(m_resetTime, 1,RESET_TIME).SetCompleteFunction([&]() {
		//アニメーションをオフに
		ActiveOff();
		});
}

/// <summary>
/// 回転アクションを選択
/// </summary>
/// <returns>回転軸</returns>
DirectX::SimpleMath::Vector3 SpiderActionAnimator::SelectAction()
{
	//実行アクション
	std::vector<SpiderAction*> execution;
	//速度
	DirectX::SimpleMath::Vector3 velocity = m_playerRigidbody->GetVelocity();
	//向き
	DirectX::SimpleMath::Vector3 direction = m_models->GetTransform()->GetWorldAxisFromLocal(DirectX::SimpleMath::Vector3::UnitZ);
	//アクション選択
	for (auto& action : m_actions)
	{
		//アクション条件に合うかを判断
		if (action->RotationConditions(direction,velocity))
		{
			//スロット取得
			int slot = action->m_slot;
			//スロットのサイズに拡大
			if (execution.size() <= slot)
			{
				execution.resize(slot + 1, nullptr);
			}
			//スロットに格納
			if (execution[slot] == nullptr)
			{
				execution[slot] = action.get();
			}
			else//優先度確認
			{
				if(execution[slot]->m_priority < action->m_slot)execution[slot] = action.get();
			}
		}
	}
	
	//実行アクションがない場合は0で返す
	if (execution.empty())return DirectX::SimpleMath::Vector3::Zero;

	//返す軸
	DirectX::SimpleMath::Vector3 axis;

	//軸を計算
	for (auto& action : execution)
	{
		if (action == nullptr)continue;
		axis += action->m_axis;
	}

	axis.Normalize();

	return axis;
}

