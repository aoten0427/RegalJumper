// ================================================================ 
// �t�@�C���� : SpiderAnimatorCenter.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̃A�j���[�V�������Ǘ�
// ================================================================
#include"pch.h"
#include"SpiderAnimatorCenter.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"
#include"Game/Play/Player/SpiderAnimation/SpiderActionAnimator.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="models">�w偃��f��</param>
SpiderAnimatorCenter::SpiderAnimatorCenter(SpiderModels* models)
{
	//�A�j���[�^�[�쐬
	AddAnimator(std::make_unique<Animator>("PlayerIdle","Resources/JSON/PlayerData/Player_Idle.json"));
	AddAnimator(std::make_unique<Animator>("PlayerWalk","Resources/JSON/PlayerData/Player_Walk.json"));
	AddAnimator(std::make_unique<Animator>("PlayerAir", "Resources/JSON/PlayerData/Player_Air.json"));
	AddAnimator(std::make_unique<SpiderActionAnimator>("PlayerAction", models));
	//�A�j���[�^�[�ɃI�u�W�F�N�g��o�^
	AddAnimationObject("Main",models);
	auto modelParts = models->GetModelParts();
	for (auto& parts : modelParts)
	{
		AddAnimationObject(parts->GetName(), parts);
	}
	AddAnimationToAnimator();
	//�A�j���[�V�������[�h
	LoadAnimation();

	SetActiveAnimator("PlayerIdle", true);
}
