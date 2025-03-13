// ================================================================ 
// �t�@�C���� : CursorEffect.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �J�[�\���N���b�N���̃G�t�F�N�g
// ================================================================

#include"pch.h"
#include"CursorEffect.h"
#include"Base/Tween/DoTween.h"

constexpr float INITIAL_SIZE = 20;
constexpr float TARGET_SIZE = 70;
constexpr float SPEED = 0.2f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="position">�����ʒu</param>
CursorEffect::CursorEffect(Canvas* canvas, DirectX::SimpleMath::Vector2 position):UserInterface(canvas,"CursorEffect",8)
	,
	m_size{INITIAL_SIZE}
{

	SetSize(DirectX::SimpleMath::Vector2(m_size,m_size));
	SetPosition(position);

	//�ω�Tween����
	Tween* tween = AddComponent<Tween>(this);
	tween->DoFloat(m_size, TARGET_SIZE, SPEED).SetEase(Easing::Ease::Normal).SetCompleteFunction([&]() {
		Destroy();
		});
}

/// <summary>
/// �A�b�v�f�[�g�@�T�C�Y�ύX
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void CursorEffect::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetSize(DirectX::SimpleMath::Vector2(m_size, m_size));
}
