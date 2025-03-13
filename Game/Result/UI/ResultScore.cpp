// ================================================================ 
// ファイル名 : ResultScore.cpp
// 作成者 : 景山碧天
// 説明 :  リザルトのスコア表示
// ================================================================
#include"pch.h"
#include"ResultScore.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/DoTween.h"
#include"Base/Event/Observer.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/GameManager.h"

constexpr int MARK_CLIPPING = 1200;//スコアマークの1つ分の範囲
constexpr int SCORE_CLIPPING = 500;//スコアの１つ分の範囲

constexpr float DELAY_TIME = 2.3f;//スコア表示のための遅延時間

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
ResultScore::ResultScore(Canvas* canvas):UserInterface(canvas)
	,
	m_mark{nullptr},
	m_markSize{ 0,0 },
	m_markTween{nullptr},
	m_score{nullptr},
	m_scoreSize{ 1600,1600 },
	m_scoreTween{nullptr},
	m_timer{ 0 }
{
	using namespace DirectX::SimpleMath;
	//スコア枠生成
	m_mark = GetScene()->AddObject<UserInterface>(canvas,"ScoreMark",3);
	m_mark->SetPosition(Vector2(830, 380));
	m_mark->SetSize(m_markSize);
	m_markTween = AddComponent<Tween>(this,true);
	m_markTween->DoVector2(m_markSize,Vector2(600,600), 0.2f).SetEase(Easing::Ease::OutQuad).SetDelay(1.8f);
	//スコア生成
	m_score = GetScene()->AddObject<UserInterface>(canvas,"Score",3);
	m_score->SetPosition(Vector2(830, 380));
	m_score->SetSize(m_scoreSize);
	m_score->SetActive(false);
	m_scoreTween = AddComponent<Tween>(this,true);
	m_scoreTween->DoVector2(m_scoreSize, Vector2(260, 260), 0.8f).SetEase(Easing::Ease::OutBounce).SetDelay(DELAY_TIME).SetCompleteFunction([&]() {
		GetScene()->ChangeState(Scene::State::END);
		});

	//データ読み込み
	LoadJSON();
	//データ書き込み
	WriteJSON();

	//オブザーバ生成 スキップ処理登録
	Observer<>* skip = AddComponent<Observer<>>(this);
	skip->RegistrationSubject("ResultSkip");
	skip->SetFunction([&]() {Skip(); });
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void ResultScore::ObjectUpdate(float deltatime)
{
	m_timer += deltatime;
	m_mark->SetSize(m_markSize);
	if (m_timer > DELAY_TIME)
	{
		m_score->SetActive(true);
		m_score->SetSize(m_scoreSize);
	}
}

/// <summary>
/// データ読み込み
/// </summary>
void ResultScore::LoadJSON()
{
	using namespace DirectX::SimpleMath;

	//ステージ名
	std::string stageName = GameManager::GetInstance()->GetStageName();
	//JSONファイル選択
	std::string filename = "Resources/JSON/ClearData/" + stageName + ".json";

	const float ClipingX = 0.25f;
	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		float clearTime = GameManager::GetInstance()->GetResultTime();

		if (clearTime <= m_json["OrderTime"]["S"])
		{
			m_mark->SetClipRange(Vector4(0, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(0, 0, ClipingX, 1));
		}
		else if (clearTime <= m_json["OrderTime"]["A"])
		{
			m_mark->SetClipRange(Vector4(ClipingX, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(ClipingX, 0, ClipingX, 1));
		}
		else if (clearTime <= m_json["OrderTime"]["B"])
		{
			m_mark->SetClipRange(Vector4(ClipingX * 2, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(ClipingX * 2, 0, ClipingX, 1));
		}
		else
		{
			m_mark->SetClipRange(Vector4(ClipingX * 3, 0, ClipingX, 1));
			m_score->SetClipRange(Vector4(ClipingX * 3, 0, ClipingX, 1));
		}

		ifs.close();
	}

}

/// <summary>
/// データ書き込み
/// </summary>
void ResultScore::WriteJSON()
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

		float clearTime = GameManager::GetInstance()->GetResultTime();
		//今回のクリアタイムとベストタイムを比較
		if (m_json["BestTime"] >= clearTime)
		{
			//今回のほうが短ければ上書き
			m_json["BestTime"] = clearTime;
			std::ofstream file(filename.c_str());
			if (file.good())
			{
				file << m_json;
				file.close();
			}
		}
	}
}

/// <summary>
/// スキップ
/// </summary>
void ResultScore::Skip()
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	m_markTween->Kill();
	m_scoreTween->Kill();
	m_timer = DELAY_TIME;
}
