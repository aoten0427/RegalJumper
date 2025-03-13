// ================================================================ 
// �t�@�C���� : PlayButton.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g����ʂł̃v���C�{�^��
// ================================================================
#include"pch.h"
#include"Base/Scene/Scene.h"
#include"PlayButton.h"
#include"Base/Fade/FadeManager.h"
#include"Base/Sound/Sound.h"

constexpr DirectX::SimpleMath::Vector2 POSITION = DirectX::SimpleMath::Vector2(940, 330);
constexpr DirectX::SimpleMath::Vector2 INITIAL_SIZE = DirectX::SimpleMath::Vector2(240, 88);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
PlayButton::PlayButton(Canvas* canvas):Button(canvas,"PlayButton",1)
{
	using namespace DirectX::SimpleMath;

	SetPosition(POSITION);
	SetSize(INITIAL_SIZE);
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select1", false);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void PlayButton::MouseWithinEvent(bool within)
{
	using namespace DirectX::SimpleMath;
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//�G��Ă�����傫������
	if (within) { SetSize(INITIAL_SIZE * 1.2f); }
	else { SetSize(INITIAL_SIZE); }
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g �X�e�[�W�I����ʂ̈ړ�
/// </summary>
/// <param name="within">�͈͓���</param>
void PlayButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		//�t�F�[�h���N�����Z���N�g�V�[����
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::SELECT);
			});
		m_sound->Play();
	}
}
