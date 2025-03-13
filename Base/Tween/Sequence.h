// ================================================================ 
// �t�@�C���� : Sequence.h
// �쐬�� : �i�R�ɓV
// ���� :  Tween�𕡐��Ǘ�����
// ================================================================
#pragma once
#include"Base/Component/Component.h"

class TweenCore;

class Sequence :public Component
{

private:
	//�R�A
	std::vector<TweenCore*> m_cores;
	//���ݓ������Ă���R�A�ԍ�
	int m_activeNumber;
public:
	Sequence(Object* object);
	~Sequence();
	//Int�ǉ�
	TweenCore& AppendInt(int& origin, int end, float time);
	//float�ǉ�
	TweenCore& AppendFloat(float& origin, float end, float time);
	//Vector2�ǉ�
	TweenCore& AppendVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time);
	//Vector3�ǉ�
	TweenCore& AppendVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time);
	//Vector4�ǉ�
	TweenCore& AppendVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time);
	//Quaternion�ǉ�
	TweenCore& AppendQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time);
	
	//����
	void Kill();
	//�ĊJ
	void Play();
	//�ꎞ��~
	void Pause();
	//���[�v
	void Loop();
	//���X�^�[�g
	void ReStart();
private:
	//�ǉ����̃v���Z�X
	void AppendProcess(TweenCore* newCore);
	
};