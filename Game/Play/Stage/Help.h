// ================================================================ 
// ファイル名 : Help.h
// 作成者 : 景山碧天
// 説明 :  ヘルプ情報
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Scene/Scene.h"

class Camera;
class PrimitiveRenderer;
class HelpInfomation;

class Help :public Object
{
public:
	ObjectTag GetTag() { return ObjectTag::Help; };
private:
	//表示関係
	PrimitiveRenderer* m_renderer;
	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//頂点
	DirectX::VertexPositionTexture m_vertexs[4];
	//接触有効フラグ
	bool m_isContactActive;
	//インフォメーション
	HelpInfomation* m_infomation;
	//
	bool m_biginFinish;
public:
	//コンストラクタ
	Help(Scene* scene, int infomationNum,bool begin = false);
	//デストラクタ
	~Help()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
	//描画
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//Trigger実行有無
	bool IsTriggerAct(Collider* collider)override;
	//Trigger処理
	void OnTrigger(Collider* collider)override;

	void BeginOpen(Scene::State current, Scene::State old);
};