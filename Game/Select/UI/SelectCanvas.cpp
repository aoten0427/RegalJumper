// ================================================================ 
// �t�@�C���� : SelectCanvas.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[���L�����o�X
// ================================================================
#include"pch.h"
#include"SelectCanvas.h"
#include"Base/Scene/Scene.h"
#include"Game/Select/UI/SelectUIBase.h"
#include"Game/Select/UI/SelectStageData.h"
#include"Game/Select/UI/SelectArrow.h"
#include"Game/Select/UI/SelectBestTime.h"
#include"Game/Select/UI/SelectExitButton.h"
#include"Game/Select/UI/SelectPlayButton.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
SelectCanvas::SelectCanvas(Scene* scene):GameCanvas(scene)
{
	scene->AddObject<SelectUIBase>(this);
	scene->AddObject<SelectBestTime>(this);
	scene->AddObject<SelectArrow>(this);
	scene->AddObject<SelectArrow>(this, true);
	scene->AddObject<SelectStageData>(this);
	scene->AddObject<SelectExitButton>(this);
	scene->AddObject<SelectPlayButton>(this);
}
