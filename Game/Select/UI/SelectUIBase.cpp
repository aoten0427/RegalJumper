// ================================================================ 
// �t�@�C���� : SelectUIBase.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[��UI�̃x�[�X
// ================================================================

#include"pch.h"
#include"SelectUIBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�����L�����o�X</param>
SelectUIBase::SelectUIBase(Canvas* canvas):UserInterface(canvas,"SelectBase")
{
	using namespace DirectX::SimpleMath;

	SetPosition(Vector2(960, 360));
	SetSize(Vector2(640, 720));
	
}
