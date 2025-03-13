// ================================================================ 
// �t�@�C���� : AnimatorCcenter.h
// �쐬�� : �i�R�ɓV
// ���� :  ����̃I�u�W�F�N�g�𓮂����A�j���[�^�[�̊Ǘ����s��
// ================================================================

#pragma once
#include"Base/MyLibraries/Animation/Animator.h"
class Object;
class Animator;

class AnimatiorCenter
{
private:
	std::unordered_map<std::string, Animator*> m_activeAnimator;
	//����A�j���[�^�[
	/*std::pair<std::string,Animator*> m_currentAnimator;*/
	//�o�^�A�j���[�^�[
	std::unordered_map<std::string, std::unique_ptr<Animator>> m_animators;
	//�A�j���[�V�����I�u�W�F�N�g
	std::unordered_map<std::string, Object*> m_animationObjects;
	//
	std::pair<std::string,Animator*> m_singleAnimator;
	//
	std::unordered_set<std::string> m_removeAnimator;
public:
	AnimatiorCenter();
	~AnimatiorCenter() = default;
	//�A�b�v�f�[�g
	void Update(float deltatime);

	//�A�j���[�^�[�̃A�N�e�B�u��ݒ�
	void SetActiveAnimator(std::string name, bool active);
	//�A�j���[�^�[�ǉ�
	void AddAnimator(std::unique_ptr<Animator> animator);
	//�I�u�W�F�N�g�ǉ�
	void AddAnimationObject(std::string name, Object* object);
	//�e�A�j���[�^�[�ɃA�j���[�V�����ǉ�
	void AddAnimationToAnimator();
	//�e�A�j���[�^�[�Ƀt�@�C���̃��[�h�w��
	void LoadAnimation();
};