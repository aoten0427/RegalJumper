// ================================================================ 
// �t�@�C���� : ResultBG.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�w�i
// ================================================================

#include"pch.h"
#include"ResultBG.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/Tween/DoTween.h"
#include"Base/Sound/Sound.h"

//�S�Ă̎��i���o������܂ł̎���
constexpr float APPEARANCE_TIME = 3.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
ResultBG::ResultBG(Canvas* canvas):UserInterface(canvas,"ResultBG")
	,
	m_quads{},
	m_quadsColor{},
	m_openTime{},
	m_timer{ 0 },
	m_flag{ false }
{
	//�ʒu�A�傫����ݒ�
	SetPosition(DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y));
	SetSize(DirectX::SimpleMath::Vector2(Screen::WIDTH, Screen::HEIGHT));
	//�f�[�^�ǂݍ���
	LoadData();

	AddComponent<Sound>(this, Sound::SoundType::SE, "Result", true);
}

/// <summary>
/// �A�b�v�f�[�g �l�p�̐F�𒲐�
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void ResultBG::ObjectUpdate(float deltatime)
{
	using namespace DirectX::SimpleMath;
	//���o�̏o��
	if (m_timer < APPEARANCE_TIME)
	{
		m_timer += deltatime;
		for (int i = 0; i < m_openTime.size(); i++)
		{
			//�o�����Ԃɍ��킹�ē����x�ύX
			if (m_openTime[i] < m_timer)
			{
				float alpha = std::min((m_timer - m_openTime[i]) * 1.6f, 1.0f);

				m_quadsColor[i].w = alpha;
			}
		}
	}
	//�����x�ύX�̃��[�v���N��
	if (m_timer > 3.0f && !m_flag)
	{
		m_flag = true;
		LoopSet();
	}
	//�F�ݒ�
	for (int i = 0; i < m_quads.size(); i++)
	{
		m_quads[i]->SetColor(m_quadsColor[i]);
	}
}

/// <summary>
/// �f�[�^�ǂݍ���
/// </summary>
void ResultBG::LoadData()
{
	//JSON�t�@�C���I��
	std::string filename = "Resources/JSON/ResultData/ResultData.json";
	//�ǂݍ���
	std::ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//���f���ǂݍ���
		size_t num = m_json["Quads"].size();

		for (int i = 0; i < num; i++)
		{
			using namespace DirectX::SimpleMath;
			//����
			m_quads.push_back(GetScene()->AddObject<UserInterface>(GetCanvas(), "ResultQuad",1));
			//�����ɃZ�b�g
			m_quads.back()->SetColor(Vector4(1, 1, 1, 0));
			//�ʒu�ƃT�C�Y����
			Vector2 position{ m_json["Quads"][i]["x"],m_json["Quads"][i]["y"] };
			Vector2 size{ m_json["Quads"][i]["width"],m_json["Quads"][i]["height"] };
			m_quads.back()->SetPosition(position);
			m_quads.back()->SetSize(size);
			//�o�����Ԃ��L�^
			m_openTime.push_back(m_json["Quads"][i]["openTime"]);
			m_quadsColor.push_back(Vector4(1, 1, 1, 0));
		}
	}

}

/// <summary>
/// ���[�v���Z�b�g
/// </summary>
void ResultBG::LoopSet()
{
	for (int i = 0; i < m_quadsColor.size(); i++)
	{
		AddComponent<Tween>(this, true)->DoVector4(m_quadsColor[i],DirectX::SimpleMath::Vector4(1, 1, 1, 0.3f), 2.0f).
			SetLoop(-1).SetDelay(m_openTime[i]);
	}
}
