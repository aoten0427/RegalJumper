#include"pch.h"
#include"TweenManager.h"
#include"TweenCore.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TweenManager::TweenManager()
	:
	m_tweens{},
	m_isCoreDestroy{false}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TweenManager::~TweenManager()
{
}

/// <summary>
/// TweenCore�쐬(Tween�N���X����)
/// </summary>
/// <param name="tween">�R�A����������Tween</param>
/// <returns>�ǉ��R�A</returns>
TweenCore* TweenManager::AddTween(const Tween& tween)
{
	UNREFERENCED_PARAMETER(tween);
	//�V����TweenCore�̐���
	std::unique_ptr<TweenCore> newCore = std::make_unique<TweenCore>();
	TweenCore* returnCore = newCore.get();
	m_tweens.push_back(std::move(newCore));
	return returnCore;
}

/// <summary>
/// TweenCore�쐬(Sequence�N���X����)
/// </summary>
/// <param name="tween">�R�A����������Sequence</param>
/// <returns>�ǉ��R�A</returns>
TweenCore* TweenManager::AddTween(const Sequence& sequence)
{
	UNREFERENCED_PARAMETER(sequence);
	//�V����TweenCore�̐���
	std::unique_ptr<TweenCore> newCore = std::make_unique<TweenCore>();
	TweenCore* returnCore = newCore.get();
	m_tweens.push_back(std::move(newCore));
	return returnCore;
}

/// <summary>
/// Tween�폜
/// </summary>
void TweenManager::RemoveTween()
{
	//�폜�v�����Ȃ���΃p�X
	if (!m_isCoreDestroy)return;
	//�폜�v�f���폜
	m_tweens.erase(std::remove_if(m_tweens.begin(), m_tweens.end(), [&]
	(std::unique_ptr<TweenCore>& core) {
			return core.get()->GetState() == TweenCore::State::DESTROY;
		}), m_tweens.end());
	//�폜�v�����I�t��
	m_isCoreDestroy = false;
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void TweenManager::Update(float deltatime)
{
	for (auto& tween : m_tweens)
	{
		tween->Update(deltatime);
	}
	RemoveTween();
}


