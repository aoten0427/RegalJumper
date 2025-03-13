// ================================================================ 
// �t�@�C���� : UserInterface.cpp
// �쐬�� : �i�R�ɓV
// ���� :  UI�N���X
// ================================================================

#include"pch.h"
#include"UserInterface.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Resource/ShaderManager.h"
#include"Base/Resource/GameResources.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/UIManager.h"
#include"Base/Canvas/Canvas.h"
#include"Base/Screen.h"
#include"Base/Component/Render/PrimitiveRenderer.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�L�����o�X</param>
/// <param name="filename">�ǂݍ��݉摜</param>
/// <param name="renderorder">�D��x</param>
UserInterface::UserInterface(Canvas* canvas, std::string filename, int renderorder) :Object(canvas->GetScene())
	,
	m_canvas{canvas},
	m_render{ nullptr },
	m_CBuffer{},
	m_inputLayout{ nullptr },
	m_vertexShader{ nullptr },
	m_pixelShader{ nullptr },
	m_geometryShader{ nullptr },
	m_position{ DirectX::SimpleMath::Vector2(Screen::CENTER_X,Screen::CENTER_Y) },
	m_size{ DirectX::SimpleMath::Vector2(100,100) },
	m_color{ DirectX::SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f) },
	m_extent{ DirectX::SimpleMath::Vector2(1.0f,1.0f) },
	m_offset{ DirectX::SimpleMath::Vector2(0.5f,0.5f) },
	m_clipRange{ DirectX::SimpleMath::Vector4(0.0f,0.0f,1.0f,1.0f) },
	m_freeElement{DirectX::SimpleMath::Vector4::Zero},
	m_mouseEventFlag{ false }
{
	//�}�l�[�W���[�֓o�^
	GetScene()->GetUIManager()->AddUserInterface(this);

	//�����_���[�쐬
	m_render = AddComponent<PrimitiveRenderer>(this, filename, renderorder,true);
	m_render->SetRender(std::bind(&UserInterface::Render, this, std::placeholders::_1, std::placeholders::_2));

	//�V�F�[�_�[�ݒ�
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_inputLayout = ShaderManager::CreateInputLayout(device,NOMAL_INPUT_LAYOUT , "UIVS.cso");
	m_vertexShader = ShaderManager::CreateVSShader(device, "UIVS.cso");
	m_geometryShader = ShaderManager::CreateGSShader(device, "UIGS.cso");
	m_pixelShader = ShaderManager::CreatePSShader(device, "UIPS.cso");
	m_CBuffer = ShaderManager::CreateConstantBuffer<ConstBuffer>(device);
	//�摜�ǂݍ���
	if (filename != Config::NONE_FILE)SetTexture(filename);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UserInterface::~UserInterface()
{
	//�}�l�[�W���[����폜
	GetScene()->GetUIManager()->ReMoveUserInterface(this);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="primitiveBatch">�v���~�e�B�u�o�b�`</param>
/// <param name="camera">�J����</param>
void UserInterface::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	UNREFERENCED_PARAMETER(camera);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto state = GetCommonResources()->GetCommonStates();

	VertexPositionTexture vertex{};

	//�ݒ�̓o�^
	ConstBuffer cbuff;
	cbuff.WindowSize = Vector2(Screen::WIDTH, Screen::HEIGHT);
	cbuff.Position = Vector4(m_position.x, m_position.y, 0, 0);
	cbuff.Size = m_size;
	cbuff.Color = m_color;
	cbuff.Extent = m_extent;
	cbuff.Offset = m_offset;
	cbuff.ClipRange = m_clipRange;
	cbuff.Free = m_freeElement;
	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { state->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	�������`��w��
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(state->DepthNone(), 0);

	context->RSSetState(state->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//�`��
	primitiveBatch->Begin();
	primitiveBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	primitiveBatch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// �`�揇�ύX
/// </summary>
/// <param name="order">�D��x</param>
void UserInterface::SetRenderOrder(int order)
{
	m_render->SetRenderOrder(order);
}

/// <summary>
/// �摜�ǂݍ���
/// </summary>
/// <param name="filename">�ǂݍ��݉摜��</param>
void UserInterface::SetTexture(std::string filename)
{
	auto resources = GameResources::GetInstance();
	m_texture = resources->GetTexture(filename);
}

/// <summary>
/// ���_�V�F�[�_�Z�b�g
/// </summary>
/// <param name="filename">VS�V�F�[�_�[��</param>
void UserInterface::SetVertexShader(std::string filename)
{
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_inputLayout = ShaderManager::CreateInputLayout(device, NOMAL_INPUT_LAYOUT, filename);
	m_vertexShader = ShaderManager::CreateVSShader(device, filename);
}

/// <summary>
/// �s�N�Z���V�F�[�_�Z�b�g
/// </summary>
/// <param name="filename">PS�V�F�[�_�[��</param>
void UserInterface::SetPixelShader(std::string filename)
{
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_pixelShader = ShaderManager::CreatePSShader(device, filename);
}

/// <summary>
/// �ʕ`��Z�b�g
/// </summary>
/// <param name="render">�`���ݒ�</param>
void UserInterface::SetRender(std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> render)
{
	m_render->SetRender(render);
}

/// <summary>
/// �V�[���؂�ւ��C�x���g
/// </summary>
/// <param name="scene">�ύX�V�[��</param>
void UserInterface::LoadScene(Scene* scene)
{
	UNREFERENCED_PARAMETER(scene);
	scene->GetUIManager()->AddUserInterface(this);
	m_canvas = scene->GetCanvas();
	m_render->LoadScene(scene);
}
