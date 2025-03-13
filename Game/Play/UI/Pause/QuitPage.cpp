// ================================================================ 
// �t�@�C���� : QuitPage.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �ޏo�y�[�W
// ================================================================
#include"pch.h"
#include"QuitPage.h"
#include"Base/Base.h"
#include"Base/Screen.h"
#include"Game/Play/UI/Pause/Pause.h"

constexpr DirectX::SimpleMath::Vector2 BUTTON_SIZE = DirectX::SimpleMath::Vector2(160, 80);
constexpr float BUTTON_X = 150.0f;
constexpr float BUTTON_Y = 500.0f;

/// <summary>
/// �ޏo�I���{�^���@�R���X�g���N�^
/// </summary>
/// <param name="canvas"></param>
QButton::QButton(Canvas* canvas) :Button(canvas)
{
	SetRenderOrder(6);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">�͈͓���</param>
void QButton::MouseWithinEvent(bool within)
{
	//�F�ύX
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0, 0.87f, 0.82f, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// �ޏo�y�[�W�@�R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="pause">�|�[�Y</param>
QuitPage::QuitPage(Canvas* canvas, Pause* pause):UserInterface(canvas,"QuitBorad",5)
{
	using namespace DirectX::SimpleMath;

	
	SetSize(DirectX::SimpleMath::Vector2(640, 640));

	auto bg = GetScene()->AddObject<UserInterface>(canvas);
	bg->GetTransform()->SetParent(GetTransform());
	bg->SetSize(Vector2(Screen::WIDTH, Screen::HEIGHT));
	bg->SetColor(Vector4(1, 1, 1, 0.5));

	
	//�I���͂��{�^��
	auto yes = GetScene()->AddObject<QButton>(canvas);
	yes->SetTexture("Yes");
	yes->SetPosition(Vector2(Screen::CENTER_X - BUTTON_X, BUTTON_Y));
	yes->SetSize(Vector2(160, 80));
	yes->GetTransform()->SetParent(GetTransform());
	yes->SetFunction([&]() {
		PostQuitMessage(0);
		});

	//�I���������{�^��
	auto no = GetScene()->AddObject<QButton>(canvas);
	no->SetTexture("No");
	no->SetPosition(Vector2(Screen::CENTER_X + BUTTON_X, BUTTON_Y));
	no->SetSize(Vector2(240, 80));
	no->GetTransform()->SetParent(GetTransform());
	no->SetFunction([&,pause]() {
		SetActive(false);
		pause->SetActive(true);
		});

	SetActive(false);
}


