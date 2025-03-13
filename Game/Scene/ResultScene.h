// ================================================================ 
// �t�@�C���� : ResultScene.h
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�V�[��
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class ResultScene :public Scene
{
public:
	Camera* GetCamera()const override{ return m_camera; }
	Canvas* GetCanvas()const override{ return m_canvas; }
private:
	//�J����
	Camera* m_camera;
	//�L�����o�X
	Canvas* m_canvas;
public:
	//�R���X�g���N�^
	ResultScene(CommonResources* resources);
	//�f�X�g���N�^
	~ResultScene()override = default;
	//�A�b�v�f�[�g
	void SceneUpdate(float deltatime)override;
	//�V�[��ID�擾
	SceneID GetSceneID() { return SceneID::RESULT; }
};