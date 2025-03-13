// ================================================================ 
// ファイル名 : ParameterBase.h
// 作成者 : 景山碧天
// 説明 :  パラメータ基底クラス
// ================================================================
#pragma once
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>

template <typename T>
class ParameterBase {
public:
    //データ読み込み
    static void LOAD_DATA()
    {
        GetInstance()->LoadData();
    }

    ParameterBase(const ParameterBase&) = delete;
    ParameterBase& operator=(const ParameterBase&) = delete;
protected:
    ParameterBase() = default;
    virtual ~ParameterBase() = default;

    // インスタンス生成
    static T* GetInstance() {
        if (instance == nullptr)
        {
            instance.reset(new T());
        }
        return instance.get();
    }

private:
    //自身のインスタンス
    static std::unique_ptr<T> instance;
private:
    //派生先データ読み込み関数
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
