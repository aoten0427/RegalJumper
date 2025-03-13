// ================================================================ 
// �t�@�C���� : TweenManager.h
// �쐬�� : �i�R�ɓV
// ���� :  Tween�Ǘ�
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"

class Tween;
class Sequence;
class TweenCore;
class Sequence;

class TweenManager:public Singleton<TweenManager>
{
	friend class Singleton<TweenManager>;
private:
	TweenManager();
private:
	//tween�{��
	std::vector<std::unique_ptr<TweenCore>> m_tweens;
	//Core�j��t���O
	bool m_isCoreDestroy;
public:
	~TweenManager();
	//Tween����̍쐬�˗�
	TweenCore* AddTween(const Tween& tween);
	//Sequence����̍쐬�˗�
	TweenCore* AddTween(const Sequence& sequence);
	//�A�b�v�f�[�g
	void Update(float deltatime);
	//�R�A�j��t���O���I����
	void CoreDestroyOn() { m_isCoreDestroy = true; }
private:
	//Tween�폜
	void RemoveTween();
};