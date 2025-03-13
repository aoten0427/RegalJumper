// ================================================================ 
// ファイル名 : Animation.h
// 作成者 : 景山碧天
// 説明 :  位置と回転を変化させるアニメーション
// ================================================================

#pragma once


class Object;
class Sequence;

class Animation
{
public:
	//ポジションアニメーションのアクティブセット
	void SetPositionActive(bool active) { m_changePosition.first = active; }
	//回転アニメーションのアクティブセット
	void SetRotateActive(bool active) { m_changeRotate.first = active; }
private:
	//保持者
	Object* m_holder;
	//ポジション情報
	std::pair<bool, DirectX::SimpleMath::Vector3> m_changePosition;
	Sequence* m_positionSequence;
	//回転情報
	std::pair<bool, DirectX::SimpleMath::Quaternion> m_changeRotate;
	Sequence* m_rotateSequence;
public:
	//コンストラクタ
	Animation(Object* holder);
	//デストラクタ
	~Animation() = default;
	//アニメーションアップデート
	void AnimationUpdate();

	//ポジションアニメーション追加
	void AddPositionAnimation(DirectX::SimpleMath::Vector3 position,float speed,std::string ease,float delay);
	//ポジションループ設定
	void PositionLoop();
	//回転アニメーション追加
	void AddRotateAnimation(DirectX::SimpleMath::Quaternion rotate, float speed, std::string ease, float delay);
	//回転ループ設定
	void RotateLoop();
	//開始
	void Play();
	//終了
	void End();
};