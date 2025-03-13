// ================================================================ 
// �t�@�C���� : UserInterface.h
// �쐬�� : �i�R�ɓV
// ���� :  UI�N���X
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Config.h"

class Canvas;
class Camera;
class PrimitiveRenderer;

class UserInterface:public Object
{
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4    Position;
		DirectX::SimpleMath::Vector2	WindowSize;
		DirectX::SimpleMath::Vector2	Size;
		DirectX::SimpleMath::Vector4    Color;
		DirectX::SimpleMath::Vector2    Extent;
		DirectX::SimpleMath::Vector2    Offset;
		DirectX::SimpleMath::Vector4    ClipRange;
		DirectX::SimpleMath::Vector4    Free;
	};
public:
	//�Q�b�^�[
	Canvas* GetCanvas() const { return m_canvas; }

	Microsoft::WRL::ComPtr<ID3D11Buffer> GetCBuffer() { return m_CBuffer; }
	Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout() { return m_inputLayout; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture() { return m_texture; }
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader() { return m_vertexShader; }
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader() { return m_pixelShader; }
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> GetGeometryShader() { return m_geometryShader; }

	DirectX::SimpleMath::Vector2 GetPosition()const { return m_position; }
	DirectX::SimpleMath::Vector2 GetSize()const { return m_size; }
	DirectX::SimpleMath::Vector4 GetColor()const { return m_color; }
	DirectX::SimpleMath::Vector2 GetExtent()const { return m_extent; }
	DirectX::SimpleMath::Vector2 GetOffset()const { return m_offset; }
	DirectX::SimpleMath::Vector4 GetClipRange()const { return m_clipRange; }
	bool GetMouseEventFlag()const { return m_mouseEventFlag; }
	//�Z�b�^�[
	void SetPosition(const DirectX::SimpleMath::Vector2 position) { m_position = position; }
	void SetSize(const DirectX::SimpleMath::Vector2 size) { m_size = size; }
	void SetColor(const DirectX::SimpleMath::Vector4 color) { m_color = color; }
	void SetExtent(const DirectX::SimpleMath::Vector2 extent) { m_extent = extent; }
	void SetOffset(const DirectX::SimpleMath::Vector2 offset) { m_offset = offset; }
	void SetClipRange(const DirectX::SimpleMath::Vector4 range) { m_clipRange = range; }
	void SetMouseEventFlag(bool mouseEventflag) { m_mouseEventFlag = mouseEventflag; }
	void SetFreeElement(const DirectX::SimpleMath::Vector4 free) { m_freeElement = free; }
private:
	//�L�����o�X
	Canvas* m_canvas;
	//�`��
	PrimitiveRenderer* m_render;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//�|�W�V����
	DirectX::SimpleMath::Vector2 m_position;
	//�T�C�Y
	DirectX::SimpleMath::Vector2 m_size;
	//�F
	DirectX::SimpleMath::Vector4 m_color;
	//��
	DirectX::SimpleMath::Vector2 m_extent;
	//�I�t�Z�b�g
	DirectX::SimpleMath::Vector2 m_offset;
	//�؂���͈�
	DirectX::SimpleMath::Vector4 m_clipRange;
	//�t���[
	DirectX::SimpleMath::Vector4 m_freeElement;
	//�}�E�X�ɂ��C�x���g�����s���邩���f
	bool m_mouseEventFlag;
public:
	UserInterface(Canvas* canvas,std::string filename = "Quad", int renderorder = 0);
	virtual ~UserInterface() override;
	//�`��
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//�`�揀�ݒ�
	void SetRenderOrder(int order);
	//�e�N�X�`���Z�b�g
	void SetTexture(std::string filename);
	//�o�[�e�b�N�X�V�F�[�_�[�ݒ�
	void SetVertexShader(std::string filename);
	//�s�N�Z���V�F�[�_�ݒ�
	void SetPixelShader(std::string filename);
	//�`��
	void SetRender(std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> render);
	//�V�[���؂�ւ����C�x���g
	virtual void LoadScene(Scene* scene) override;

	//�}�E�X���m�C�x���g
	virtual void MouseWithinEvent(bool within) { UNREFERENCED_PARAMETER(within); };
	//���N���b�N�C�x���g
	virtual void LeftClickEvent(bool within) { UNREFERENCED_PARAMETER(within); };
};