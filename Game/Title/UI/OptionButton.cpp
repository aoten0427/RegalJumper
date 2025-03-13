// ================================================================ 
// �t�@�C���� : OptionButton.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g����ʂł̃I�v�V�����{�^��
// ================================================================

#include"pch.h"
#include "OptionButton.h"
#include"Base/Scene/Scene.h"
#include"Base/Sound/Sound.h"
#include"Game/GameManager.h"


constexpr DirectX::SimpleMath::Vector2 INITIAL_SIZE = DirectX::SimpleMath::Vector2(400, 88);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
OptionButton::OptionButton(Canvas* canvas) :Button(canvas,"OptionButton",1)
{
	SetPosition(DirectX::SimpleMath::Vector2(990, 460));
	SetSize(INITIAL_SIZE);
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select1", false);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void OptionButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//�T�C�Y�ύX
	if (within) { SetSize(INITIAL_SIZE * 1.2f); }
	else { SetSize(INITIAL_SIZE); }
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g �I�v�V�������J��
/// </summary>
/// <param name="within">�͈͓���</param>
void OptionButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//�I�v�V�������J��
		GameManager::GetInstance()->OpenOption();
		SetSize(INITIAL_SIZE);
		m_sound->Play();
	}
}
