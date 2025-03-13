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
	// Work�ƃL�[��R�Â���R���e�i
	std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> m_workToButton;
	std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> m_workToAxises;
public:
	InputCollector(std::string name);
	~InputCollector() = default;

	// �{�^�����[�N��ǉ�����
	void AddButtonWork(std::string work);
	// �{�^�����[�N�Ƀ{�^����ǉ�����
	void AddButtonToButtonWork(std::string work, std::string device, std::string button);
	// �{�^�����[�N���폜
	void RemoveButtonWork(std::string work);
	// �{�^�����[�N����{�^�����폜
	void RemoveButtonFromButtonWork(std::string work, std::string device, std::string button);
	// �S�Ẵ{�^�����[�N���擾
	const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& GetAllButtonWork();

	// �����[�N��ǉ�����
	void AddAxisWork(std::string work);
	// �����[�N�Ɏ���ǉ�����
	void AddAxisToAxisWork(std::string work, std::string device, std::string axis);
	// �����[�N���폜
	void RemoveAxisWork(std::string work);
	// �����[�N���玲���폜
	void RemoveAxisFromAxisWork(std::string work, std::string device, std::string axis);
	// �S�Ă̎����[�N���擾
	const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& GetAllAxisWork();
};