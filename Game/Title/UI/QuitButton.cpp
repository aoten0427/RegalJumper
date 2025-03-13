#include"pch.h"
#include"QuitButton.h"
#include"Base/Base.h"
#include"Base/Sound/Sound.h"

constexpr DirectX::SimpleMath::Vector2 POSITION = DirectX::SimpleMath::Vector2(910, 590);
constexpr DirectX::SimpleMath::Vector2 INITIAL_SIZE = DirectX::SimpleMath::Vector2(240, 88);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
QuitButton::QuitButton(Canvas* canvas):Button(canvas,"QuitButton",2)
{
	SetPosition(POSITION);
	SetSize(INITIAL_SIZE);
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select1", false);
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void QuitButton::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//�T�C�Y�ύX
	if (within) { SetSize(INITIAL_SIZE * 1.2f); }
	else { SetSize(INITIAL_SIZE); }
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g �����ꂽ��Q�[���I��
/// </summary>
/// <param name="within">�͈͓���</param>
void QuitButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		PostQuitMessage(0);
	}
}
