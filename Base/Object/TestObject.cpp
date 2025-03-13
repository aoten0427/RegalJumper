#include"pch.h"
#include"TestObject.h"
#include"Base/Base.h"
#include"Base/Camera/Camera.h"
#include"Base/Resource/GameResources.h"
#include"MyLib/DebugString.h"

#include"Base/Tween/Tween.h"
#include"Base/Tween/Sequence.h"
#include"Base/Tween/TweenCore.h"

#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Thread.h"

#include"Base/MyLibraries/Animation/Animator.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/CommonManager/ShadowMapManager.h"

#include"Base/Canvas/UserInterface/UserInterface.h"
TestObject::TestObject(Scene* scene):Object(scene)
	,
	m_pos{}
{
	using namespace DirectX::SimpleMath;

	GetScene()->ChangeState(Scene::State::PLAY);

	///*AddComponent<Rigidbody>(this);*/
	m_player = AddComponent<Model3D>(this, "SpiderHead");
	m_player->SetRender(std::bind(&TestObject::ModelRender, this, std::placeholders::_1));
	//m_box = AddComponent<Model3D>(this, "Box2");
	//m_box->SetPosition(Vector3(0, -8, 0));
	//m_box->SetScale(Vector3(6, 6, 6));
	//m_box->SetRender(std::bind(&TestObject::ModelRender, this, std::placeholders::_1));

	//auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	//m_shadowMap.vertexShader = ShaderManager::CreateVSShader(device, "ShadowMapVS.cso");
	//m_shadowMap.pixelShader = ShaderManager::CreatePSShader(device, "ShadowMapPS.cso");

	//m_shadowDraw.vertexShader = ShaderManager::CreateVSShader(device, "ShadowDrawVS.cso");
	//m_shadowDraw.pixelShader = ShaderManager::CreatePSShader(device, "ShadowDrawPS.cso");
	//m_shadowDraw.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "ShadowDrawVS.cso");

	//m_shadowMap.cBuffer = ShaderManager::CreateConstantBuffer<cbLight>(device);
	//


	//// シャドウマップの大きさを指定する
	//const RECT rectShadow = { 0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE };

	//// レンダーテクスチャを作成する
	//m_shadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	//m_shadowMapRT->SetDevice(device);
	//m_shadowMapRT->SetWindow(rectShadow);

	//// 深度ステンシルを作成する
	//m_shadowMapDS = std::make_unique<mylib::DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	//m_shadowMapDS->SetDevice(device);
	//m_shadowMapDS->SetWindow(rectShadow);


	//m_depth = std::make_unique<DepthResources>(device, SHADOWMAP_SIZE);

	//// シャドウマップ用のサンプラーを作成する
	//D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	//samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	//samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
	//DX::ThrowIfFailed(
	//	device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	//);



	//float t = 100;
	//// ライトの座標
	//m_lightPosition = Vector3(t, t, 0.0f);
	

	
	for (int i = 0; i < 6; i++)
	{
		m_mainSphere.push_back(AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr, true, 0.5f));
	}

	for (int i = 0; i < 61; i++)
	{
		m_subSphere.push_back(AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr, true, 0.2f));
	}
}

TestObject::~TestObject()
{
}

void TestObject::ObjectUpdate(float deltatime)
{
	/*Move(deltatime);*/

	/*m_ui->SetPosition(m_pos);*/
}

void TestObject::OnCollision(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	auto debug = GetCommonResources()->GetDebugString();
	debug->AddString("hit");
}

void TestObject::PushBack(DirectX::SimpleMath::Vector3 pushback)
{
	GetTransform()->Translate(pushback);
}

//void TestObject::Move(float deltatime)
//{
//	UNREFERENCED_PARAMETER(deltatime);
//	using namespace DirectX::SimpleMath;
//
//	auto input = GetCommonResources()->GetInput();
//
//	float speed = 0.2f;
//
//	if (input->IsKeyDown(DirectX::Keyboard::Space))
//	{
//		if (input->IsKeyDown(DirectX::Keyboard::A))
//		{
//			GetTransform()->TransRotate(Vector3::UnitY, 1);
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::D))
//		{
//			GetTransform()->TransRotate(Vector3::UnitY, -1);
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::W))
//		{
//			GetTransform()->TransRotate(Vector3::UnitX, 1);
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::S))
//		{
//			GetTransform()->TransRotate(Vector3::UnitX, -1);
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::Q))
//		{
//			GetTransform()->TransRotate(Vector3::UnitZ, 1);
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::E))
//		{
//			GetTransform()->TransRotate(Vector3::UnitZ, -1);
//		}
//	}
//	else
//	{
//		if (input->IsKeyDown(DirectX::Keyboard::A))
//		{
//			m_rigidbody->AddForce(Vector3(-speed, 0, 0));
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::D))
//		{
//			m_rigidbody->AddForce(Vector3(speed, 0, 0));
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::W))
//		{
//			m_rigidbody->AddForce(Vector3(0, 0, -speed));
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::S))
//		{
//			m_rigidbody->AddForce(Vector3(0, 0, speed));
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::Q))
//		{
//			m_rigidbody->AddForce(Vector3(0, speed, 0));
//		}
//		if (input->IsKeyDown(DirectX::Keyboard::E))
//		{
//			m_rigidbody->AddForce(Vector3(0, -speed, 0));
//		}
//	}
//
//	
//}

