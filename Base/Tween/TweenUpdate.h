// ================================================================ 
// ファイル名 : TweenUpdate.h
// 作成者 : 景山碧天
// 説明 :  データ型に応じたTweenの処理を行う
// ================================================================

#pragma once
#include"ITweenUpdate.h"


template<typename DataType>
class TweenUpdate :public ITweenUpdate
{
private:
	//変化する値のアドレス
	DataType* m_origin;
	//初期値
	DataType m_startValue;
	//終了値
	DataType m_endValue;
	//変化値
	DataType m_changeValue;
	//変化割合(0～1)
	float m_ratio;
	//変化時間
	float m_targetTime;
	//イージングタイプ
	Easing::Ease m_easeType;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="origin">変更データ</param>
	/// <param name="end">最終値</param>
	/// <param name="time">変化時間</param>
	TweenUpdate(DataType& origin, DataType end, float time)
		:
		m_origin{&origin},
		m_startValue{origin},
		m_endValue{end},
		m_changeValue{},
		m_ratio{0},
		m_targetTime{ time },
		m_easeType{Easing::Ease::Normal}
	{
		//変化量を計算
		m_changeValue = m_endValue - m_startValue;
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TweenUpdate()
	{
		m_origin = nullptr;
	}

	//変化アドレスの確認
	bool IsSurvival() { return m_origin; }

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltatime">フレーム経過時間</param>
	/// <returns>変化終了か</returns>
	bool Update(float deltatime)override
	{
		//中身確認
		if (!IsSurvival())return false;
		//目的時間に合わせて割合を加算
		m_ratio += deltatime / m_targetTime;
		//1を超えた場合戻す
		if (m_ratio >= 1)m_ratio = 1;
		//値変換
		*m_origin = static_cast<DataType>(m_startValue + m_changeValue * Easing::Selection(m_easeType, m_ratio));
		//m_ratioが1の場合(変化が終わった)場合trueを返す
		if (m_ratio >= 1)return true;
		return false;
	}

	//イージング種類設定
	void SetEase(const Easing::Ease& ease)override { m_easeType = ease; }
	//値変更(巻き戻り)
	void Yoyo()override
	{
		if (!IsSurvival())return;
		//初期値と終了値を入れ替え
		std::swap(m_startValue, m_endValue);
		//変化値を設定
		m_changeValue = m_endValue - m_startValue;
		//割合0に
		m_ratio = 0;
	}
	//値変更(初期設定)
	void ReStart()override
	{
		if (!IsSurvival())return;
		//割合を0に
		m_ratio = 0;
	}
	//値変更(加算)
	void Incremental()override
	{
		if (!IsSurvival())return;
		//初期値、終了値に変化値を加算
		m_startValue += m_changeValue;
		m_endValue += m_changeValue;
		//割合を0に
		m_ratio = 0;
	}
	//処理処理
	void Kill()override
	{
		if (!IsSurvival())return;
		//割合を1に
		m_ratio = 1;
		//値を終了値に変更
		*m_origin = m_endValue;
	}
	//相対値に変更
	void Relative()
	{
		if (!IsSurvival())return;
		//変化値を終了値に変更
		if (m_ratio != 0)return;
		m_changeValue = m_endValue;
		m_endValue = *m_origin + m_changeValue;
		m_startValue = *m_origin;
	}
	//終点は変えずに初期値変更
	void ReLoad()override
	{
		if (!IsSurvival())return;
		m_startValue = *m_origin;
		m_changeValue = m_endValue - m_startValue;
	}
};


