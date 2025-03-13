// ================================================================ 
// �t�@�C���� : UIReticle.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���e�B�N��
// ================================================================
#include"pch.h"
#include"UIReticle.h"
#include"Base/Scene/Scene.h"
#include"Base/Screen.h"
#include"Base/Event/Observer.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
UIReticle::UIReticle(Canvas* canvas):UserInterface(canvas,"UIReticle",2)
{
	SetPosition(DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y + 10));
	SetSize(DirectX::SimpleMath::Vector2(360, 260));

	UserInterface* esc = GetScene()->AddObject<UserInterface>(canvas, "Escape", 2);
	esc->SetPosition(DirectX::SimpleMath::Vector2(30, 30));
	esc->SetSize(DirectX::SimpleMath::Vector2(35, 35));

	//�|�[�Y�ɕt�������I�u�U�[�o�[
	//�|�[�Y�I�[�v��
	Observer<>* pauseOpen = AddComponent<Observer<>>(this);
	pauseOpen->SetFunction([&]() {SetActive(false); });
	pauseOpen->RegistrationSubject("PauseOpen");
	//�|�[�Y�N���[�Y
	Observer<>* pauseClose = AddComponent<Observer<>>(this);
	pauseClose->SetFunction([&]() {SetActive(true); });
	pauseClose->RegistrationSubject("PauseClose");

	//���e�B�N�����ǂɓ�����ۂ̐F�ύX
	Observer<bool>* hitObs = AddComponent<Observer<bool>>(this);
	hitObs->SetFunction(std::bind(&UIReticle::ChangeColor, this, std::placeholders::_1));
	hitObs->RegistrationSubject("Reticle");
}

/// <summary>
/// ���e�B�N�����ǂɓ�����ۂ̐F�ύX
/// </summary>
/// <param name="hit"></param>
void UIReticle::ChangeColor(bool hit)
{
	if (hit)
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 0.0, 1, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}
