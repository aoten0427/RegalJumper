// ================================================================ 
// ファイル名 : SelectScene.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーン
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class SelectScene :public Scene
{
public:
	Camera* GetCamera()const { return m_camera; }
	Canvas* GetCanvas()const { return m_canvas; }
private:
	//カメラ
	Camera* m_camera;
	//キャンバス
	Canvas* m_canvas;
public:
	//コンストラクタ
	SelectScene(CommonResources* resources);
	//デストラクタ
	~SelectScene()override = default;
	//アップデート
	void SceneUpdate(float deltatime)override;
	//シーンID取得
	SceneID GetSceneID() { return SceneID::SELECT; }
};