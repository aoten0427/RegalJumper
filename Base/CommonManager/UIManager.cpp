// ================================================================ 
// �t�@�C���� : UIManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  UI�̓���Ǘ�
// ================================================================

#include"pch.h"
#include"UIManager.h"
#include"Base/CommonResources.h"
#include"Base/Input/DirectXInputs.h"
#include"Base/Canvas/UserInterface/UserInterface.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="commonResources">�R�������\�[�X</param>
UIManager::UIManager(CommonResources* commonResources)
	:
	m_userInterfaces{}
{
	//���̓V�X�e������
	m_input = commonResources->GetInput();
}

/// <summary>
/// �X�V
/// </summary>
void UIManager::Update()
{
	//�}�E�X�̍��W���擾
	DirectX::SimpleMath::Vector2 mousePos(static_cast<float>(m_input->GetMouseState().x), static_cast<float>(m_input->GetMouseState().y));

	std::vector<UserInterface*> active;
	//���݃A�N�e�B�u�̂��̂��擾
	for (auto& ui : m_userInterfaces)
	{
		//�C�x���g�t���O���I�t�̏ꍇ�X���[
		if (!ui->GetMouseEventFlag())continue;
		if (ui->GetActive())active.push_back(ui);
	}

	for (auto& ui : active)
	{
		//�͈͂ɓ����Ă��邩
		bool within = WithIn(mousePos, ui);
		//�C�x���g���s
		ui->MouseWithinEvent(within);

		//���L�[�������Ă�����N���b�N�C�x���g���s
		if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
		{
			ui->LeftClickEvent(within);
		}
	}
}

/// <summary>
/// UI�ǉ�
/// </summary>
/// <param name="userinterfase">�ǉ�UI</param>
void UIManager::AddUserInterface(UserInterface* userinterfase)
{
	m_userInterfaces.push_back(userinterfase);
}

/// <summary>
/// UI�폜
/// </summary>
/// <param name="userinterface">�폜UI</param>
void UIManager::ReMoveUserInterface(UserInterface* userinterface)
{
	auto remove = std::find(m_userInterfaces.begin(), m_userInterfaces.end(), userinterface);
	if (remove != m_userInterfaces.end())
	{
		m_userInterfaces.erase(remove);
	}
}

/// <summary>
/// ��������擾
/// </summary>
/// <param name="pos">�}�E�X�|�W�V����</param>
/// <param name="ui">UI</param>
/// <returns>�����ɂ��邩</returns>
bool UIManager::WithIn(const DirectX::SimpleMath::Vector2& pos, UserInterface* ui)
{
	using namespace DirectX::SimpleMath;

	Vector2 position = ui->GetPosition();
	Vector2 size(abs(ui->GetSize().x), abs(ui->GetSize().y));
	Vector2 offsetPar = ui->GetOffset();

	//UI�̎l�����擾
	RECT corner = RECT{
		static_cast<int>(position.x - size.x * offsetPar.x),
		static_cast<int>(position.y - size.y * offsetPar.y),
		static_cast<int>(position.x + size.x * (1 - offsetPar.x)),
		static_cast<int>(position.y + size.y * (1 - offsetPar.y)),
	};

	if (corner.left > pos.x)return false;
	if (corner.right < pos.x)return false;
	if (corner.top > pos.y)return false;
	if (corner.bottom < pos.y)return false;

	return true;
}
