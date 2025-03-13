// ================================================================ 
// �t�@�C���� : TargetMark.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�[�Q�b�g�\���}�[�N
// ================================================================
#include"pch.h"
#include"TargetMark.h"
#include"Base/Base.h"
#include"Base/Tween/DoTween.h"

constexpr float EXTENS = 1.5f;
constexpr float CHANGE_SPEED = 0.3f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="holder">�����I�u�W�F�N�g</param>
TargetMark::TargetMark(Scene* scene, Object* holder):Object(scene)
	,
	m_size{0}
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	GetTransform()->SetParent(holder->GetTransform());

	m_renderer = AddComponent<PrimitiveRenderer>(this,"TargetMark");
	m_renderer->SetRender(std::bind(&TargetMark::Render, this, std::placeholders::_1, std::placeholders::_2));

	// �x�[�V�b�N�G�t�F�N�g���쐬����
	m_basicEffect = std::make_unique<BasicEffect>(GetCommonResources()->GetDeviceResources()->GetD3DDevice());
	m_basicEffect->SetTextureEnabled(true);

	// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			GetCommonResources()->GetDeviceResources()->GetD3DDevice(),
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	m_tween = AddComponent<Tween>(this, true);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="primitiveBatch">�v���~�e�B�u�o�b�`</param>
/// <param name="camera">�J����</param>
void TargetMark::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�ݒu�������J�����̈ʒu����ݒ�
	Vector3 pos = GetTransform()->GetWorldPosition() - camera.GetEyePosition();
	pos.Normalize();
	Matrix mat = Matrix::CreateTranslation(-pos * 5 * m_size);

	//�\���ꏊ���v�Z
	VertexPositionTexture vertexs[4]{
		{Vector3(-EXTENS * m_size,EXTENS * m_size,0),Vector2(0,0)},
		{Vector3(EXTENS * m_size,EXTENS * m_size,0),Vector2(1,0)},
		{Vector3(EXTENS * m_size,-EXTENS * m_size,0),Vector2(1,1)},
		{Vector3(-EXTENS * m_size,-EXTENS * m_size,0),Vector2(0,1)},
	};

	//�r���{�[�h�ݒ�
	Matrix bill = camera.GetViewMatrix().Invert();
	bill._41 = 0;
	bill._42 = 0;
	bill._43 = 0;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetCommonResources()->GetCommonStates();

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, sampler);

	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);// �u�����h�X�e�[�g
	context->OMSetDepthStencilState(states->DepthDefault(), 0);		// �[�x�o�b�t�@/�X�e���V���o�b�t�@
	context->RSSetState(states->CullNone());			// �J�����O
	context->IASetInputLayout(m_inputLayout.Get());


	m_basicEffect->SetView(camera.GetViewMatrix());				// �r���[�s��
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());	// �ˉe�s��
	m_basicEffect->SetWorld(bill * mat * GetTransform()->GetWorldMatrix());
	m_basicEffect->SetTexture(m_renderer->GetImage());

	m_basicEffect->Apply(context);

	primitiveBatch->Begin();

	primitiveBatch->DrawQuad(vertexs[0], vertexs[1], vertexs[2], vertexs[3]);

	primitiveBatch->End();
}

/// <summary>
/// �J��
/// </summary>
void TargetMark::Open()
{
	m_size = 10;
	m_tween->DoFloat(m_size, 1, CHANGE_SPEED).SetEase(Easing::Ease::OutQuad);
}

/// <summary>
/// ����
/// </summary>
void TargetMark::Close()
{
	m_tween->DoFloat(m_size, 0, CHANGE_SPEED).SetEase(Easing::Ease::InQuad);
}
