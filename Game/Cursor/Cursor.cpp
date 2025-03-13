// ================================================================ 
// �t�@�C���� : Cursor.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �J�[�\����\��
// ================================================================
#include"pch.h"
#include"Cursor.h"
#include"Base/Base.h"
#include"Game/GameManager.h"
#include"Game/Cursor/CursorEffect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
Cursor::Cursor(Canvas* canvas):UserInterface(canvas,"Cursor",10)
{
	GameManager::GetInstance()->SetCursor(this);
	SetSize(DirectX::SimpleMath::Vector2(20, 20));
	SetColor(DirectX::SimpleMath::Vector4(0.1f, 1.0f, 0.8f, 1.0f));
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Cursor::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (!GetActive())return;
	//�ʒu���X�V
	DirectXInputs* input = GetCommonResources()->GetInput();
	auto& mouse = input->GetMouseState();
	SetPosition(DirectX::SimpleMath::Vector2(static_cast<float>(mouse.x), static_cast<float>(mouse.y)));
	//�N���b�N�C�x���g
	if (input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		MakeEffect();
	}
}

/// <summary>
/// �G�t�F�N�g����
/// </summary>
void Cursor::MakeEffect()
{
	GetScene()->AddObject<CursorEffect>(GetCanvas(), GetPosition());
}
