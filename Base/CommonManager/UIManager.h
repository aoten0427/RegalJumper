// ================================================================ 
// ファイル名 : UIManager.h
// 作成者 : 景山碧天
// 説明 :  UIの動作管理
// ================================================================

#pragma once

class UserInterface;
class CommonResources;
class DirectXInputs;

class UIManager
{
private:
	//入力機構
	DirectXInputs* m_input;
	//管理UI
	std::vector<UserInterface*> m_userInterfaces;
public:
	//コンストラクタ
	UIManager(CommonResources* commonResources);
	//デストラクタ
	~UIManager() = default;
	//アップデート
	void Update();
	//UI追加
	void AddUserInterface(UserInterface* userinterfase);
	//UI削除
	void ReMoveUserInterface(UserInterface* userinterface);
private:
	//内部判定取得
	bool WithIn(const DirectX::SimpleMath::Vector2& pos, UserInterface* ui);
};