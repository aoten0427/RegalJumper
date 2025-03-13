#include"pch.h"
#include"EditorScene.h"
#include"Base/Base.h"
#include"Base/Camera/DebugCamera.h"
#include"Base/Canvas/Canvas.h"
#include"Base/Canvas/UserInterface/UserInterface.h"

#include"MyLib/DebugString.h"
#include"Base/Object/TestObject.h"
#include"Base/Object/TestObject2.h"
#include"Base/Input/DirectXInputs.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
EditorScene::EditorScene(CommonResources* resources) :Scene(resources,"Editor")
{
	m_camera = AddObject<DebugCamera>(this);
	m_canvas = AddObject<Canvas>(this);

	/*AddObject<TestObject>(this);*/
	auto obj = AddObject<TestObject2>(this);
	/*obj->AddComponent<Rigidbody>(obj);
	AddObject<SpiderModels>(this,obj);*/
	/*AddObject<TestObject2>(this);*/
}

EditorScene::~EditorScene()
{

}

void EditorScene::Initialize()
{
}

void EditorScene::SceneUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::G))
	{
		ChangeScene(Scene::SceneID::TITLE);
	}
}

void EditorScene::Render()
{

}
