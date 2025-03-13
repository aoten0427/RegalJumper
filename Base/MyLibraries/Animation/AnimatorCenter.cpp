// ================================================================ 
// ファイル名 : AnimatorCcenter.h
// 作成者 : 景山碧天
// 説明 :  同一のオブジェクトを動かすアニメーターの管理を行う
// ================================================================
#include"pch.h"
#include"AnimatorCenter.h"
#include"Base/MyLibraries/Animation/Animator.h"

/// <summary>
/// コンストラクタ
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
/// アップデート
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
/// アニメーターのアクティブを切り替え
/// </summary>
/// <param name="name"></param>
/// <param name="active"></param>
void AnimatiorCenter::SetActiveAnimator(std::string name, bool active)
{
	//アニメーターがあるか判断
	if (m_animators.find(name) == m_animators.end())return;

	//アクティブ設定
	if (active)
	{
		if (m_activeAnimator.find(name) != m_activeAnimator.end())return;
		//並列判定
		bool parallel = m_animators[name]->GetIsParallel();
		//並列アニメーターでない場合アニメーターを止める
		if (!parallel)
		{
			//現在の単一アニメーターを止める
			if (m_singleAnimator.second)SetActiveAnimator(m_singleAnimator.first, false);
			//単一アニメーターを書き換える
			m_singleAnimator = { name,m_animators[name].get() };

		}
		//アクティブ設定
		m_activeAnimator[name] = m_animators[name].get();
		m_activeAnimator[name]->Play();
	}
	//非アクティブ設定
	else
	{
		if (m_activeAnimator.find(name) == m_activeAnimator.end())return;
		if (m_singleAnimator.first == name)m_singleAnimator = { "",nullptr };
		//アクティブ解除
		m_animators[name].get()->End();
		m_removeAnimator.insert(name);
	}
	
}



/// <summary>
/// アニメーター追加
/// </summary>
/// <param name="name">アニメーター名</param>
/// <param name="animator">アニメーター</param>
void AnimatiorCenter::AddAnimator(std::unique_ptr<Animator> animator)
{
	std::string name = animator.get()->GetName();
	m_animators.insert({ name,std::move(animator) });
	m_animators[name].get()->SetAnimatorCenter(this);
}

/// <summary>
/// アニメーションオブジェクト追加
/// </summary>
/// <param name="name">オブジェクト名</param>
/// <param name="object">オブジェクト</param>
void AnimatiorCenter::AddAnimationObject(std::string name, Object* object)
{
	m_animationObjects.insert({ name,object });
}

/// <summary>
/// 各アニメーターにアニメーション追加
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
/// 各アニメーターにファイルのロード指示
/// </summary>
void AnimatiorCenter::LoadAnimation()
{
	for (auto& animator : m_animators)
	{
		animator.second->LoadData();
	}
}
