#include"pch.h"
#include"PlayerParameter.h"


void PlayerParameter::LoadData()
{
	//JSONファイル選択
	std::string filename = "Resources/JSON/Parameter/PlayerParameter.json";

	//読み込み
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		m_parameter.MASS = m_json["MASS"];
		m_parameter.COLLIDER_SIZE = GetVector3(m_json, "COLLIDER_SIZE");
		m_parameter.INITIAL_POSITION = GetVector3(m_json, "INITIAL_POSITION");
		m_parameter.GRAVITY_GROUND = m_json["GRAVITY_GROUND"];
		m_parameter.GRAVITY_AIR = m_json["GRAVITY_AIR"];
		m_parameter.GRAVITY_THREAD = m_json["GRAVITY_THREAD"];
		m_parameter.SPEED_GROUND = m_json["SPEED_GROUND"];
		m_parameter.SPEED_AIR = m_json["SPEED_AIR"];
		m_parameter.SPEED_THREAD = m_json["SPEED_THREAD"];
		m_parameter.FRECTION_GROUND = m_json["FRECTION_GROUND"];
		m_parameter.FRECTION_AIR = m_json["FRECTION_AIR"];
		m_parameter.FRECTION_THREAD = m_json["FRECTION_THREAD"];
		m_parameter.JUMP_POWER = m_json["JUMP_POWER"];
		m_parameter.RESET_HEIGHT = m_json["RESET_HEIGHT"];
		m_parameter.SEARCH_RANGE = m_json["SEAECH_RANGE"];
		m_parameter.SEARCH_VISION = m_json["SEAECH_VISION"];

		ifs.close();
	}
}

const PlayerParameter::Parameter* PlayerParameter::PARAMETER()
{
	return &GetInstance()->m_parameter;
}
