// ================================================================ 
// �t�@�C���� : StageCenter
// �쐬�� : �i�R�ɓV
// ���� :  �v���C��ʂɔz�u����I�u�W�F�N�g���Ǘ�
// ================================================================
#include"pch.h"
#include"StageCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/Component/Transform/Transform.h"
#include"Game/GameManager.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/Play/Stage/Skydome.h"
#include"Game/Play/Stage/Box.h"
#include"Game/Play/Stage/TargetBox.h"
#include"Game/Play/Stage/Goal.h"
#include"Game/Play/Stage/Help.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
StageCenter::StageCenter(Scene* scene):Object(scene)
{
	scene->AddObject<Skydome>(scene);
	LoadData();
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void StageCenter::LoadData()
{
	using namespace DirectX::SimpleMath;

	std::string stagename = GameManager::GetInstance()->GetStageName();

	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/StageData/" + stagename + ".json";
	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//�X�e�[�W�f�[�^�ǂݍ���
		size_t num = m_json["StageObject"].size();

		for (int i = 0; i < num; i++)
		{
			//���W�擾
			Vector3 position{ m_json["StageObject"][i]["position"]["x"],
			m_json["StageObject"][i]["position"]["y"] ,
			m_json["StageObject"][i]["position"]["z"] };
			//�X�P�[���擾
			Vector3 scale{ m_json["StageObject"][i]["scale"]["x"],
			m_json["StageObject"][i]["scale"]["y"] ,
			m_json["StageObject"][i]["scale"]["z"] };

			//box����
			if (m_json["StageObject"][i]["TYPE"] == "Box")
			{
				auto box = GetScene()->AddObject<Box>(GetScene());
				box->GetTransform()->SetPosition(position);
				box->GetTransform()->SetScale(scale);
			}
			//�^�[�Q�b�g�{�b�N�X����
			else if (m_json["StageObject"][i]["TYPE"] == "Target")
			{
				auto target = GetScene()->AddObject<TargetBox>(GetScene());
				target->GetTransform()->SetPosition(position);
			}
			else if (m_json["StageObject"][i]["TYPE"] == "Goal")
			{
				auto goal = GetScene()->AddObject<Goal>(GetScene());
				goal->GetTransform()->SetPosition(position);
			}
			else if (m_json["StageObject"][i]["TYPE"] == "Help")
			{
				int infomationNum = m_json["StageObject"][i]["InfomationNum"];
				bool begin = m_json["StageObject"][i]["Begin"];
				auto help = GetScene()->AddObject<Help>(GetScene(), infomationNum,begin);
				help->GetTransform()->Translate(position);
			}
		}

		ifs.close();
	}
}
