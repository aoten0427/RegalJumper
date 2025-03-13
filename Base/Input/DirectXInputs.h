#pragma once


class DirectXInputs
{
private:
	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
	DirectX::Mouse::State m_mouseState;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;
	DirectX::Keyboard::State m_keyboardState;
public:
	DirectXInputs(const HWND& window);
	~DirectXInputs() = default;

	void Update();


	// �}�E�X�X�e�[�g���擾����
	const DirectX::Mouse::State& GetMouseState() const
	{
		return m_mouseState;
	}
	// �}�E�X�̃{�^���X�e�[�g�g���b�J�[���擾����
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker() const
	{
		return m_mouseTracker;
	}
	// �L�[�{�[�h�X�e�[�g���擾����
	const DirectX::Keyboard::State& GetKeyboardState() const
	{
		return m_keyboardState;
	}
	// �L�[�{�[�h�̃X�e�[�g�g���b�J�[���擾����
	const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyboardTracker() const
	{
		return m_keyboardTracker;
	}

	const bool IsKeyFree(DirectX::Keyboard::Keys key)
	{
		return m_keyboardState.IsKeyUp(key);
	}

	const bool IsKeyDown(DirectX::Keyboard::Keys key)
	{
		return m_keyboardState.IsKeyDown(key);
	}

	const bool IsKeyPress(DirectX::Keyboard::Keys key)
	{
		return m_keyboardTracker->IsKeyPressed(key);
	}

	const bool IsKeyRelease(DirectX::Keyboard::Keys key)
	{
		return m_keyboardTracker->IsKeyReleased(key);
	}

	int GetScrollWheel()
	{
		return m_mouseState.scrollWheelValue;
	}

	
};