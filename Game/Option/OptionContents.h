// ================================================================ 
// ファイル名 : OptionContents.h
// 作成者 : 景山碧天
// 説明 :  オプションでの変更内容
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class OptionContents:public Button
{
public:
	float GetPearcent() const { return m_percent; }
private:
	//操作のアクティブフラグ
	bool m_buttonActive;
	//操作項目
	UserInterface* m_contents;
	//操作項目名
	std::string m_contentsName;
	//本体バー
	UserInterface* m_mainBar;
	//割合範囲描画バー
	UserInterface* m_subBar;
	//移動割合ポイント
	UserInterface* m_point;
	//移動割合
	float m_percent;
public:
	//コンストラクタ
	OptionContents(Canvas* canvas, std::string contentsname, float initialPar = 0.5f);
	//デストラクタ
	~OptionContents() override = default;
	//アップデート
	void ObjectUpdate(float deltatime) override;
	//ポジションセット
	void SetPosition(const DirectX::SimpleMath::Vector2& position);
	//open
	void Open();
	//close
	void Close();
	//マウス感知イベント
	void MouseWithinEvent(bool within) override;
	//左マウスクリックイベント
	void LeftClickEvent(bool within) override;
};