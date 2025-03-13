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

class Box :public Object
{
public:
	//タグ取得
	ObjectTag GetTag() { return ObjectTag::Stage; };
private:
	Model3D* m_model;

	ShaderSet m_set;
public:
	//コンストラクタ
	Box(Scene* scene);
	//デストラクタ
	~Box() override = default;

	void Render(const Camera& camera);
};
