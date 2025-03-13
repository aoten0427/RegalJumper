// ================================================================ 
// ファイル名 : TweenCore.h
// 作成者 : 景山碧天
// 説明 :  Tweenの実行本体
// ================================================================

#pragma once
#include"Easing.h"

class ITweenUpdate;

class TweenCore
{
public:
	//ループ種類
	enum class LoopType
	{
		Yoyo,
		ReStart,
		Incremental
	};

	//状態
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
	//状態セット
	void SetState(State state) { m_state = state; }
	//状態取得
	State GetState()const { return m_state; }
	//関数取得
	std::function<void()> GetFunction() { return m_function; }
	//再利用フラグセット
	void SetReuse(bool reuse) { m_reuse = reuse; }
private:
	//状態
	State m_state;
	//変化タイプ
	ChangeType m_changeType;
	//アップデート機構
	std::unique_ptr<ITweenUpdate> m_update;
	//遅延時間
	float m_delayTime;
	//関数
	std::function<void()> m_function;
	//ループ回数
	int m_loopCount;
	//ループタイプ
	LoopType m_loopType;
	//再利用フラグ
	bool m_reuse;
public:
	TweenCore();
	~TweenCore();

	void Update(float deltatime);

	//Int型生成
	TweenCore& DoInt(int& origin, int end, float time);
	//float型生成
	TweenCore& DoFloat(float& origin, float end, float time);
	//Vector2型生成
	TweenCore& DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time);
	//Vector3型生成
	TweenCore& DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time);
	//Vector4型生成
	TweenCore& DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time);
	//Quaternion型生成
	TweenCore& DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time);

	//遅延
	TweenCore& SetDelay(float delaytime);
	//完了時に起動
	TweenCore& SetCompleteFunction(std::function<void()> action);
	//イージング設定
	TweenCore& SetEase(Easing::Ease easy);
	//ループを設定(ループ回数 -1で無限,ループタイプ)
	TweenCore& SetLoop(int count, LoopType looptype = LoopType::Yoyo);
	//変化タイプセット
	TweenCore& SetChangeType(ChangeType type);
	//完了
	void Kill();
	//一時停止
	void Pause();
	//再開
	void Play();
	//自身の削除
	void Destroy();
	//再スタート
	void ReStart();
private:
	//関数実行
	void DoFunction();
	//ループ処理
	void Loop();
	//相対的な変化を設定
	TweenCore& Relative();
	//初期値を現在値として変更
	TweenCore& ReLoad();
};