#include"pch.h"
#include"TitleCanvas.h"
#include"Base/Scene/Scene.h"
#include"Game/Title/UI/TitleBG.h"
#include"Game/Title/UI/PlayButton.h"
#include"Game/Title/UI/OptionButton.h"
#include"Game/Title/UI/QuitButton.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
TitleCanvas::TitleCanvas(Scene* scene):GameCanvas(scene)
{
	//�w�i�쐬
	scene->AddObject<TitleBG>(this);
	//�v���C�{�^���쐬
	scene->AddObject<PlayButton>(this);
	//�I�v�V�����{�^���쐬
	scene->AddObject<OptionButton>(this);
	//�I���{�^���쐬
	scene->AddObject<QuitButton>(this);
}

