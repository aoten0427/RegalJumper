#include"pch.h"
#include"DirectXInputs.h"

DirectXInputs::DirectXInputs(const HWND& window)
{
	// マウスを使用できる状態にする
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// キーボードを使用できる状態にする
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}

void DirectXInputs::Update()
{
	// マウスの情報を更新する
	m_mouseState = m_mouse->GetState();
	m_mouseTracker->Update(m_mouseState);

	// キーボードの情報を更新する
	m_keyboardState = m_keyboard->GetState();
	m_keyboardTracker->Update(m_keyboardState);
}
