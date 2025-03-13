// ================================================================ 
// �t�@�C���� : UIManager.h
// �쐬�� : �i�R�ɓV
// ���� :  UI�̓���Ǘ�
// ================================================================

#pragma once

class UserInterface;
class CommonResources;
class DirectXInputs;

class UIManager
{
private:
	//���͋@�\
	DirectXInputs* m_input;
	//�Ǘ�UI
	std::vector<UserInterface*> m_userInterfaces;
public:
	//�R���X�g���N�^
	UIManager(CommonResources* commonResources);
	//�f�X�g���N�^
	~UIManager() = default;
	//�A�b�v�f�[�g
	void Update();
	//UI�ǉ�
	void AddUserInterface(UserInterface* userinterfase);
	//UI�폜
	void ReMoveUserInterface(UserInterface* userinterface);
private:
	//��������擾
	bool WithIn(const DirectX::SimpleMath::Vector2& pos, UserInterface* ui);
};