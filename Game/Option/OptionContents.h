// ================================================================ 
// �t�@�C���� : OptionContents.h
// �쐬�� : �i�R�ɓV
// ���� :  �I�v�V�����ł̕ύX���e
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class OptionContents:public Button
{
public:
	float GetPearcent() const { return m_percent; }
private:
	//����̃A�N�e�B�u�t���O
	bool m_buttonActive;
	//���썀��
	UserInterface* m_contents;
	//���썀�ږ�
	std::string m_contentsName;
	//�{�̃o�[
	UserInterface* m_mainBar;
	//�����͈͕`��o�[
	UserInterface* m_subBar;
	//�ړ������|�C���g
	UserInterface* m_point;
	//�ړ�����
	float m_percent;
public:
	//�R���X�g���N�^
	OptionContents(Canvas* canvas, std::string contentsname, float initialPar = 0.5f);
	//�f�X�g���N�^
	~OptionContents() override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime) override;
	//�|�W�V�����Z�b�g
	void SetPosition(const DirectX::SimpleMath::Vector2& position);
	//open
	void Open();
	//close
	void Close();
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within) override;
	//���}�E�X�N���b�N�C�x���g
	void LeftClickEvent(bool within) override;
};