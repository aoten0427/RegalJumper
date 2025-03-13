// ================================================================ 
// ファイル名 : Model3D.cpp
// 作成者 : 景山碧天
// 説明 :  モデル描画を行う
// ================================================================

#include"pch.h"
#include"Model3D.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Resource/GameResources.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/Object/Object.h"
#include"Base/Camera/Camera.h"
#include"Base/Component/Transform/Transform.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="modelname">読み込みモデル名</param>
/// <param name="renderOrder">描画準</param>
Model3D::Model3D(Object* object, std::string modelname, int renderOrder):Component(object)
	,
	m_renderOrder(renderOrder),
	m_model{nullptr},
	m_position{DirectX::SimpleMath::Vector3::Zero},
	m_scale{DirectX::SimpleMath::Vector3::One},
	m_rotate{ DirectX::SimpleMath::Quaternion::Identity },
	m_matrix{DirectX::SimpleMath::Matrix::Identity},
	m_render{nullptr},
	m_isAfterRender{false},
	m_isShadow{true}
{
	//描画マネージャーへの登録
	object->GetScene()->GetRenderManager()->AddModel3D(this);

	//モデル名が設定されていたらロードする
	if (modelname != Config::NONE_FILE)Load(modelname);
}

/// <summary>
/// デストラクタ
/// </summary>
Model3D::~Model3D()
{
	//描画マネージャーから削除
	GetObject()->GetScene()->GetRenderManager()->RemoveModel3D(this);
}

/// <summary>
/// モデル読み込み
/// </summary>
/// <param name="name">モデル名</param>
void Model3D::Load(std::string name)
{
	m_model = GameResources::GetInstance()->GetModel(name);
}

/// <summary>
/// ワールドmatrix取得
/// </summary>
/// <returns>ワールド行列</returns>
DirectX::SimpleMath::Matrix Model3D::GetWorldMatrix()
{
	return m_matrix * GetObject()->GetTransform()->GetWorldMatrix();
}


/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void Model3D::Render(const Camera& camera)
{
	
	if (m_render)
	{
		m_render(camera);
	}
	else if(m_model != nullptr)
	{
		auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
		auto states = GetCommonResources()->GetCommonStates();
		m_model->Draw(context, *states,GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
	
}

/// <summary>
/// 描画順変更
/// </summary>
/// <param name="renderOrder">優先度</param>
void Model3D::ChangeRenderOrder(int renderOrder)
{
	m_renderOrder = renderOrder;
}

/// <summary>
/// ポジションセット
/// </summary>
/// <param name="position">位置</param>
void Model3D::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	m_position = position;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// スケールセット
/// </summary>
/// <param name="scale">スケール</param>
void Model3D::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	m_scale = scale;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// 回転セット
/// </summary>
/// <param name="rotate">回転</param>
void Model3D::SetRotate(DirectX::SimpleMath::Quaternion roteto)
{
	m_rotate = roteto;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// 個別描画セット
/// </summary>
/// <param name="render">個別描画</param>
void Model3D::SetRender(std::function<void(const Camera&)> render)
{
	m_render = render;
}

/// <summary>
/// シーン切り替えイベント
/// </summary>
/// <param name="scene">変更シーン</param>
void Model3D::LoadScene(Scene* scene)
{
	//描画マネージャーへの登録
	scene->GetRenderManager()->AddModel3D(this);
}
