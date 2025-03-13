#include"pch.h"
#include"DirectXInputs.h"

DirectXInputs::DirectXInputs(const HWND& window)
{
	// �}�E�X���g�p�ł����Ԃɂ���
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// �L�[�{�[�h���g�p�ł����Ԃɂ���
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}

void DirectXInputs::Update()
{
	// �}�E�X�̏����X�V����
	m_mouseState = m_mouse->GetState();
	m_mouseTracker->Update(m_mouseState);

	// �L�[�{�[�h�̏����X�V����
	m_keyboardState = m_keyboard->GetState();
	m_keyboardTracker->Update(m_keyboardState);
}
