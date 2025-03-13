// ================================================================ 
// �t�@�C���� : ResultCanvas.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�p�L�����o�X
// ================================================================

#include"pch.h"
#include"ResultCanvas.h"
#include"Base/Scene/Scene.h"
#include"Game/Result/UI/ResultBG.h"
#include"Game/Result/UI/ResultStageData.h"
#include"Game/Result/UI/ResultTime.h"
#include"Game/Result/UI/ResultScore.h"
#include"Game/Result/UI/ResultOrderTime.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
ResultCanvas::ResultCanvas(Scene* scene):GameCanvas(scene)
{
	scene->AddObject<ResultBG>(this);
	scene->AddObject<ResultStageData>(this);
	scene->AddObject<ResultTime>(this);
	scene->AddObject<ResultScore>(this);
	scene->AddObject<ResultOrderTIme>(this);
}
