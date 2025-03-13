// ================================================================ 
// �t�@�C���� : SpiderModelState.h
// �쐬�� : �i�R�ɓV
// ���� :  �w偃��f���̕`����
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class SpiderModelStateMachine;
class SpiderModels;

class Camera;

class SpiderModelState:public IState
{
public:
	//�`����
	enum class RenderType
	{
		NONE,
		ENTRY,
		NORMAL,
		PLAY,
		EXIT
	};
private:
	SpiderModelStateMachine* m_machine;
public:
	//�R���X�g���N�^
	SpiderModelState(SpiderModelStateMachine* machine,SpiderModels* spidermodel);
	//�f�X�g���N�^
	virtual ~SpiderModelState() = default;
	//�`��
	virtual void Render(const Camera& camera) = 0;
	//��ԕω�
	void ChangeState(RenderType type);
};