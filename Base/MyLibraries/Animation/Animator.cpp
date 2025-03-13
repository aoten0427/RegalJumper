// ================================================================ 
// ファイル名 : Animator.cpp
// 作成者 : 景山碧天
// 説明 :  複数のアニメーションをまとめたもの
// ================================================================
#include"pch.h"
#include"Animator.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/MyLibraries/Animation/AnimatorCenter.h"

/// <summary>
/// コンストラクタ
/// </summary>
Animator::Animator(std::string name,std::string filename)
	:
	m_name{name},
	m_filename{filename},
	m_animations{},
	m_animatorCenter{nullptr},
	m_isParallel{false}
{

}

/// <summary>
/// 開始処理
/// </summary>
void Animator::Play()
{
	for (auto& animation : m_animations)
	{
		animation.second->Play();
	}
}

/// <summary>
/// アップデート
/// </summary>
void Animator::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	for (auto& animation : m_animations)
	{
		animation.second->AnimationUpdate();
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Animator::End()
{
	for (auto& animation : m_animations)
	{
		animation.second->End();
	}
}

/// <summary>
/// アクティブをオフにする
/// </summary>
void Animator::ActiveOff()
{
	if (m_animatorCenter)m_animatorCenter->SetActiveAnimator(m_name,false);
}

/// <summary>
/// アニメーション追加
/// </summary>
/// <param name="name">追加アニメーション名</param>
/// <param name="object">変化するオブジェクト</param>
void Animator::AddAnimation(std::string name, Object* object)
{
	//アニメーション作成
	m_animations.insert({ name,std::make_unique<Animation>(object) });
}

/// <summary>
/// ファイルのロード
/// </summary>
/// <param name="fileName">読み込みファイル名</param>
void Animator::LoadData()
{
	if (m_filename == Config::NONE_FILE)return;
	//読み込み
	std::ifstream ifs(m_filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;
		//名前取得
		m_name = m_json["Name"];

		for (auto itr = m_json["Data"].begin(); itr != m_json["Data"].end(); itr++)
		{
			//アニメーション検索
			auto animation = m_animations.find(itr.key());
			if (animation == m_animations.end())continue;

			//ポジションアニメーション追加
			size_t num = itr.value()["Position"].size();
			for (size_t i = 0; i < num; i++)
			{
				auto& PosData = itr.value()["Position"][i];
				//変更位置
				DirectX::SimpleMath::Vector3 pos{ PosData["Pos"]["x"],PosData["Pos"]["y"],PosData["Pos"]["z"] };
				//変更スピード
				float speed = PosData["Speed"];
				//Easing
				std::string ease = PosData["Ease"];
				//遅延
				float delay = PosData["Delay"];
				//アニメーション追加
				animation->second->AddPositionAnimation(pos, speed, ease, delay);
			}
			//ポジションループ設定
			if (itr.value()["PositionLoop"])animation->second->PositionLoop();

			//回転アニメーション追加
			num = itr.value()["Rotate"].size();
			for (size_t i = 0; i < num; i++)
			{
				auto& RotaData = itr.value()["Rotate"][i];
				//変更後回転
				DirectX::SimpleMath::Quaternion rota{ RotaData["Rota"]["x"],RotaData["Rota"]["y"],RotaData["Rota"]["z"],RotaData["Rota"]["w"] };
				//変更スピード
				float speed = RotaData["Speed"];
				//Easing
				std::string ease = RotaData["Ease"];
				//遅延
				float delay = RotaData["Delay"];
				//アニメーション追加
				animation->second->AddRotateAnimation(rota, speed, ease, delay);
			}
			//回転ループ設定
			if (itr.value()["RotateLoop"])animation->second->RotateLoop();
		}
	}

}
