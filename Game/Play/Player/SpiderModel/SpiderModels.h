// ================================================================ 
// ファイル名 : SpiderModel.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛のモデルを管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"

class Camera;
class SpiderModelParts;
class SpiderModelStateMachine;
class SpiderAnimatorCenter;

class SpiderModels:public Object
{
public:
	//ライト情報
	struct CBLight
	{
		DirectX::SimpleMath::Vector4 LightPosition;         // 光源の位置
		DirectX::SimpleMath::Vector4 CameraPosition;	    // カメラの位置
		float Diffuse;									    // 拡散反射係数
		float Ambient;							            // 環境光係数
		float Specular;							            // 鏡面反射係数
		float Roughness;							        // 粗さ
		DirectX::SimpleMath::Vector4 DiffuseColor;		    // 拡散反射色
		DirectX::SimpleMath::Vector4 SpecularColor;	        // 鏡面反射色
		float complex_refractive_index;				        // 屈折率
		float bonus[3];
	};
public:
	//全てのパーツを渡す
	std::vector<SpiderModelParts*>& GetModelParts() { return m_parts; }
	//ライトデータを渡す
	CBLight& GetLightData() { return m_lightdata; }
	//アニメーターを返す
	SpiderAnimatorCenter* GetAnimator()const { return m_animation.get(); }
	//ホルダーを返す
	Object* GetHolder() { return m_holder; }
private:
	Object* m_holder;
	//パーツ全体
	std::vector<SpiderModelParts*> m_parts;
	//各パーツ
	SpiderModelParts* m_body;
	SpiderModelParts* m_head;
	std::vector<SpiderModelParts*> m_legs;
	//ステートマシン
	std::unique_ptr<SpiderModelStateMachine> m_machine;
	//ライティング情報
	CBLight m_lightdata;
	//アニメーションクラス
	std::unique_ptr<SpiderAnimatorCenter> m_animation;
public:
	//コンストラクタ
	SpiderModels(Scene* scene,Object* holder = nullptr);
	//デストラクタ
	~SpiderModels()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//描画
	void Render(const Camera& camera);
	//状態変化
	void ChangeState(SpiderModelState::RenderType state);
private:
	//データ読み込み
	void LoadData();
};