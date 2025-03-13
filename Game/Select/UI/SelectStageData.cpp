// ================================================================ 
// ファイル名 : SelectStageData.cpp
// 作成者 : 景山碧天
// 説明 :  ステージ番号を表示
// ================================================================
#include"pch.h"
#include"SelectStageData.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
SelectStageData::SelectStageData(Canvas* canvas):UserInterface(canvas)
	,
	m_numberSize{ 70,100 },
	m_stageNumber{}
{
	using namespace DirectX::SimpleMath;
	SetColor(Vector4(0, 0, 0, 0));

	//ハイフン作成
	UserInterface* hyphen = GetScene()->AddObject<UserInterface>(canvas,"Hyphen",1);
	hyphen->SetPosition(Vector2(960, 175));
	hyphen->SetOffset(Vector2(0.5f, 1));

	//ステージ番号作成
	for (int i = 0; i < 2; i++)
	{
		m_stageNumber[i] = GetScene()->AddObject<UserInterface>(canvas,"Numbers",1);
		m_stageNumber[i]->SetSize(m_numberSize);
		m_stageNumber[i]->SetOffset(Vector2(0.5f, 1));
	}
	//位置調整
	m_stageNumber[0]->SetPosition(Vector2(870, 175));
	m_stageNumber[1]->SetPosition(Vector2(1050, 175));
	//ステージ番号のクリップ
	std::pair<int, int> stageNum = GameManager::GetInstance()->GetStageNum();
	m_stageNumber[0]->SetClipRange(Vector4(stageNum.first / 10.0f, 0, 0.1f, 1.0f));
	m_stageNumber[1]->SetClipRange(Vector4(stageNum.second / 10.0f, 0, 0.1f, 1.0f));

	m_tween = AddComponent<Tween>(this,true);

	//データ更新オブザーバー作成
	m_observer = AddComponent<Observer<>>(this);
	m_observer->SetFunction([&]() {DataUpdate(); });
	m_observer->RegistrationSubject("LeftArrow");
	m_observer->RegistrationSubject("RightArrow");
}

/// <summary>
/// 位置更新
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void SelectStageData::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	m_stageNumber[0]->SetSize(m_numberSize);
	m_stageNumber[1]->SetSize(m_numberSize);
}

/// <summary>
/// データ更新
/// </summary>
void SelectStageData::DataUpdate()
{
	using namespace DirectX::SimpleMath;

	//表示を消す
	m_tween->DoVector2(m_numberSize, Vector2(70, 0), 0.1f).SetCompleteFunction([&]() {
		//ステージ番号のクリップ
		std::pair<int, int> stageNum = GameManager::GetInstance()->GetStageNum();
		m_stageNumber[0]->SetClipRange(Vector4(stageNum.first / 10.0f, 0, 0.1f, 1.0f));
		m_stageNumber[1]->SetClipRange(Vector4(stageNum.second / 10.0f, 0, 0.1f, 1.0f));
		//表示させる
		m_tween->DoVector2(m_numberSize, Vector2(70, 100), 0.1f);
		});
}
