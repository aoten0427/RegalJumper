// ================================================================ 
// �t�@�C���� : Tween.h
// �쐬�� : �i�R�ɓV
// ���� :  Tween���������߂̃N���X
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class TweenCore;

class Tween :public Component
{
private:
	//Tween�{��
	TweenCore* m_core;
	//�ė��p�t���O
	bool m_reuse;
public:
	//�R���X�g���N�^
	Tween(Object* object,bool reuse = false);
	//�f�X�g���N�^
	~Tween();
	//�A�b�v�f�[�g
	void Update(float deltatime)override;
	//Int����
	TweenCore& DoInt(int& origin, int end, float time);
	//float����
	TweenCore& DoFloat(float& origin, float end, float time);
	//Vector2����
	TweenCore& DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time);
	//Vector3����
	TweenCore& DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time);
	//Vector4����
	TweenCore& DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time);
	//Quaternion����
	TweenCore& DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time);

	//����
	void Kill();
	//�ꎞ��~
	void Pause();
	//�ĊJ
	void Play();
};
