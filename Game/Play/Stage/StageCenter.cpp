// ================================================================ 
// ファイル名 : StageCenter
// 作成者 : 景山碧天
// 説明 :  プレイ画面に配置するオブジェクトを管理
// ================================================================
#include"pch.h"
#include"StageCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/Component/Transform/Transform.h"
#include"Game/GameManager.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/Play/Stage/Skydome.h"
#include"Game/Play/Stage/Box.h"
#include"Game/Play/Stage/TargetBox.h"
#include"Game/Play/Stage/Goal.h"
#include"Game/Play/Stage/Help.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
StageCenter::StageCenter(Scene* scene):Object(scene)
{
	scene->AddObject<Skydome>(scene);
	LoadData();
}

/// <summary>
/// データ読み込み
/// </summary>
void StageCenter::LoadData()
{
	using namespace DirectX::SimpleMath;

	std::string stagename = GameManager::GetInstance()->GetStageName();

	//JSONファイル選択
	std::string filename = "Resources/JSON/StageData/" + stagename + ".json";
	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//ステージデータ読み込み
		size_t num = m_json["StageObject"].size();

		for (int i = 0; i < num; i++)
		{
			//座標取得
			Vector3 position{ m_json["StageObject"][i]["position"]["x"],
			m_json["StageObject"][i]["position"]["y"] ,
			m_json["StageObject"][i]["position"]["z"] };
			//スケール取得
			Vector3 scale{ m_json["StageObject"][i]["scale"]["x"],
			m_json["StageObject"][i]["scale"]["y"] ,
			m_json["StageObject"][i]["scale"]["z"] };

			//box生成
			if (m_json["StageObject"][i]["TYPE"] == "Box")
			{
				auto box = GetScene()->AddObject<Box>(GetScene());
				box->GetTransform()->SetPosition(position);
				box->GetTransform()->SetScale(scale);
			}
			//ターゲットボックス生成
			else if (m_json["StageObject"][i]["TYPE"] == "Target")
			{
				auto target = GetScene()->AddObject<TargetBox>(GetScene());
				target->GetTransform()->SetPosition(position);
			}
			else if (m_json["StageObject"][i]["TYPE"] == "Goal")
			{
				auto goal = GetScene()->AddObject<Goal>(GetScene());
				goal->GetTransform()->SetPosition(position);
			}
			else if (m_json["StageObject"][i]["TYPE"] == "Help")
			{
				int infomationNum = m_json["StageObject"][i]["InfomationNum"];
				bool begin = m_json["StageObject"][i]["Begin"];
				auto help = GetScene()->AddObject<Help>(GetScene(), infomationNum,begin);
				help->GetTransform()->Translate(position);
			}
		}

		ifs.close();
	}
}
