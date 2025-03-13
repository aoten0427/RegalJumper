// ================================================================ 
// �t�@�C���� : AnimatorCcenter.h
// �쐬�� : �i�R�ɓV
// ���� :  ����̃I�u�W�F�N�g�𓮂����A�j���[�^�[�̊Ǘ����s��
// ================================================================
#include"pch.h"
#include"AnimatorCenter.h"
#include"Base/MyLibraries/Animation/Animator.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
AnimatiorCenter::AnimatiorCenter()
	:
	m_activeAnimator{},
	m_animators{},
	m_animationObjects{},
	m_singleAnimator{"",nullptr}
{

}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
void AnimatiorCenter::Update(float deltatime)
{
	if (m_activeAnimator.empty())return;
	for (auto& animator : m_activeAnimator)
	{
 		animator.second->Update(deltatime);
	}
	for (auto& remove : m_removeAnimator)
	{
		m_activeAnimator.erase(remove);
	}
	m_removeAnimator.clear();
}


/// <summary>
/// �A�j���[�^�[�̃A�N�e�B�u��؂�ւ�
/// </summary>
/// <param name="name"></param>
/// <param name="active"></param>
void AnimatiorCenter::SetActiveAnimator(std::string name, bool active)
{
	//�A�j���[�^�[�����邩���f
	if (m_animators.find(name) == m_animators.end())return;

	//�A�N�e�B�u�ݒ�
	if (active)
	{
		if (m_activeAnimator.find(name) != m_activeAnimator.end())return;
		//���񔻒�
		bool parallel = m_animators[name]->GetIsParallel();
		//����A�j���[�^�[�łȂ��ꍇ�A�j���[�^�[���~�߂�
		if (!parallel)
		{
			//���݂̒P��A�j���[�^�[���~�߂�
			if (m_singleAnimator.second)SetActiveAnimator(m_singleAnimator.first, false);
			//�P��A�j���[�^�[������������
			m_singleAnimator = { name,m_animators[name].get() };

		}
		//�A�N�e�B�u�ݒ�
		m_activeAnimator[name] = m_animators[name].get();
		m_activeAnimator[name]->Play();
	}
	//��A�N�e�B�u�ݒ�
	else
	{
		if (m_activeAnimator.find(name) == m_activeAnimator.end())return;
		if (m_singleAnimator.first == name)m_singleAnimator = { "",nullptr };
		//�A�N�e�B�u����
		m_animators[name].get()->End();
		m_removeAnimator.insert(name);
	}
	
}



/// <summary>
/// �A�j���[�^�[�ǉ�
/// </summary>
/// <param name="name">�A�j���[�^�[��</param>
/// <param name="animator">�A�j���[�^�[</param>
void AnimatiorCenter::AddAnimator(std::unique_ptr<Animator> animator)
{
	std::string name = animator.get()->GetName();
	m_animators.insert({ name,std::move(animator) });
	m_animators[name].get()->SetAnimatorCenter(this);
}

/// <summary>
/// �A�j���[�V�����I�u�W�F�N�g�ǉ�
/// </summary>
/// <param name="name">�I�u�W�F�N�g��</param>
/// <param name="object">�I�u�W�F�N�g</param>
void AnimatiorCenter::AddAnimationObject(std::string name, Object* object)
{
	m_animationObjects.insert({ name,object });
}

/// <summary>
/// �e�A�j���[�^�[�ɃA�j���[�V�����ǉ�
/// </summary>
void AnimatiorCenter::AddAnimationToAnimator()
{
	for (auto& animator : m_animators)
	{
		for (auto& animation : m_animationObjects)
		{
			animator.second->AddAnimation(animation.first, animation.second);
		}
	}
}

/// <summary>
/// �e�A�j���[�^�[�Ƀt�@�C���̃��[�h�w��
/// </summary>
void AnimatiorCenter::LoadAnimation()
{
	for (auto& animator : m_animators)
	{
		animator.second->LoadData();
	}
}
