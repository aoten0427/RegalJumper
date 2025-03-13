// ================================================================ 
// ファイル名 : PlayScene.h
// 作成者 : 景山碧天
// 説明 :  プレイシーン
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class PlayScene :public Scene
{
public:
	Camera* GetCamera()const override{ return m_camera; }
	Canvas* GetCanvas()const override{ return m_canvas; }
private:
	//カメラ
	Camera* m_camera;
	//キャンバス
	Canvas* m_canvas;
public:
	//コンストラクタ
	PlayScene(CommonResources* resources);
	//デストラクタ
	~PlayScene()override = default;
	//アップデート
	void SceneUpdate(float deltatime)override;
	//シーンID取得
	SceneID GetSceneID() { return SceneID::PLAY; }
};