// ================================================================ 
// ファイル名 : Option.cpp
// 作成者 : 景山碧天
// 説明 :  オプション
// ================================================================
#include"pch.h"
#include"Option.h"
#include"Base/Screen.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/Object/UnbreakableManager.h"
#include"Base/Event/Subject.h"
#include"Base/Tween/DoTween.h"
#include"Base/Sound/SoundManager.h"
#include"Game/GameManager.h"
#include"Game/Option/OptionContents.h"
#include"Game/Option/OptionExitButton.h"


constexpr float BGM_POSITION = 180.0f;//BGM表示位置
constexpr float SE_POSITION = 350.0f;//SE表示位置
constexpr float SENSITIVITY_POSITION = 520.0f;//感度表示位置

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
Option::Option(Canvas* canvas):UserInterface(canvas,"Option",5)
	,
	m_oldSceneState{Scene::State::RESERVE},
	m_size{ Screen::WIDTH / 2,0 },
	m_openSubject{nullptr},
	m_closeSubject{nullptr}
{
	using namespace DirectX::SimpleMath;
	//ゲームマネジャーに登録
	GameManager::GetInstance()->SetOption(this);

	LoadData();

	//情報設定
	SetPosition(Vector2(Screen::CENTER_X, Screen::CENTER_Y));
	SetSize(m_size);
	//tween作成
	m_tween = AddComponent<Tween>(this,true);
	//Subject作成
	m_openSubject = AddComponent<Subject<>>(this, "OptionOpen");
	m_closeSubject = AddComponent<Subject<>>(this, "OptionClose");

	//変更内容作成
	//BGM
	m_contents[0] = UnbreakableManager::GetInstance()->AddObject<OptionContents>("BGM", canvas, "BGM",m_initialParcent[0]);
	m_contents[0]->SetPosition(Vector2(Screen::CENTER_X, BGM_POSITION));
	m_contents[0]->Close();
	m_contents[0]->SetFunction([&]() {
		SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::BGM, m_contents[0]->GetPearcent());
		});
	//SE
	m_contents[1] = UnbreakableManager::GetInstance()->AddObject<OptionContents>("SE", canvas, "SE",m_initialParcent[1]);
	m_contents[1]->SetPosition(Vector2(Screen::CENTER_X, SE_POSITION));
	m_contents[1]->Close();
	m_contents[1]->SetFunction([&]() {
		SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::SE, m_contents[1]->GetPearcent());
		});
	//感度
	m_contents[2] = UnbreakableManager::GetInstance()->AddObject<OptionContents>("Sensitivity", canvas, "Sensitivity", m_initialParcent[2]);
	m_contents[2]->SetPosition(Vector2(Screen::CENTER_X, SENSITIVITY_POSITION));
	m_contents[2]->Close();
	m_contents[2]->SetFunction([&]() {
		m_sensitivity = m_contents[2]->GetPearcent();
		});
	//退出ボタン
	m_exitButton = UnbreakableManager::GetInstance()->AddObject<OptionExit>("OptionExit", canvas, this);
	m_exitButton->SetFunction([&]() {Close(); });

	//初期音量設定
	SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::BGM, m_initialParcent[0]);
	SoundManager::GetInstance()->ChangeVolume(Sound::SoundType::SE, m_initialParcent[1]);
	m_sensitivity = m_initialParcent[2];
}



/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Option::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetSize(m_size);
}

/// <summary>
/// 終了処理　オプションデータの保存
/// </summary>
void Option::Finalize()
{
	WriteData();
}

/// <summary>
/// 開く
/// </summary>
void Option::Open()
{
	using namespace DirectX::SimpleMath;
	//前の状態を取得
	m_oldSceneState = GetScene()->GetState();
	//シーンの状態変更
	GetScene()->ChangeState(Scene::State::STOP);
	//開く
	m_tween->DoVector2(m_size, Vector2(Screen::WIDTH / 2, Screen::HEIGHT), 0.2f).SetCompleteFunction([&]() {
		//要素をみえるようにする
		for (int i = 0; i < SELECT_NUM; i++)
		{
			m_contents[i]->Open();
		}
		m_exitButton->SetActive(true);
		});
	//開いた通知を出す
	m_openSubject->Notify();
}

/// <summary>
/// 閉じる
/// </summary>
void Option::Close()
{
	using namespace DirectX::SimpleMath;
	//開始前の状態に変化
	GetScene()->ChangeState(m_oldSceneState);
	//閉じる
	m_tween->DoVector2(m_size, Vector2(Screen::WIDTH / 2, 0), 0.2f);
	//要素を見えなくする
	for (int i = 0; i < SELECT_NUM; i++)
	{
		m_contents[i]->Close();
	}
	m_exitButton->SetActive(false);
	//閉じた通知を出す
	m_closeSubject->Notify();
}

/// <summary>
/// データ読み込み
/// </summary>
void Option::LoadData()
{
	//JSONファイル選択
	std::string filename = "Resources/JSON/Option/Option.json";

	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//各要素のパーセント初期値を取得
		m_initialParcent[0] = m_json["BGM"];
		m_initialParcent[1] = m_json["SE"];
		m_initialParcent[2] = m_json["Sensitivity"];


		ifs.close();
	}
}

/// <summary>
/// データ書き込み
/// </summary>
void Option::WriteData()
{
	//JSONファイル選択
	std::string filename = "Resources/JSON/Option/Option.json";

	//読み込み
	std::ofstream close(filename.c_str());
	if (close.good())
	{
		nlohmann::json m_json;

		//各要素のパーセントを保存
		m_json["BGM"] = m_contents[0]->GetPearcent();
		m_json["SE"] = m_contents[1]->GetPearcent();
		m_json["Sensitivity"] = m_contents[2]->GetPearcent();

		close << m_json;

		close.close();
	}
}
