// ================================================================ 
// �t�@�C���� : Search.h
// �쐬�� : �i�R�ɓV
// ���� :  �^�[�Q�b�g��T���T�[�`���[
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Game/Play/Enemy/Target.h"

template<typename...Args>
class Observer;

class Search :public Object
{
public:
	//�^�O�擾
	ObjectTag GetTag() { return ObjectTag::Search; }
	//�����ݒ�
	void SetViewingDirection(const DirectX::SimpleMath::Vector3& view) { m_viewingDirection = view; m_viewingDirection.Normalize(); }
	//�{���͈�
	void SetRange(const float& range) { m_range = range; }
	//���o�͈͐ݒ�
	void SetVision(const float& vision) { m_vision = vision; }
	//�^�[�Q�b�g�̎擾
	Target* GetTarget() { return m_target; }
private:
	//�^�[�Q�b�g
	Target* m_target;
	//�T���^�[�Q�b�g�̎��
	std::unordered_map<Target::TargetType, bool> m_searchType;
	//�����Ă������
	DirectX::SimpleMath::Vector3 m_viewingDirection;
	//�{���͈�
	float m_range;
	//���o�͈�
	float m_vision;
	//�^�[�Q�b�g�����I�u�U�[�o�[
	Observer<>* m_targetDelete;
public:
	//�R���X�g���N�^
	Search(Scene* scene,Object* holder, float radius = 100.0f);
	//�f�X�g���N�^
	~Search()override = default;
	void ObjectUpdate(float deltatime)override;
	//Trigger�̎��s�L��
	bool IsTriggerAct(Collider* collider) override;
	//Trigger����
	void OnTrigger(Collider* collider) override;
private:
	//�^�[�Q�b�g��I��
	void SelectTarget(Target* newTarget);
};