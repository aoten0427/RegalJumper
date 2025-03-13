// ================================================================ 
// ファイル名 : GameManager.h
// 作成者 : 景山碧天
// 説明 :  ゲーム共通の情報を管理
// ================================================================

#pragma once
#include"Base/MyLibraries/Singleton.h"

class Option;
class Cursor;

class GameManager :public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
private:
	GameManager();
public:
	const int MAX_STAGE_MAIN = 1;
	const int MAX_STAGE_SUB = 4;
public:
	//ステージ番号をを返す
	int GetStageNumber() const { return g_stageNumber; }
	//リザルトタイムセット
	void SetResultTimer(float timer) { m_resultTimer = timer; }
	//リザルトタイム取得
	float GetResultTime()const { return m_resultTimer; }
private:
	//ステージ番号
	int g_stageNumber;
	//オプション
	Option* g_option;
	//カーソル
	Cursor* g_cursor;
	//リザルト表示タイム
	float m_resultTimer;
public:
	~GameManager();

	//オプションセット
	void SetOption(Option* option);
	//オプションを開く
	void OpenOption();
	//感度を取得
	float GetSensitivity();
	//カーソルをセット
	void SetCursor(Cursor* cursor);
	//カーソルの表示を変える
	void ViewCursor(bool view);

	//ステージ番号を〇_〇の形式で返す
	std::string GetStageName();
	//ステージ番号を〇_〇の形式で返す
	std::pair<int, int> GetStageNum();
	//ステージ番号を変化させる
	bool ChangeStage(int add);
};
