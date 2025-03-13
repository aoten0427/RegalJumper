#include"pch.h"
#include"TestObject2.h"
#include"Base/Base.h"
#include"Base/CommonManager/RenderManager.h"
#include"Base/Resource/ShaderManager.h"

TestObject2::TestObject2(Scene* scene) :Object(scene)
{
	using namespace DirectX::SimpleMath;

	m_model = AddComponent<Model3D>(this, "Box");
	m_model->SetRender(std::bind(&TestObject2::ModelRender, this, std::placeholders::_1));

	/*GetTransform()->Translate(Vector3(0, -5, -5));*/
	GetTransform()->TransScale(Vector3(3, 3, 3));

	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_set.vertexShader = ShaderManager::CreateVSShader(device, "BoxVS.cso");
	m_set.pixelShader = ShaderManager::CreatePSShader(device, "BoxPS.cso");
	m_set.inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "BoxVS.cso");
	m_set.cBuffer = ShaderManager::CreateConstantBuffer<PlayerPosition>(device);
	
	/*D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	DX::ThrowIfFailed(
		device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	);

	cBuffer = ShaderManager::CreateConstantBuffer<cbLight>(device);*/
}

TestObject2::~TestObject2()
{
}

void TestObject2::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//Move(deltatime);

	//auto input = GetCommonResources()->GetInput();

	//if (input->IsKeyPress(DirectX::Keyboard::K))
	//{
	//	Destroy();
	//}
	//if (input->IsKeyPress(DirectX::Keyboard::L))
	//{
	//	/*seq->Play();*/
	//	//m_subject->Notify(7);
	//}

	//auto debug = GetCommonResources()->GetDebugString();
	//debug->AddString("%d", testTween);

}

void TestObject2::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	
}

void TestObject2::ModelRender(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	m_model->GetModel()->Draw(context, *states, m_model->GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(), false, [&] {
		// 定数バッファを指定する
		PlayerPosition ppos;
		ppos.Position = Vector4(0, 15, 0,0);
		context->UpdateSubresource(m_set.cBuffer.Get(), 0, NULL, &ppos, 0, 0);

		ID3D11Buffer* cbuf[] = { m_set.cBuffer.Get() };
		context->VSSetConstantBuffers(1, 1, cbuf);
		context->PSSetConstantBuffers(1, 1, cbuf);

		// シェーダを設定する
		context->VSSetShader(m_set.vertexShader.Get(), nullptr, 0);
		context->PSSetShader(m_set.pixelShader.Get(), nullptr, 0);

		context->IASetInputLayout(m_set.inputLayout.Get());

		// サンプラーステートを指定する
		ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
		context->PSSetSamplers(0, 1, sampler);
		});

}

void TestObject2::Move(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	/*using namespace DirectX::SimpleMath;

	auto input = GetCommonResources()->GetInput();

	float speed = 0.2f;

	if (input->IsKeyDown(DirectX::Keyboard::Space))
	{
		if (input->IsKeyDown(DirectX::Keyboard::A))
		{
			GetTransform()->TransRotate(Vector3::UnitY, 1);
		}
		if (input->IsKeyDown(DirectX::Keyboard::D))
		{
			GetTransform()->TransRotate(Vector3::UnitY, -1);
		}
		if (input->IsKeyDown(DirectX::Keyboard::W))
		{
			GetTransform()->TransRotate(Vector3::UnitX, 1);
		}
		if (input->IsKeyDown(DirectX::Keyboard::S))
		{
			GetTransform()->TransRotate(Vector3::UnitX, -1);
		}
		if (input->IsKeyDown(DirectX::Keyboard::Q))
		{
			GetTransform()->TransRotate(Vector3::UnitZ, 1);
		}
		if (input->IsKeyDown(DirectX::Keyboard::E))
		{
			GetTransform()->TransRotate(Vector3::UnitZ, -1);
		}
	}
	else
	{
		if (input->IsKeyDown(DirectX::Keyboard::A))
		{
			m_rigidbody->Addforce(Vector3(-speed, 0, 0));
		}
		if (input->IsKeyDown(DirectX::Keyboard::D))
		{
			m_rigidbody->Addforce(Vector3(speed, 0, 0));
		}
		if (input->IsKeyDown(DirectX::Keyboard::W))
		{
			m_rigidbody->Addforce(Vector3(0, 0, -speed));
		}
		if (input->IsKeyDown(DirectX::Keyboard::S))
		{
			m_rigidbody->Addforce(Vector3(0, 0, speed));
		}
		if (input->IsKeyDown(DirectX::Keyboard::Q))
		{
			m_rigidbody->Addforce(Vector3(0, speed, 0));
		}
		if (input->IsKeyDown(DirectX::Keyboard::E))
		{
			m_rigidbody->Addforce(Vector3(0, -speed, 0));
		}
	}*/


}

void TestObject2::Test(int i)
{
	UNREFERENCED_PARAMETER(i);
	/*auto debug = GetCommonResources()->GetDebugString();
	debug->AddString("hit");
	Destroy();*/
}
