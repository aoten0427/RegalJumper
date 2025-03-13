// ================================================================ 
// ファイル名 : ResultBG.cpp
// 作成者 : 景山碧天
// 説明 :  リザルト背景
// ================================================================

#include"pch.h"
#include"ResultBG.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/Tween/DoTween.h"
#include"Base/Sound/Sound.h"

//全ての資格が出現するまでの時間
constexpr float APPEARANCE_TIME = 3.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
ResultBG::ResultBG(Canvas* canvas):UserInterface(canvas,"ResultBG")
	,
	m_quads{},
	m_quadsColor{},
	m_openTime{},
	m_timer{ 0 },
	m_flag{ false }
{
	//位置、大きさを設定
	SetPosition(DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y));
	SetSize(DirectX::SimpleMath::Vector2(Screen::WIDTH, Screen::HEIGHT));
	//データ読み込み
	LoadData();

	AddComponent<Sound>(this, Sound::SoundType::SE, "Result", true);
}

/// <summary>
/// アップデート 四角の色を調整
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void ResultBG::ObjectUpdate(float deltatime)
{
	using namespace DirectX::SimpleMath;
	//視覚の出現
	if (m_timer < APPEARANCE_TIME)
	{
		m_timer += deltatime;
		for (int i = 0; i < m_openTime.size(); i++)
		{
			//出現時間に合わせて透明度変更
			if (m_openTime[i] < m_timer)
			{
				float alpha = std::min((m_timer - m_openTime[i]) * 1.6f, 1.0f);

				m_quadsColor[i].w = alpha;
			}
		}
	}
	//透明度変更のループを起動
	if (m_timer > 3.0f && !m_flag)
	{
		m_flag = true;
		LoopSet();
	}
	//色設定
	for (int i = 0; i < m_quads.size(); i++)
	{
		m_quads[i]->SetColor(m_quadsColor[i]);
	}
}

/// <summary>
/// データ読み込み
/// </summary>
void ResultBG::LoadData()
{
	//JSONファイル選択
	std::string filename = "Resources/JSON/ResultData/ResultData.json";
	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//モデル読み込み
		size_t num = m_json["Quads"].size();

		for (int i = 0; i < num; i++)
		{
			using namespace DirectX::SimpleMath;
			//生成
			m_quads.push_back(GetScene()->AddObject<UserInterface>(GetCanvas(), "ResultQuad",1));
			//透明にセット
			m_quads.back()->SetColor(Vector4(1, 1, 1, 0));
			//位置とサイズ調整
			Vector2 position{ m_json["Quads"][i]["x"],m_json["Quads"][i]["y"] };
			Vector2 size{ m_json["Quads"][i]["width"],m_json["Quads"][i]["height"] };
			m_quads.back()->SetPosition(position);
			m_quads.back()->SetSize(size);
			//出現時間を記録
			m_openTime.push_back(m_json["Quads"][i]["openTime"]);
			m_quadsColor.push_back(Vector4(1, 1, 1, 0));
		}
	}

}

/// <summary>
/// ループをセット
/// </summary>
void ResultBG::LoopSet()
{
	for (int i = 0; i < m_quadsColor.size(); i++)
	{
		AddComponent<Tween>(this, true)->DoVector4(m_quadsColor[i],DirectX::SimpleMath::Vector4(1, 1, 1, 0.3f), 2.0f).
			SetLoop(-1).SetDelay(m_openTime[i]);
	}
}
