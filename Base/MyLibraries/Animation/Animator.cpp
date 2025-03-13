// ================================================================ 
// �t�@�C���� : Animator.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �����̃A�j���[�V�������܂Ƃ߂�����
// ================================================================
#include"pch.h"
#include"Animator.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include"Base/MyLibraries/Animation/AnimatorCenter.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Animator::Animator(std::string name,std::string filename)
	:
	m_name{name},
	m_filename{filename},
	m_animations{},
	m_animatorCenter{nullptr},
	m_isParallel{false}
{

}

/// <summary>
/// �J�n����
/// </summary>
void Animator::Play()
{
	for (auto& animation : m_animations)
	{
		animation.second->Play();
	}
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
void Animator::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	for (auto& animation : m_animations)
	{
		animation.second->AnimationUpdate();
	}
}

/// <summary>
/// �I������
/// </summary>
void Animator::End()
{
	for (auto& animation : m_animations)
	{
		animation.second->End();
	}
}

/// <summary>
/// �A�N�e�B�u���I�t�ɂ���
/// </summary>
void Animator::ActiveOff()
{
	if (m_animatorCenter)m_animatorCenter->SetActiveAnimator(m_name,false);
}

/// <summary>
/// �A�j���[�V�����ǉ�
/// </summary>
/// <param name="name">�ǉ��A�j���[�V������</param>
/// <param name="object">�ω�����I�u�W�F�N�g</param>
void Animator::AddAnimation(std::string name, Object* object)
{
	//�A�j���[�V�����쐬
	m_animations.insert({ name,std::make_unique<Animation>(object) });
}

/// <summary>
/// �t�@�C���̃��[�h
/// </summary>
/// <param name="fileName">�ǂݍ��݃t�@�C����</param>
void Animator::LoadData()
{
	if (m_filename == Config::NONE_FILE)return;
	//�ǂݍ���
	std::ifstream ifs(m_filename.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;
		//���O�擾
		m_name = m_json["Name"];

		for (auto itr = m_json["Data"].begin(); itr != m_json["Data"].end(); itr++)
		{
			//�A�j���[�V��������
			auto animation = m_animations.find(itr.key());
			if (animation == m_animations.end())continue;

			//�|�W�V�����A�j���[�V�����ǉ�
			size_t num = itr.value()["Position"].size();
			for (size_t i = 0; i < num; i++)
			{
				auto& PosData = itr.value()["Position"][i];
				//�ύX�ʒu
				DirectX::SimpleMath::Vector3 pos{ PosData["Pos"]["x"],PosData["Pos"]["y"],PosData["Pos"]["z"] };
				//�ύX�X�s�[�h
				float speed = PosData["Speed"];
				//Easing
				std::string ease = PosData["Ease"];
				//�x��
				float delay = PosData["Delay"];
				//�A�j���[�V�����ǉ�
				animation->second->AddPositionAnimation(pos, speed, ease, delay);
			}
			//�|�W�V�������[�v�ݒ�
			if (itr.value()["PositionLoop"])animation->second->PositionLoop();

			//��]�A�j���[�V�����ǉ�
			num = itr.value()["Rotate"].size();
			for (size_t i = 0; i < num; i++)
			{
				auto& RotaData = itr.value()["Rotate"][i];
				//�ύX���]
				DirectX::SimpleMath::Quaternion rota{ RotaData["Rota"]["x"],RotaData["Rota"]["y"],RotaData["Rota"]["z"],RotaData["Rota"]["w"] };
				//�ύX�X�s�[�h
				float speed = RotaData["Speed"];
				//Easing
				std::string ease = RotaData["Ease"];
				//�x��
				float delay = RotaData["Delay"];
				//�A�j���[�V�����ǉ�
				animation->second->AddRotateAnimation(rota, speed, ease, delay);
			}
			//��]���[�v�ݒ�
			if (itr.value()["RotateLoop"])animation->second->RotateLoop();
		}
	}

}
