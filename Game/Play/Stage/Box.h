// ================================================================ 
// ファイル名 : Box.h
// 作成者 : 景山碧天
// 説明 :  ステージに主に使われる箱
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Resource/ShaderManager.h"

class Model3D;
class Camera;
class Player;

class Box :public Object
{
private:
	struct PlayerPosition
	{
		DirectX::SimpleMath::Vector4 Position;
	};
public:
	//タグ取得
	ObjectTag GetTag() { return ObjectTag::Stage; };
private:
	Model3D* m_model;

	ShaderSet m_set;

	Player* m_player;

	//	テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_modelTexture;
public:
	//コンストラクタ
	Box(Scene* scene, Player* m_player);
	Box(Scene* scene);
	//デストラクタ
	~Box() override = default;
	void Render(const Camera& camera);
private:
	void Initialize();
};
