// ================================================================ 
// �t�@�C���� :PlayerCenter.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�Ɋ֌W������̂��Ǘ�
// ================================================================
#include"pch.h"
#include"PlayerCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Player/Search.h"
#include"Game/Play/Player/Reticle.h"
#include"Game/Parameter/PlayerParameter.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
PlayerCenter::PlayerCenter(Scene* scene):Object(scene)
{
	//�v���C���[����
	m_player = scene->AddObject<Player>(scene,this);
	//������
	m_thread = scene->AddObject<Thread>(scene);
	//�T�[�`���[����
	m_search = scene->AddObject<Search>(scene,m_player);
	m_search->SetRange(PlayerParameter::PARAMETER()->SEARCH_RANGE);
	m_search->SetVision(PlayerParameter::PARAMETER()->SEARCH_VISION);
	//���e�B�N������
	scene->AddObject<Reticle>(scene, m_player);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void PlayerCenter::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	Camera* camera = GetScene()->GetCamera();
	//�T�[�`���[�̌�����ݒ�
	m_search->SetViewingDirection((camera->GetTargetPosition() - camera->GetEyePosition()));
}

/// <summary>
/// ������
/// </summary>
/// <param name="direction">���˕���</param>
void PlayerCenter::ThreadShot(DirectX::SimpleMath::Vector3 direction)
{
	m_thread->Shot(m_player, m_player->GetTransform()->GetWorldPosition(), direction,m_search->GetTarget());
}
