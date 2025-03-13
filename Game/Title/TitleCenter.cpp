// ================================================================ 
// ファイル名 :TitleCenter.cpp 
// 作成者 : 景山碧天
// 説明 :  タイトルシーンを管理
// ================================================================
#include"pch.h"
#include"TitleCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonResources.h"
#include"Base/Event/Observer.h"
#include"Base/Sound/Sound.h"
#include"Base/Input/DirectXInputs.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
TitleCenter::TitleCenter(Scene* scene) :Object(scene)
{
	m_begin = AddComponent<Observer<>>(this);
	m_begin->SetFunction([&]() {GetScene()->ChangeState(Scene::State::PLAY); });
	m_begin->RegistrationSubject("Reserve");
}

/// <summary>
/// 更新
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void TitleCenter::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::Escape))
	{
		PostQuitMessage(0);
	}
}
