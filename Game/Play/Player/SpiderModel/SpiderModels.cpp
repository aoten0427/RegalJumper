// ================================================================ 
// �t�@�C���� : SpiderModel.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w偂̃��f�����Ǘ�
// ================================================================
#include"pch.h"
#include"SpiderModels.h"
#include"Base/Base.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Game/Play/Player/SpiderModel/SpiderModelParts.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelStateMachine.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="holder">�����I�u�W�F�N�g</param>
SpiderModels::SpiderModels(Scene* scene, Object* holder):Object(scene)
	,
	m_holder{holder},
	m_parts{},
	m_head{nullptr},
	m_body{nullptr},
	m_legs{},
	m_machine{nullptr},
	m_lightdata{}
{	
	//�z���_�[��e�Ƃ��ēo�^
	if (holder)GetTransform()->SetParent(holder->GetTransform());
	//���i�f�[�^�ǂݍ���
	LoadData();
	//�`��Ɏg�����f���N���X�쐬
	Model3D* model = AddComponent<Model3D>(this);
	model->SetRender(std::bind(&SpiderModels::Render, this, std::placeholders::_1));
	model->SetIsAfterDraw(true);
	//�X�e�[�g�}�V��
	m_machine = std::make_unique<SpiderModelStateMachine>(this);
	//
	GetTransform()->Translate(DirectX::SimpleMath::Vector3(0, -0.1f, 0.8f));
	//�ړ������̖��ŉ�]������
	GetTransform()->TransRotate(DirectX::SimpleMath::Vector3::UnitY, 180.0f);
	//�A�j���[�V��������
	m_animation = std::make_unique<SpiderAnimatorCenter>(this);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void SpiderModels::ObjectUpdate(float deltatime)
{
	//�X�e�[�g�}�V���A�b�v�f�[�g
	m_machine->Update(deltatime);
	//�A�j���[�^�[�X�V
	m_animation->Update(deltatime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void SpiderModels::Render(const Camera& camera)
{
	using namespace DirectX::SimpleMath;
	//���C�g����ݒ�
	m_lightdata.LightPosition = Vector4(-200, 500, 50, 0);
	m_lightdata.CameraPosition = Vector4(camera.GetEyePosition().x, camera.GetEyePosition().y, camera.GetEyePosition().z, 0);
	m_lightdata.Ambient = 0.4f;
	m_lightdata.Diffuse = 0.4f;
	m_lightdata.Specular = 0.4f;
	m_lightdata.Roughness = 0.5f;
	m_lightdata.DiffuseColor = Vector4(1, 1, 1, 1);
	m_lightdata.SpecularColor = Vector4(0.5, 0.5, 0.5, 1);
	m_lightdata.complex_refractive_index = 5.0f;
	//�X�e�[�g�}�V���ŕ`��
	m_machine->Render(camera);
}

/// <summary>
/// ��ԕύX
/// </summary>
/// <param name="state">�ω��X�e�[�g</param>
void SpiderModels::ChangeState(SpiderModelState::RenderType state)
{
	m_machine->ChangeState(state);
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void SpiderModels::LoadData()
{
	using namespace DirectX::SimpleMath;

	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/PlayerData/ModelPosition.json";

	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//���f���ǂݍ���
		size_t num = m_json["Parts"].size();
		for (int i = 0; i < num; i++)
		{
			SpiderModelParts* product = nullptr;

			std::string name = m_json["Parts"][i]["Name"];

			Vector3 position = Vector3(m_json["Parts"][i]["Position"]["x"],
				m_json["Parts"][i]["Position"]["y"],
				m_json["Parts"][i]["Position"]["z"]);
			Vector3 scale = Vector3(m_json["Parts"][i]["Scale"]["x"],
				m_json["Parts"][i]["Scale"]["y"],
				m_json["Parts"][i]["Scale"]["z"]);
			Quaternion rotate = Quaternion(m_json["Parts"][i]["Rotate"]["x"],
				m_json["Parts"][i]["Rotate"]["y"],
				m_json["Parts"][i]["Rotate"]["z"],
				m_json["Parts"][i]["Rotate"]["w"]);
			//���̐���
			if (m_json["Parts"][i]["Type"] == "Body")
			{
				m_body = GetScene()->AddObject<SpiderModelParts>(GetScene(), name, "SpiderBody", "SpiderBody");
				product = m_body;
			}
			//�琶��
			if (m_json["Parts"][i]["Type"] == "Head")
			{
				m_head = GetScene()->AddObject<SpiderModelParts>(GetScene(), name, "SpiderHead", "SpiderHead");
				product = m_head;
			}
			//������
			if (m_json["Parts"][i]["Type"] == "Leg")
			{
				m_legs.push_back(GetScene()->AddObject<SpiderModelParts>(GetScene(), name, m_json["Parts"][i]["Model"], m_json["Parts"][i]["Texture"]));
				product = m_legs.back();
			}

			//�����Z�b�g
			product->GetTransform()->Translate(position);
			product->GetTransform()->SetScale(scale);
			product->GetComponent<Model3D>()->SetRotate(rotate);
			//product->SetRenderData(&m_renderType, &m_timer, &m_alpha);
			product->GetTransform()->SetParent(GetTransform());
			m_parts.push_back(product);
		}
	}
}
