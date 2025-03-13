// ================================================================ 
// �t�@�C���� : ParameterBase.h
// �쐬�� : �i�R�ɓV
// ���� :  �p�����[�^���N���X
// ================================================================
#pragma once
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>

template <typename T>
class ParameterBase {
public:
    //�f�[�^�ǂݍ���
    static void LOAD_DATA()
    {
        GetInstance()->LoadData();
    }

    ParameterBase(const ParameterBase&) = delete;
    ParameterBase& operator=(const ParameterBase&) = delete;
protected:
    ParameterBase() = default;
    virtual ~ParameterBase() = default;

    // �C���X�^���X����
    static T* GetInstance() {
        if (instance == nullptr)
        {
            instance.reset(new T());
        }
        return instance.get();
    }

private:
    //���g�̃C���X�^���X
    static std::unique_ptr<T> instance;
private:
    //�h����f�[�^�ǂݍ��݊֐�
    virtual void LoadData() {};
protected:
    DirectX::SimpleMath::Vector3 GetVector3(nlohmann::json& json, std::string key);
    
};

template <typename T>
std::unique_ptr<T> ParameterBase<T>::instance = nullptr;

template<typename T>
inline DirectX::SimpleMath::Vector3 ParameterBase<T>::GetVector3(nlohmann::json& json, std::string key)
{
    return DirectX::SimpleMath::Vector3(json[key]["x"], json[key]["y"], json[key]["z"]);
}
