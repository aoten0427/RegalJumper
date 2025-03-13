// ================================================================ 
// ファイル名 : SceneManager.cpp
// 作成者 : 景山碧天
// 説明 :  シーン管理マネージャ
// ================================================================

#include"pch.h"
#include"SceneManager.h"
#include"Base/CommonResources.h"
#include"Game/Scene/TitleScene.h"
#include"Game/Scene/SelectScene.h"
#include"Game/Scene/PlayScene.h"
#include"Game/Scene/ResultScene.h"
#include"Game/Scene/EditorScene.h"
#include"Base/Object/UnbreakableManager.h"
#include"Game/Parameter/ParameterManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{nullptr},
	m_unbreakableManager{nullptr},
	m_commonResources{nullptr}
{
	ParameterManager::LoadDaata();
	ShowCursor(false);
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources"コモンリソース></param>
void SceneManager::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	m_unbreakableManager = UnbreakableManager::GetInstance();

	ChangeScene(Scene::SceneID::TITLE);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void SceneManager::Update(float deltatime)
{
	// 説明用変数：次のシーン
	const Scene::SceneID nextSceneID = m_currentScene->GetNextSceneID();
	// シーンを変更しないとき
	if (nextSceneID != Scene::SceneID::NONE)
	{
		// シーンを変更するとき
		ChangeScene(nextSceneID);
	}
	//シーンアップデート
	m_currentScene->Update(deltatime);
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Render()
{
	m_currentScene->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
	//現在稼働中のシーンの前に非破壊オブジェクトを消す
	m_unbreakableManager->Delete();
	//現在のシーンの削除
	m_currentScene.reset();
}

/// <summary>
/// シーン変更
/// </summary>
/// <param name="sceneID"></param>
void SceneManager::ChangeScene(Scene::SceneID sceneID)
{
	DeleteScene();
	CreateScene(sceneID);
}

/// <summary>
/// シーン生成
/// </summary>
/// <param name="sceneID">変更ID</param>
void SceneManager::CreateScene(Scene::SceneID sceneID)
{
	//IDに合わせてシーンを生成
	switch (sceneID)
	{
	case Scene::SceneID::NONE:
		break;
	case Scene::SceneID::TITLE:
		m_currentScene = std::make_unique<TitleScene>(m_commonResources);
		break;
	case Scene::SceneID::SELECT:
		m_currentScene = std::make_unique<SelectScene>(m_commonResources);
		break;
	case Scene::SceneID::PLAY:
		m_currentScene = std::make_unique<PlayScene>(m_commonResources);
		break;
	case Scene::SceneID::RESULT:
		m_currentScene = std::make_unique<ResultScene>(m_commonResources);
		break;
	case Scene::SceneID::EDITOR:
		m_currentScene = std::make_unique<EditorScene>(m_commonResources);
		break;
	default:
		assert(!"SceneManager::CreateScene::シーン名が存在しません！");
		break;
	}

	//シーンを初期化
	m_currentScene->Initialize();
	//非破壊オブジェクトのロード
	m_unbreakableManager->LoadScene(m_currentScene.get());
}

/// <summary>
/// シーン削除
/// </summary>
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}
