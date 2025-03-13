// ================================================================ 
// ファイル名 : TargetBox.cpp
// 作成者 : 景山碧天
// 説明 :  移動に使うターゲットオブジェクト
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
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
TargetBox::TargetBox(Scene* scene):Object(scene)
	,
	m_state{State::CLOSE},
	m_movePar{0}
{
	using namespace DirectX::SimpleMath;

	//メインモデル作成
	m_mainModel = AddComponent<Model3D>(this, "TargetMain");
	m_mainModel->SetScale(Vector3(INITAL_EXTENS, INITAL_EXTENS, INITAL_EXTENS));
	//サブ作成
	for (int i = 0; i < 8; i++)
	{
		auto object = scene->AddObject<Object>(scene);
		//親子設定
		object->GetTransform()->SetParent(GetTransform());
		//モデル作成
		auto model = object->AddComponent<Model3D>(object,"TargetSub");
		//スケール、回転設定
		model->SetScale(Vector3(INITAL_EXTENS, INITAL_EXTENS, INITAL_EXTENS));
		object->GetTransform()->TransRotate(Vector3::UnitY, i / 2 * 90.0f);
		object->GetTransform()->TransRotate(Vector3::UnitZ, i % 2 * 180.0f);
		m_subModels[i] = object;

	}
	//ターゲット作成
	m_target = scene->AddObject<Target>(scene,this,Target::TargetType::Move);
	//判定作成
	AddComponent<Sphere>(this, CollisionType::FIXED, nullptr, false, INITAL_EXTENS);
	//Tween作成
	m_tween = AddComponent<Tween>(this, true);
	//ターゲットマーク作成
	m_targetMark = scene->AddObject<TargetMark>(scene, this);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void TargetBox::ObjectUpdate(float deltatime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(deltatime);

	switch (m_state)
	{
	case TargetBox::State::CLOSE:
		//ターゲットされていたら開く
		if (m_target->GetIsTarget())Open();
		break;
	case TargetBox::State::OPEN:
		//ターゲットされていなければ閉じる
		if (!m_target->GetIsTarget())Close();
		break;
	case TargetBox::State::MOVE:
		Move();
		break;
	default:
		break;
	}
}

//開く
void TargetBox::Open()
{
	//開く処理実行
	m_state = State::MOVE;
	m_tween->DoFloat(m_movePar, 1, 0.3f).SetEase(Easing::Ease::OutCubic).SetCompleteFunction([&]() {
		m_state = State::OPEN;
		});
	m_targetMark->Open();
}

//とじる
void TargetBox::Close()
{
	//閉じる処理実行
	m_state = State::MOVE;
	m_tween->DoFloat(m_movePar, 0, 0.3f).SetEase(Easing::Ease::OutCubic).SetCompleteFunction([&]() {
		m_state = State::CLOSE;
		});
	m_targetMark->Close();
}

/// <summary>
/// 開閉処理
/// </summary>
void TargetBox::Move()
{
	using namespace DirectX::SimpleMath;
	//ポジションセット
	for (int i = 0; i < 8; i++)
	{
		Vector3 direction = m_subModels[i]->GetTransform()->GetWorldAxisFromLocal(Vector3(1, 1, -1));
		m_subModels[i]->GetTransform()->SetPosition(direction * m_movePar);
	}
}
