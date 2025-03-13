// ================================================================ 
// ファイル名 : IState.h
// 作成者 : 景山碧天
// 説明 :  ステートのインターフェース
// ================================================================

#pragma once

class IState
{
public:
	virtual ~IState() = default;
	// 事前更新する
	virtual void PreUpdate() = 0;
	// 更新する
	virtual void Update(float deltaTime) = 0;
	// 事後更新する
	virtual void PostUpdate() = 0;
};