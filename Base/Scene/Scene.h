// ================================================================ 
// ファイル名 : Scene.h
// 作成者 : 景山碧天
// 説明 :  シーン基底クラス
// ================================================================

#pragma once

// 前方宣言
class CommonResources;
class Object;
class Camera;
class Canvas;

class CollisionManager;
class RigidbodyManager;
class RenderManager;
class DebugCollider;
class UIManager;
class SceneState;

class Scene
{
public:
	//シーンID
	enum class SceneID
	{
		NONE,
		TITLE,
		SELECT,
		PLAY,
		RESULT,
		EDITOR
	};
	//シーンステート
	enum class State
	{
		RESERVE, //開始
		PLAY,    //実行
		STOP,    //ストップ
		FEAD,    //フェード
		END,     //終了
	};
public:
	//名前取得
	std::string GetName()const { return m_name; }
	//コモンリソース取得
	CommonResources* GetCommonResources()const { return m_commonResources; }
	//カメラ取得
	virtual Camera* GetCamera()const = 0;
	//キャンバス取得
	virtual Canvas* GetCanvas()const = 0;
	//判定マネージャー取得
	CollisionManager* GetCollisionManager()const { return m_collisionManager.get(); }
	//リジッドボディマネージャー取得
	RigidbodyManager* GetRigidbodyManager()const { return m_rigidbodyManager.get(); }
	//描画マネージャー取得
	RenderManager* GetRenderManager()const { return m_renderManager.get(); }
	//デバックコライダー取得
	DebugCollider* GetDebugCollider()const { return m_debugCollider.get(); }
	//UIマネージャー取得
	UIManager* GetUIManager()const { return m_uiManager.get(); }
	//オブジェクト削除フラグオン
	void ObjectDestroyOn() { m_isObjectDestroy = true; }
private:
	//名前
	std::string m_name;
	//ネクストシーン
	SceneID m_nextSceneID;
	//コモンリソース
	CommonResources* m_commonResources;
	//管理オブジェクト
	std::vector<std::unique_ptr<Object>> m_objects;
	//保留オブジェクト
	std::vector<std::unique_ptr<Object>> m_pendingObjects;
	//アップデート確認
	bool m_updating;
	//オブジェクト削除フラグ
	bool m_isObjectDestroy;

	//衝突マネージャー
	std::unique_ptr<CollisionManager> m_collisionManager;
	//Rigidbodyマネージャー
	std::unique_ptr<RigidbodyManager> m_rigidbodyManager;
	//描画マネージャー
	std::unique_ptr<RenderManager> m_renderManager;
	//デバッグコライダー
	std::unique_ptr<DebugCollider> m_debugCollider;
	//UIマネージャー
	std::unique_ptr<UIManager>     m_uiManager;

	//状態
	SceneState* m_state;
public:
	//コンストラクタ
	Scene(CommonResources* resources,std::string name);
	//デストラクタ
	virtual ~Scene();
	//初期化
	virtual void Initialize();
	//アップデート
	void Update(float deltatime);
	//シーンアップデート
	virtual void SceneUpdate(float deltatime) { UNREFERENCED_PARAMETER(deltatime); };
	//描画
	void Render();
	//終了処理
	void Finalize();

	//シーンID取得
	virtual SceneID GetSceneID() = 0;
	//シーン切り替え
	virtual void ChangeScene(SceneID nextscene) { m_nextSceneID = nextscene; };
	//シーンID取得
	virtual SceneID GetNextSceneID() { return m_nextSceneID; };

	//オブジェクト追加
	template<typename Obj,typename... Args>
	Obj* AddObject(Args&&... args);
	//オブジェクト削除
	void RemoveObject();

	//状態切り替え
	void ChangeState(Scene::State state);
	Scene::State GetState()const;
};

//オブジェクト追加
template<typename Obj, typename ...Args>
inline Obj* Scene::AddObject(Args && ...args)
{
	//オブジェクト生成
	auto object = std::make_unique<Obj>(std::forward<Args>(args)...);
	//戻り値生成
	Obj* back = object.get();
	if (m_updating)
	{
		//アップデート中なら保留オブジェクトへ移動
		m_pendingObjects.push_back(std::move(object));
	}
	else
	{
		//アップデート中でないなら更新オブジェクトへ移動
		m_objects.push_back(std::move(object));
	}
	return back;
}
