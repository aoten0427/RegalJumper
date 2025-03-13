#pragma  once
#include"InputData.h"

class InputCollector
{
public:
	std::string GetName()const { return m_name; }
	void SetIsActive(bool isactive) { m_isActive = isactive; };
	bool GetIsActive()const { return m_isActive; }
private:
	std::string m_name;
	bool m_isActive;
	// Workとキーを紐づけるコンテナ
	std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> m_workToButton;
	std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> m_workToAxises;
public:
	InputCollector(std::string name);
	~InputCollector() = default;

	// ボタンワークを追加する
	void AddButtonWork(std::string work);
	// ボタンワークにボタンを追加する
	void AddButtonToButtonWork(std::string work, std::string device, std::string button);
	// ボタンワークを削除
	void RemoveButtonWork(std::string work);
	// ボタンワークからボタンを削除
	void RemoveButtonFromButtonWork(std::string work, std::string device, std::string button);
	// 全てのボタンワークを取得
	const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& GetAllButtonWork();

	// 軸ワークを追加する
	void AddAxisWork(std::string work);
	// 軸ワークに軸を追加する
	void AddAxisToAxisWork(std::string work, std::string device, std::string axis);
	// 軸ワークを削除
	void RemoveAxisWork(std::string work);
	// 軸ワークから軸を削除
	void RemoveAxisFromAxisWork(std::string work, std::string device, std::string axis);
	// 全ての軸ワークを取得
	const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& GetAllAxisWork();
};