// ================================================================ 
// ファイル名 : ITweenUpdate.h
// 作成者 : 景山碧天
// 説明 :  TweenUpdateインターフェース
// ================================================================

#pragma once
#include"Easing.h"

class ITweenUpdate
{
public:
	virtual ~ITweenUpdate() = default;
	//アップデート
	virtual bool Update(float deltatime) = 0;
	//イージング種類設定
	virtual void SetEase(const Easing::Ease& easy) = 0;
	//値変更(巻き戻り)
	virtual void Yoyo() = 0;
	//値変更(初期設定)
	virtual void ReStart() = 0;
	//値変更(加算)
	virtual void Incremental() = 0;
	//処理処理
	virtual void Kill() = 0;
	//変化量を相対値として利用
	virtual void Relative() = 0;
	//終点は変えずに初期値変更
	virtual void ReLoad() = 0;
};