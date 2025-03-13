// ================================================================ 
// �t�@�C���� : Animator.h
// �쐬�� : �i�R�ɓV
// ���� :  �����̃A�j���[�V�������܂Ƃ߂�����
// ================================================================

#pragma once
#include"Base/MyLibraries/Animation/Animation.h"
#include"Base/Config.h"

class Object;
class AnimatiorCenter;

class Animator
{
public:
	std::string GetName() { return m_name; }

	void SetAnimatorCenter(AnimatiorCenter* center) { m_animatorCenter = center; }

	void SetIsParallel(bool isparallel) { m_isParallel = isparallel; }
	bool GetIsParallel() const { return m_isParallel; }
private:
	//���O
	std::string m_name;
	//�ǂݍ��݃t�@�C��
	std::string m_filename;
	//�A�j���[�V����
	std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
	//�Ǘ���
	AnimatiorCenter* m_animatorCenter;
	//����ŋN�����邩����
	bool m_isParallel;
public:
	//�R���X�g���N�^
	Animator(std::string name,std::string filename = Config::NONE_FILE);
	//�f�X�g���N�^
	virtual ~Animator() = default;
	//�J�n
	virtual void Play();
	//�A�b�v�f�[�g
	virtual void Update(float deltatime);
	//�I��
	virtual void End();
	//�A�j���[�^�[�Z���^�[�ւ̃X�g�b�v�ʒm
	void ActiveOff();
	//�A�j���[�V�����쐬
	void AddAnimation(std::string name, Object* object);
	//�t�@�C���̃��[�h
	void LoadData();
};