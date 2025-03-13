// ================================================================ 
// �t�@�C���� : OptionContents.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �I�v�V�����ł̕ύX���e
// ================================================================

#include"pch.h"
#include"OptionContents.h"
#include"Base/Base.h"
#include"Base/Object/UnbreakableManager.h"

constexpr int BAR_LENTH = 386;             //�o�[�̒���
constexpr int HARF_LENTH = BAR_LENTH / 2;  //�o�[�̒����̔���

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
/// <param name="contentsname">���O(�R���e���c�\�����̉摜)</param>
/// <param name="initialPar">�����p�[�Z���g</param>
OptionContents::OptionContents(Canvas* canvas, std::string contentsname, float initialPar):Button(canvas)
	,
	m_buttonActive{ false },
	m_contents{ nullptr },
	m_contentsName{ contentsname },
	m_mainBar{ nullptr },
	m_subBar{ nullptr },
	m_point{ nullptr },
	m_percent{ initialPar }
{
	using namespace DirectX::SimpleMath;
	SetSize(Vector2(400, 80));
	SetColor(Vector4(0, 0, 0, 0));

	//�{�̃o�[����
	m_mainBar = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "main",canvas,"Quad",7);
	m_mainBar->SetSize(Vector2(390, 14));
	m_mainBar->SetColor(Vector4(0.73f, 0.95f, 0.94f, 1.0f));
	m_mainBar->GetTransform()->SetParent(GetTransform());
	//�T�u�o�[����
	m_subBar = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "sub", canvas, "Quad", 8);
	m_subBar->SetSize(Vector2(BAR_LENTH, 9));
	m_subBar->SetOffset(DirectX::SimpleMath::Vector2(0, 0.5f));
	m_subBar->SetColor(Vector4(0, 0.95f, 0.94f, 1.0f));
	m_subBar->GetTransform()->SetParent(GetTransform());
	//�����|�C���g����
	m_point = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "point", canvas, "BarPoint", 9);
	m_point->SetSize(Vector2(30, 60));
	m_point->GetTransform()->SetParent(GetTransform());
	//�R���e���c�\��������
	m_contents = UnbreakableManager::GetInstance()->AddObject<UserInterface>(m_contentsName + "name",canvas,m_contentsName,7);
	m_contents->SetSize(Vector2(108, 72));
	m_contents->GetTransform()->SetParent(GetTransform());

	
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void OptionContents::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (!m_buttonActive)return;
	auto& mouseTrack = GetCommonResources()->GetInput()->GetMouseTracker();
	//�{�^���������ꂽ��A�N�e�B�u��ԉ���
	if (mouseTrack->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::UP)
	{
		m_buttonActive = false;
		DoFunction();
		return;
	}

	using namespace DirectX::SimpleMath;

	auto& mouseState = GetCommonResources()->GetInput()->GetMouseState();
	//�}�E�X�̈ʒu���擾
	Vector2 position(static_cast<float>(mouseState.x), GetPosition().y);
	//�͈͓��ɗ}����
	if (position.x > GetPosition().x + HARF_LENTH)position.x = GetPosition().x + HARF_LENTH;
	if (position.x < GetPosition().x - HARF_LENTH)position.x = GetPosition().x - HARF_LENTH;
	//�|�C���g�̈ʒu���Z�b�g
	m_point->SetPosition(position);

	//�������v�Z
	m_percent = (position.x - (GetPosition().x - HARF_LENTH)) / BAR_LENTH;

	//�T�u�o�[�̈ʒu�𒲐�
	m_subBar->SetSize(DirectX::SimpleMath::Vector2(BAR_LENTH * m_percent, 9));
}

/// <summary>
/// �|�W�V�������Z�b�g
/// </summary>
/// <param name="position">�ύX�|�W�V����</param>
void OptionContents::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	using namespace DirectX::SimpleMath;
	UserInterface::SetPosition(position);
	m_mainBar->SetPosition(position);
	m_contents->SetPosition(position + Vector2(0, -60));
	m_subBar->SetPosition(position + Vector2(-BAR_LENTH / 2, 0));
	m_subBar->SetSize(Vector2(BAR_LENTH * m_percent, 9));
	m_point->SetPosition(Vector2((position.x - HARF_LENTH) + BAR_LENTH * m_percent, position.y));
}

/// <summary>
/// �J��
/// </summary>
void OptionContents::Open()
{
	SetActive(true);
}

/// <summary>
/// ����
/// </summary>
void OptionContents::Close()
{
	SetActive(false);
}

/// <summary>
/// �}�E�X���m�C�x���g
/// </summary>
/// <param name="within">���g�͈͓̔���</param>
void OptionContents::MouseWithinEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	//�\�����̐F��ύX
	if (within)
	{
		m_contents->SetColor(DirectX::SimpleMath::Vector4(0.1, 0.75f, 0.93f, 1));
	}
	else
	{
		m_contents->SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// ���}�E�X�N���b�N�C�x���g
/// </summary>
/// <param name="within">���g�͈͓̔���</param>
void OptionContents::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	if (within)m_buttonActive = true;
}
