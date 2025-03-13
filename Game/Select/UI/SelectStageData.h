// ================================================================ 
// �t�@�C���� : SelectStageData.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�ԍ���\��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Tween;
template<typename...Args>
class Observer;

class SelectStageData :public UserInterface
{
private:
	//�傫��
	DirectX::SimpleMath::Vector2 m_numberSize;
	//�X�e�[�W�ԍ�
	UserInterface* m_stageNumber[2];
	//�傫���ύXTween
	Tween* m_tween;
	//�X�e�[�W�ύX�I�u�U�[�o�[
	Observer<>* m_observer;
public:
	//�R���X�g���N�^
	SelectStageData(Canvas* canvas);
	//�f�X�g���N�^
	~SelectStageData()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//�f�[�^�X�V
	void DataUpdate();
};