// ================================================================ 
// ファイル名 : SpiderModelParts.h
// 作成者 : 景山碧天
// 説明 :  スパイダーモデルの各パーツ
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"

class Model3D;
class Camera;

class SpiderModelParts :public Object
{
public:
	//名前取得
	std::string GetName()const { return m_name; }
	//モデル取得
	Model3D* GetModel() { return m_model; }
	//テクスチャ取得
	ID3D11ShaderResourceView** GetTexture() { return m_modelTexture.GetAddressOf(); }
private:
	//名前
	std::string m_name;
	//モデル
	Model3D* m_model;
	//	テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_modelTexture;
public:
	//コンストラクタ
	SpiderModelParts(Scene* scene, std::string name, std::string modelname, std::string texturename);
	//デストラクタ
	~SpiderModelParts()override = default;
};