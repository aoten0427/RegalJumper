// ================================================================ 
// ファイル名 : Animator.h
// 作成者 : 景山碧天
// 説明 :  複数のアニメーションをまとめたもの
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
	//名前
	std::string m_name;
	//読み込みファイル
	std::string m_filename;
	//アニメーション
	std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
	//管理元
	AnimatiorCenter* m_animatorCenter;
	//並列で起動するか判定
	bool m_isParallel;
public:
	//コンストラクタ
	Animator(std::string name,std::string filename = Config::NONE_FILE);
	//デストラクタ
	virtual ~Animator() = default;
	//開始
	virtual void Play();
	//アップデート
	virtual void Update(float deltatime);
	//終了
	virtual void End();
	//アニメーターセンターへのストップ通知
	void ActiveOff();
	//アニメーション作成
	void AddAnimation(std::string name, Object* object);
	//ファイルのロード
	void LoadData();
};