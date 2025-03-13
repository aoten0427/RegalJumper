// ================================================================ 
// ファイル名 : TitleScene.h
// 作成者 : 景山碧天
// 説明 :  タイトルシーン
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class TitleScene :public Scene
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
	TitleScene(CommonResources* resources);
	//デストラクタ
	~TitleScene()override = default;
	//アップデート
	void SceneUpdate(float deltatime)override;
	//シーンID取得
	SceneID GetSceneID() { return SceneID::TITLE; }
};