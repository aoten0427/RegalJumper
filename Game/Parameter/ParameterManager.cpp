// ================================================================ 
// ファイル名 : ParameterManager.cpp
// 作成者 : 景山碧天
// 説明 :  パラメータ読み込みクラス
// ================================================================
#include"pch.h"
#include"ParameterManager.h"
#include"PlayerParameter.h"
#include"ThreadParameter.h"

/// <summary>
/// 各パラメータ読み込み
/// </summary>
void ParameterManager::LoadDaata()
{
	PlayerParameter::LOAD_DATA();
	ThreadParameter::LOAD_DATA();
}
