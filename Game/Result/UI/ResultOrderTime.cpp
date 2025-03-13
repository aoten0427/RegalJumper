// ================================================================ 
// ファイル名 : ResultOrderTime.cpp
// 作成者 : 景山碧天
// 説明 :  目標時間の表示
// ================================================================
#include"pch.h"
#include"ResultOrderTime.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/GameManager.h"
#include"Game/Play/UI/Time.h"

constexpr int SCORE_START_Y = 570;//スコア表示位置
constexpr int RANGE_Y = 50;//スコア表示幅

constexpr int SCORE_SIZE = 36;//スコアサイズ

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
ResultOrderTIme::ResultOrderTIme(Canvas* canvas):UserInterface(canvas)
	,
	m_score{},
	m_orderTimes{},
	m_tween{nullptr},
	m_alpha{0}
{
	using namespace DirectX::SimpleMath;
	//本体はオフに
	SetActive(false);
	//スコア画像の分割割合
	const float ClipingX = 0.25f;
	//各スコア生成
	for (int i = 0; i < 3; i++)
	{
		m_score[i] = GetScene()->AddObject<UserInterface>(canvas,"Score",3);
		m_score[i]->SetClipRange(Vector4(i * ClipingX, 0, ClipingX, 1));
		m_score[i]->SetPosition(Vector2(1070, (float)(SCORE_START_Y + RANGE_Y * i)));
		m_score[i]->SetSize(Vector2(SCORE_SIZE, SCORE_SIZE));
		m_score[i]->SetColor(Vector4(1, 1, 1, m_alpha));
	}
	//各スコアタイム生成
	for (int i = 0; i < 3; i++)
	{
		m_orderTimes[i] = GetScene()->AddObject<Time>(canvas);
		m_orderTimes[i]->SetStartX(1100.0f);
		m_orderTimes[i]->SetPositionY((float)(SCORE_START_Y + i * RANGE_Y));
		m_orderTimes[i]->SetSize(Vector2(24, 36));
		m_orderTimes[i]->SetTimeColor(Vector4(1, 1, 1, m_alpha));
	}
	//クリアデータ読み込み
	LoadData();
	//Tween生成
	m_tween = AddComponent<Tween>(this,true);
	m_tween->DoFloat(m_alpha, 1, 0.3f).SetDelay(2.0f);

	//オブザーバ生成 スキップ処理登録
	Observer<>* skip = AddComponent<Observer<>>(this);
	skip->RegistrationSubject("ResultSkip");
	skip->SetFunction([&]() {Skip(); });

	m_mouse = GetScene()->AddObject<UserInterface>(canvas, "Mouse_left", 3);
	m_mouse->SetPosition(Vector2(830, 680));
	m_mouse->SetSize(Vector2(200, 50));
}

/// <summary>
/// アップデート　アルファ値変化
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void ResultOrderTIme::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	using namespace DirectX::SimpleMath;
	for (int i = 0; i < 3; i++)
	{
		m_score[i]->SetColor(Vector4(1, 1, 1, m_alpha));
		m_orderTimes[i]->SetTimeColor(Vector4(1, 1, 1, m_alpha));
	}
	m_mouse->SetColor(Vector4(1, 1, 1, m_alpha));
}

/// <summary>
/// データ読み込み
/// </summary>
void ResultOrderTIme::LoadData()
{
	//ステージ名
	std::string stageName = GameManager::GetInstance()->GetStageName();
	//JSONファイル選択
	std::string filename = "Resources/JSON/ClearData/" + stageName + ".json";

	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//各スコアのタイムを読み込み
		m_orderTimes[0]->SetCount(m_json["OrderTime"]["S"]);
		m_orderTimes[1]->SetCount(m_json["OrderTime"]["A"]);
		m_orderTimes[2]->SetCount(m_json["OrderTime"]["B"]);

		ifs.close();
	}
}

/// <summary>
/// スキップ
/// </summary>
void ResultOrderTIme::Skip()
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	m_tween->Kill();
}