void TestObject::Test(int i)
{
	UNREFERENCED_PARAMETER(i);
	auto debug = GetCommonResources()->GetDebugString();
	debug->AddString("hit");
}



std::vector<float> TestObject::ClampedKnotVector(int p, int n)
{
	int m = p + n + 1;
	std::vector<float> u(m);

	// 最初の n+1 個のノットを 0 に固定
	for (int i = 0; i <= n; ++i) {
		u[i] = 0.0;
	}

	// 中間のノットを均等に配置
	for (int i = 1; i < p - n; ++i) {
		u[n + i] = (float)i / (p - n);
	}

	// 最後の n+1 個のノットを 1 に固定
	for (int i = m - n - 1; i < m; ++i) {
		u[i] = 1.0;
	}

	return u;
}

float TestObject::BasisFunction(const std::vector<float>& u, int j, int k, float t, std::vector<std::vector<float>>& memo)
{
	// メモにある場合は再利用
	if (memo[j][k] != -1.0) return memo[j][k];

	double result;
	if (k == 0) {
		result = (u[j] <= t && t < u[j + 1]) ? 1.0 : 0.0;
	}
	else {
		double w1 = 0.0, w2 = 0.0;
		if ((u[j + k] - u[j]) != 0.0) {
			w1 = ((t - u[j]) / (u[j + k] - u[j])) * BasisFunction(u, j, k - 1, t, memo);
		}
		if ((u[j + k + 1] - u[j + 1]) != 0.0) {
			w2 = ((u[j + k + 1] - t) / (u[j + k + 1] - u[j + 1])) * BasisFunction(u, j + 1, k - 1, t, memo);
		}
		result = w1 + w2;
	}

	memo[j][k] = result;
	return result;
}



std::vector<DirectX::SimpleMath::Vector3> TestObject::ComputeBSplineCurve(const std::vector<DirectX::SimpleMath::Vector3>& P, int n,float step)
{
	int p = P.size();          // 制御点の数
	std::vector<float> u = { 0,0,0,0,1,2,3,3,3,3 };
	std::vector<DirectX::SimpleMath::Vector3> S; // 計算されたスプライン曲線
	S.reserve(static_cast<size_t>((u[p] - u[n]) / step) + 1); // メモリ事前確保

	// t の範囲を u[n] から u[p] に
	for (float t = u[n]; t <= u[p]; t += step) {
		DirectX::SimpleMath::Vector3 point = { 0.0f, 0.0f, 0.0f };

		// 各制御点tでのメモ化テーブルを初期化
		std::vector<std::vector<float>> memo(p, std::vector<float>(n + 1, -1.0));

		for (int j = 0; j < p; ++j) {
			float b = BasisFunction(u, j, n, t, memo);
			if (b > 0.0001) { // 微小値の制限
				point = point + P[j] * static_cast<float>(b);
			}
		}
		S.push_back(point);
	}
	return S;
}

void TestObject::ModelRender(const Camera& camera)
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();


	//std::vector<Vector3> controlPoints = {
	//	 {0.0, 0.0, 0.0},
	//	{1.0, 2.0, 1.0},
	//	{3.0, 2.0, -1.0},
	//	{3.0, 0.0, 0.0},
	//	{5.0, 2.0, 2.0},
	//	{6.0, 0.0, -1.0}
	//};

	//int degree = 3; // 3次Bスプライン
	//

	//for (int i = 0; i < m_mainSphere.size(); i++)
	//{
	//	m_mainSphere[i]->SetPosition(controlPoints[i]);
	//}

	//std::vector<DirectX::SimpleMath::Vector3> curve = ComputeBSplineCurve(controlPoints, degree,0.05f);

	//for (int i = 0; i < m_subSphere.size(); i++)
	//{
	//	float t = 0.1f * i;
	//	Vector3 p = curve[i];
	//	m_subSphere[i]->SetPosition(p);
	//}

	/*cout << "B-Spline Curve Points (3D):\n";
	for (double t = 0; t <= 3.0; t += 0.1) {
		Vec3 p = BSplinePoint(t, degree, controlPoints, knots);
		cout << "(" << p.x << ", " << p.y << ", " << p.z << ")\n";
	}*/

	auto resorce = GetScene()->GetRenderManager()->GetShadowData();


	Matrix world = m_box->GetWorldMatrix();
	m_box->GetModel()->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&]
		{
			// 定数バッファを指定する
			ID3D11Buffer* cbuf[] = { m_shadowMap.cBuffer.Get() };
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// シェーダを設定する
			context->VSSetShader(m_shadowDraw.vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_shadowDraw.pixelShader.Get(), nullptr, 0);

			context->IASetInputLayout(m_shadowDraw.inputLayout.Get());

			// サンプラーステートを指定する
			ID3D11SamplerState* sampler[] = { states->PointWrap(), m_shadowMapSampler.Get() };
			context->PSSetSamplers(0, 2, sampler);

			// 作成した深度マップをシェーダリソースとして設定する
			context->PSSetShaderResources(1, 1, &resorce->m_shaderResourcesView);	// register(t1)に&srvをバインド

			context->VSSetConstantBuffers(1, 1, &resorce->m_cbuff);
			context->PSSetConstantBuffers(1, 1, &resorce->m_cbuff);
		}
	);

	
}
