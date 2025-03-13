// ================================================================ 
// ファイル名 : ResultScene.h
// 作成者 : 景山碧天
// 説明 :  リザルトシーン
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class ResultScene :public Scene
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
	ResultScene(CommonResources* resources);
	//デストラクタ
	~ResultScene()override = default;
	//アップデート
	void SceneUpdate(float deltatime)override;
	//シーンID取得
	SceneID GetSceneID() { return SceneID::RESULT; }
};