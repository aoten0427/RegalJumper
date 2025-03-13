#pragma once
#include"Base/Scene/Scene.h"

class EditorScene :public Scene
{
public:
	Camera* GetCamera()const { return m_camera; }
	Canvas* GetCanvas()const { return m_canvas; }
private:
	Camera* m_camera;

	Canvas* m_canvas;
public:
	EditorScene(CommonResources* resources);
	~EditorScene();

	void Initialize()override;

	void SceneUpdate(float deltatime)override;

	void Render();

	//ƒV[ƒ“IDæ“¾
	SceneID GetSceneID() { return SceneID::EDITOR; }
};