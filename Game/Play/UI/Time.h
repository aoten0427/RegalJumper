// ================================================================ 
// ファイル名 : Time.h
// 作成者 : 景山碧天
// 説明 :  時間表示
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time :public UserInterface
{
public:
	//値を変更
	void SetCount(float count) { m_count = count; }
	//左端を設定
	void SetStartX(float startx) { m_startX = startx; SetView(); }
	//高さを設定
	void SetPositionY(float positiony) { m_positionY = positiony; SetView(); }
	//大きさを設定
	void SetSize(const DirectX::SimpleMath::Vector2& size) { m_size = size; SetView(); }
private:
	//時間
	float m_count;
	//数字
	UserInterface* m_numbers[6];
	//コロン
	UserInterface* m_colon;
	//ドット
	UserInterface* m_dot;
	//開始位置
	float m_startX;
	//Y座標
	float m_positionY;
	//サイズ
	DirectX::SimpleMath::Vector2 m_size;
	//値なし判定
	bool m_isNone;
public:
	//コンストラクタ
	Time(Canvas* canvas);
	//デストラクタ
	~Time()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
	//色設定
	void SetTimeColor(const DirectX::SimpleMath::Vector4 color);
	//値なしを設定
	void SetNone(bool none);
private:
	//描画位置を設定
	void SetView();
};