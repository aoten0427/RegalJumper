// ================================================================ 
// �t�@�C���� : Animation.h
// �쐬�� : �i�R�ɓV
// ���� :  �ʒu�Ɖ�]��ω�������A�j���[�V����
// ================================================================

#pragma once


class Object;
class Sequence;

class Animation
{
public:
	//�|�W�V�����A�j���[�V�����̃A�N�e�B�u�Z�b�g
	void SetPositionActive(bool active) { m_changePosition.first = active; }
	//��]�A�j���[�V�����̃A�N�e�B�u�Z�b�g
	void SetRotateActive(bool active) { m_changeRotate.first = active; }
private:
	//�ێ���
	Object* m_holder;
	//�|�W�V�������
	std::pair<bool, DirectX::SimpleMath::Vector3> m_changePosition;
	Sequence* m_positionSequence;
	//��]���
	std::pair<bool, DirectX::SimpleMath::Quaternion> m_changeRotate;
	Sequence* m_rotateSequence;
public:
	//�R���X�g���N�^
	Animation(Object* holder);
	//�f�X�g���N�^
	~Animation() = default;
	//�A�j���[�V�����A�b�v�f�[�g
	void AnimationUpdate();

	//�|�W�V�����A�j���[�V�����ǉ�
	void AddPositionAnimation(DirectX::SimpleMath::Vector3 position,float speed,std::string ease,float delay);
	//�|�W�V�������[�v�ݒ�
	void PositionLoop();
	//��]�A�j���[�V�����ǉ�
	void AddRotateAnimation(DirectX::SimpleMath::Quaternion rotate, float speed, std::string ease, float delay);
	//��]���[�v�ݒ�
	void RotateLoop();
	//�J�n
	void Play();
	//�I��
	void End();
};