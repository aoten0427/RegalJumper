// ================================================================ 
// �t�@�C���� : SpiderActionAnimation.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̋󒆋@���A�j���[�V����
// ================================================================

#pragma once
#include"Base/MyLibraries/Animation/Animator.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAction.h"

class SpiderModels;
class Rigidbody;
class Tween;

class SpiderActionAnimator :public Animator
{
private:
	
private:
	enum class State
	{
		NORMAL,
		ROTATE
	};
private:
	State m_state;
	//���f��
	SpiderModels* m_models;
	//���W�b�h�{�f�B
	Rigidbody* m_playerRigidbody;
	//�ύX�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	//��]��
	DirectX::SimpleMath::Vector3 m_axis;
	//��]��
	float m_radian;
	//�����
	float m_resetTime;
	//�A�N�V����
	std::vector<std::unique_ptr<SpiderAction>> m_actions;
	//�ύX�pTween
	Tween* m_tween;
public:
	//�R���X�g���N�^
	SpiderActionAnimator(std::string name, SpiderModels* model);
	~SpiderActionAnimator() override = default;
	//�v���C
	void Play()override;
	//�A�b�v�f�[�g
	void Update(float deltatime)override;

private:
	//�A�N�V�����̑I��
	DirectX::SimpleMath::Vector3 SelectAction();
	//��l�ɖ߂�
	void ToNormal();
};