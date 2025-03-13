// ================================================================ 
// �t�@�C���� : Help.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �w���v���
// ================================================================
#include"pch.h"
#include"Help.h"
#include"Base/Base.h"
#include"Base/Event/Observer.h"
#include"Game/Play/Stage/HelpInfomation.h"

constexpr float EXTENS = 4.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="infomationNum">�C���t�H���[�V�����ԍ�</param>
Help::Help(Scene* scene, int infomationNum,bool begin) :Object(scene)
,
m_isContactActive{ true },
m_biginFinish{ false }
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//�`��쐬
	m_renderer = AddComponent<PrimitiveRenderer>(this, "Help");
	m_renderer->SetRender(std::bind(&Help::Render, this, std::placeholders::_1, std::placeholders::_2));
	//���_���ݒ�
	m_vertexs[0] = VertexPositionTexture(Vector3(-EXTENS, EXTENS, 0), Vector2(0, 0));
	m_vertexs[1] = VertexPositionTexture(Vector3(-EXTENS, -EXTENS, 0), Vector2(0, 1));
	m_vertexs[2] = VertexPositionTexture(Vector3(EXTENS, -EXTENS, 0), Vector2(1, 1));
	m_vertexs[3] = VertexPositionTexture(Vector3(EXTENS, EXTENS, 0), Vector2(1, 0));

	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	// �x�[�V�b�N�G�t�F�N�g���쐬����
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetTextureEnabled(true);
	// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	//�R���C�_�[����
	AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr, false, 3.5f);
	//�C���t�H���[�V�����쐬
	m_infomation = scene->AddObject<HelpInfomation>(scene->GetCanvas(), static_cast<HelpInfomation::INFOMATION>(infomationNum));

	if (begin)
	{
		auto* obs = AddComponent<Observer<Scene::State, Scene::State>>(this);
		obs->SetFunction(std::bind(&Help::BeginOpen, this, std::placeholders::_1, std::placeholders::_2));
		obs->RegistrationSubject("SceneStateChange");
	}
	
	
	
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Help::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//��]������
	GetTransform()->TransRotate(DirectX::SimpleMath::Vector3::UnitY, 2);
	//�X�y�[�X�������ꂽ�ꍇ�C���t�H���[�V�����I������
	if (GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::Space) && m_isContactActive) {
		m_infomation->Close();
		m_biginFinish = true;
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="primitiveBatch">�v���~�e�B�u�o�b�`</param>
/// <param name="camera">�J����</param>
void Help::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	using namespace DirectX::SimpleMath;

	//�I�u�W�F�N�g��matrix�l���̒��_���쐬
	DirectX::VertexPositionTexture vertex[4];
	for (int i = 0; i < 4; i++)
	{
		vertex[i].position = Vector3::Transform(m_vertexs[i].position, GetTransform()->GetWorldMatrix());
		vertex[i].textureCoordinate = m_vertexs[i].textureCoordinate;
	}

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, sampler);

	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);// �u�����h�X�e�[�g
	context->OMSetDepthStencilState(states->DepthDefault(), 0);		// �[�x�o�b�t�@/�X�e���V���o�b�t�@
	context->RSSetState(states->CullNone());			// �J�����O
	context->IASetInputLayout(m_inputLayout.Get());

	m_basicEffect->SetView(camera.GetViewMatrix());
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());
	m_basicEffect->SetWorld(Matrix::Identity);
	m_basicEffect->SetTexture(m_renderer->GetImage());
	m_basicEffect->Apply(context);

	primitiveBatch->Begin();

	primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);

	primitiveBatch->End();
}

/// <summary>
/// Trigger���s�L�� �v���C���[�Ƃ̂ݍs��
/// </summary>
/// <param name="collider">����</param>
/// <returns>���s�L��</returns>
bool Help::IsTriggerAct(Collider* collider)
{
	using namespace DirectX::SimpleMath;
	if (collider->GetObject()->GetTag() != ObjectTag::Player)return false;
	if (!m_biginFinish)return false;
	//��苗�����ꂽ��A�N�e�B�u���I�t�ɂ���
	if (Vector3::Distance(collider->GetObject()->GetTransform()->GetPosition(), GetTransform()->GetPosition()) > 10.0f)
	{
		m_isContactActive = false;
	}
	//�A�N�e�B�u���͎��Ȃ�
	if (m_isContactActive)return false;
	return true;
}

/// <summary>
/// Trigger���� �w���v���J��
/// </summary>
/// <param name="collider">����</param>
void Help::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	//�A�N�e�B�u���I����
	m_isContactActive = true;
	//�w���v���e��\��
	m_infomation->Open();
	//�V�[�����X�g�b�v��Ԃ�
	GetScene()->ChangeState(Scene::State::STOP);
}

/// <summary>
/// �Q�[���J�n���̊J������
/// </summary>
/// <param name="current">���݂̃V�[�����</param>
/// <param name="old">�O�̃V�[�����</param>
void Help::BeginOpen(Scene::State current, Scene::State old)
{
	if (current == Scene::State::PLAY && old == Scene::State::RESERVE)
	{
		//�A�N�e�B�u���I����
		m_isContactActive = true;
		//�w���v���e��\��
		m_infomation->Open();
		//�V�[�����X�g�b�v��Ԃ�
		GetScene()->ChangeState(Scene::State::STOP);
	}
}
