// ================================================================ 
// ファイル名 : PrimitiveRenderer.cpp
// 作成者 : 景山碧天
// 説明 :  プリミティブバッチでの描画を行う
// ================================================================
#include"pch.h"
#include"PrimitiveRenderer.h"
#include"Base/Resource/GameResources.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/Object/Object.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="filename">読み込み画像</param>
/// <param name="renderOrder">描画順</param>
/// <param name="ui">UIかの判定</param>
PrimitiveRenderer::PrimitiveRenderer(Object* object, std::string filename, int renderOrder, bool ui):Component(object)
	,
	m_renderOrder{renderOrder},
	m_isUi(ui),
	m_render{nullptr}
{
	//描画マネージャーに登録
	object->GetScene()->GetRenderManager()->AddPrimitiveRenderer(this);
	//画像読み込み
	if (filename != Config::NONE_FILE)Load(filename);
}

/// <summary>
/// デストラクタ
/// </summary>
PrimitiveRenderer::~PrimitiveRenderer()
{
	//描画マネージャーから削除
	GetObject()->GetScene()->GetRenderManager()->RemovePrimitiveRenderer(this);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="primitiveBatch">プリミティブバッチ</param>
/// <param name="camera">カメラ</param>
void PrimitiveRenderer::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	if (m_render == nullptr)return;
	m_render(primitiveBatch, camera);
}

/// <summary>
/// 画像ロード
/// </summary>
/// <param name="filename">画像名</param>
void PrimitiveRenderer::Load(std::string filename)
{
	auto resource = GameResources::GetInstance();
	m_texture = resource->GetTexture(filename);
}

/// <summary>
/// 優先度変更
/// </summary>
/// <param name="order">優先度</param>
void PrimitiveRenderer::SetRenderOrder(int order)
{
	m_renderOrder = order;
	//描画マネージャーに登録
	GetObject()->GetScene()->GetRenderManager()->ChangeRenderOrder(this);
}

/// <summary>
/// シーン切り替えイベント
/// </summary>
/// <param name="scene">変更シーン</param>
void PrimitiveRenderer::LoadScene(Scene* scene)
{
	//描画マネージャーに登録
	scene->GetRenderManager()->AddPrimitiveRenderer(this);
}
