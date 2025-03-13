// ================================================================ 
// �t�@�C���� : TweenCore.h
// �쐬�� : �i�R�ɓV
// ���� :  Tween�̎��s�{��
// ================================================================

#pragma once
#include"Easing.h"

class ITweenUpdate;

class TweenCore
{
public:
	//���[�v���
	enum class LoopType
	{
		Yoyo,
		ReStart,
		Incremental
	};

	//���
	enum class State
	{
		PAUSE,
		PLAY,
		FINISH,
		DESTROY
	};

	enum class ChangeType
	{
		Default,
		Relative,
		ReLoad,
	};
public:
	//��ԃZ�b�g
	void SetState(State state) { m_state = state; }
	//��Ԏ擾
	State GetState()const { return m_state; }
	//�֐��擾
	std::function<void()> GetFunction() { return m_function; }
	//�ė��p�t���O�Z�b�g
	void SetReuse(bool reuse) { m_reuse = reuse; }
private:
	//���
	State m_state;
	//�ω��^�C�v
	ChangeType m_changeType;
	//�A�b�v�f�[�g�@�\
	std::unique_ptr<ITweenUpdate> m_update;
	//�x������
	float m_delayTime;
	//�֐�
	std::function<void()> m_function;
	//���[�v��
	int m_loopCount;
	//���[�v�^�C�v
	LoopType m_loopType;
	//�ė��p�t���O
	bool m_reuse;
public:
	TweenCore();
	~TweenCore();

	void Update(float deltatime);

	//Int�^����
	TweenCore& DoInt(int& origin, int end, float time);
	//float�^����
	TweenCore& DoFloat(float& origin, float end, float time);
	//Vector2�^����
	TweenCore& DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time);
	//Vector3�^����
	TweenCore& DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time);
	//Vector4�^����
	TweenCore& DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time);
	//Quaternion�^����
	TweenCore& DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time);

	//�x��
	TweenCore& SetDelay(float delaytime);
	//�������ɋN��
	TweenCore& SetCompleteFunction(std::function<void()> action);
	//�C�[�W���O�ݒ�
	TweenCore& SetEase(Easing::Ease easy);
	//���[�v��ݒ�(���[�v�� -1�Ŗ���,���[�v�^�C�v)
	TweenCore& SetLoop(int count, LoopType looptype = LoopType::Yoyo);
	//�ω��^�C�v�Z�b�g
	TweenCore& SetChangeType(ChangeType type);
	//����
	void Kill();
	//�ꎞ��~
	void Pause();
	//�ĊJ
	void Play();
	//���g�̍폜
	void Destroy();
	//�ăX�^�[�g
	void ReStart();
private:
	//�֐����s
	void DoFunction();
	//���[�v����
	void Loop();
	//���ΓI�ȕω���ݒ�
	TweenCore& Relative();
	//�����l�����ݒl�Ƃ��ĕύX
	TweenCore& ReLoad();
};