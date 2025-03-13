#include"pch.h"
#include"ThreadParameter.h"

void ThreadParameter::LoadData()
{
	//JSONファイル選択
	std::string filename = "Resources/JSON/Parameter/ThreadParameter.json";

	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		m_parameter.INITIAL_POWER = m_json["INITIAL_POWER"];
		m_parameter.INITIAL_POWER_TIP = m_json["INITIAL_POWER_TIP"];
		m_parameter.EXTEND_SPEED = m_json["EXTEND_SPEED"];
		m_parameter.DELETE_TIME = m_json["DELETE_TIME"];
		m_parameter.ADD_POWER = m_json["ADD_POWER"];
		m_parameter.SHRINK_VALUE_BEGIN = m_json["SHRINK_VALUE_BEGIN"];
		m_parameter.SHRINK_VALUE_END = m_json["SHRINK_VALUE_END"];
		m_parameter.SHRINK_SPEED = m_json["SHRINK_SPEED"];
		m_parameter.SHRINK_EASING = m_json["SHRINK_EASING"];

		ifs.close();
	}
}

const ThreadParameter::Parameter* ThreadParameter::PARAMETER()
{
	return &GetInstance()->m_parameter;
}
