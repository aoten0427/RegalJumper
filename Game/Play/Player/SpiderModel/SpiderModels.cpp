// ================================================================ 
// ファイル名 : SpiderModel.cpp
// 作成者 : 景山碧天
// 説明 :  蜘蛛のモデルを管理
// ================================================================
#include"pch.h"
#include"SpiderModels.h"
#include"Base/Base.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelStateMachine.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="holder">所属オブジェクト</param>
SpiderModels::SpiderModels(Scene* scene, Object* holder):Object(scene)
	,
	m_holder{holder},
	m_parts{},
	m_head{nullptr},
	m_body{nullptr},
	m_legs{},
	m_machine{nullptr},
	m_lightdata{}
{	
	//ホルダーを親として登録
	if (holder)GetTransform()->SetParent(holder->GetTransform());
	//部品データ読み込み
	LoadData();
	//描画に使うモデルクラス作成
	Model3D* model = AddComponent<Model3D>(this);
	model->SetRender(std::bind(&SpiderModels::Render, this, std::placeholders::_1));
	model->SetIsAfterDraw(true);
	//ステートマシン
	m_machine = std::make_unique<SpiderModelStateMachine>(this);
	//
	GetTransform()->Translate(DirectX::SimpleMath::Vector3(0, -0.1f, 0.8f));
	//移動方向の問題で回転させる
	GetTransform()->TransRotate(DirectX::SimpleMath::Vector3::UnitY, 180.0f);
	//アニメーション生成
	m_animation = std::make_unique<SpiderAnimatorCenter>(this);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void SpiderModels::ObjectUpdate(float deltatime)
{
	//ステートマシンアップデート
	m_machine->Update(deltatime);
	//アニメーター更新
	m_animation->Update(deltatime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void SpiderModels::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;
	//ライト情報を設定
	m_lightdata.LightPosition = Vector4(-200, 500, 50, 0);
	m_lightdata.CameraPosition = Vector4(camera.GetEyePosition().x, camera.GetEyePosition().y, camera.GetEyePosition().z, 0);
	m_lightdata.Ambient = 0.4f;
	m_lightdata.Diffuse = 0.4f;
	m_lightdata.Specular = 0.4f;
	m_lightdata.Roughness = 0.5f;
	m_lightdata.DiffuseColor = Vector4(1, 1, 1, 1);
	m_lightdata.SpecularColor = Vector4(0.5, 0.5, 0.5, 1);
	m_lightdata.complex_refractive_index = 5.0f;
	//ステートマシンで描画
	m_machine->Render(camera);
}

/// <summary>
/// 状態変更
/// </summary>
/// <param name="state">変化ステート</param>
void SpiderModels::ChangeState(SpiderModelState::RenderType state)
{
	m_machine->ChangeState(state);
}

/// <summary>
/// データ読み込み
/// </summary>
void SpiderModels::LoadData()
{
	using namespace DirectX::SimpleMath;

	//JSONファイル選択
	std::string filename = "Resources/JSON/PlayerData/ModelPosition.json";

	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//モデル読み込み
		size_t num = m_json["Parts"].size();
		for (int i = 0; i < num; i++)
		{
			SpiderModelParts* product = nullptr;

			std::string name = m_json["Parts"][i]["Name"];

			Vector3 position = Vector3(m_json["Parts"][i]["Position"]["x"],
				m_json["Parts"][i]["Position"]["y"],
				m_json["Parts"][i]["Position"]["z"]);
			Vector3 scale = Vector3(m_json["Parts"][i]["Scale"]["x"],
				m_json["Parts"][i]["Scale"]["y"],
				m_json["Parts"][i]["Scale"]["z"]);
			Quaternion rotate = Quaternion(m_json["Parts"][i]["Rotate"]["x"],
				m_json["Parts"][i]["Rotate"]["y"],
				m_json["Parts"][i]["Rotate"]["z"],
				m_json["Parts"][i]["Rotate"]["w"]);
			//胴体生成
			if (m_json["Parts"][i]["Type"] == "Body")
			{
				m_body = GetScene()->AddObject<SpiderModelParts>(GetScene(), name, "SpiderBody", "SpiderBody");
				product = m_body;
			}
			//顔生成
			if (m_json["Parts"][i]["Type"] == "Head")
			{
				m_head = GetScene()->AddObject<SpiderModelParts>(GetScene(), name, "SpiderHead", "SpiderHead");
				product = m_head;
			}
			//足生成
			if (m_json["Parts"][i]["Type"] == "Leg")
			{
				m_legs.push_back(GetScene()->AddObject<SpiderModelParts>(GetScene(), name, m_json["Parts"][i]["Model"], m_json["Parts"][i]["Texture"]));
				product = m_legs.back();
			}

			//情報をセット
			product->GetTransform()->Translate(position);
			product->GetTransform()->SetScale(scale);
			product->GetComponent<Model3D>()->SetRotate(rotate);
			//product->SetRenderData(&m_renderType, &m_timer, &m_alpha);
			product->GetTransform()->SetParent(GetTransform());
			m_parts.push_back(product);
		}
	}
}
