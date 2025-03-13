// ================================================================ 
// ファイル名 : GameManager.h
// 作成者 : 景山碧天
// 説明 :  ゲーム共通の情報を管理
// ================================================================
#include"pch.h"
#include"GameManager.h"
#include"Game/Option/Option.h"	
#include"Game/Cursor/Cursor.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager()
	:
	g_stageNumber{11},
	g_option{nullptr},
	g_cursor{nullptr},
	m_resultTimer{0}
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameManager::~GameManager()
{
	g_option = nullptr;
	g_cursor = nullptr;
}

/// <summary>
/// オプションをセット
/// </summary>
/// <param name="option">オプション</param>
void GameManager::SetOption(Option* option)
{
	if (g_option)return;
	g_option = option;
}

/// <summary>
/// オプションを開く
/// </summary>
void GameManager::OpenOption()
{
	if (!g_option)return;
	g_option->Open();
}

/// <summary>
/// 感度を取得
/// </summary>
/// <returns>現在の感度</returns>
float GameManager::GetSensitivity()
{
	if (!g_option) return 1.0;
	return g_option->GetSensitivity();
}

/// <summary>
/// カーソルをセット
/// </summary>
/// <param name="cursor">カーソル</param>
void GameManager::SetCursor(Cursor* cursor)
{
	if (g_cursor)return;
	g_cursor = cursor;
}

/// <summary>
/// カーソルの表示を変える
/// </summary>
/// <param name="view">表示有無</param>
void GameManager::ViewCursor(bool view)
{
	if (!g_cursor)return;
	g_cursor->SetActive(view);
}

/// <summary>
/// ステージ番号を〇_〇の形式で返す
/// </summary>
/// <returns>ステージ名</returns>
std::string GameManager::GetStageName()
{
	int main = g_stageNumber / 10;
	int sub = g_stageNumber % 10;
	std::string stagename = std::to_string(main) + "_" + std::to_string(sub);
	return stagename;
}

/// <summary>
///ステージ番号を返す
/// </summary>
/// <returns>ステージ番号</returns>
std::pair<int, int> GameManager::GetStageNum()
{
	int main = g_stageNumber / 10;
	int sub = g_stageNumber % 10;

	return std::pair<int, int>(main, sub);
}

/// <summary>
/// ステージ番号を変化させる
/// </summary>
/// <param name="add">変化数</param>
/// <returns>変化できたか</returns>
bool GameManager::ChangeStage(int add)
{
	int main = g_stageNumber / 10;
	int sub = g_stageNumber % 10;

	sub += add;
	//サブ値の境界確認
	if (sub > MAX_STAGE_SUB)
	{
		main += 1;
		sub = sub - MAX_STAGE_SUB;
	}
	if (sub <= 0)
	{
		main -= 1;
		sub = sub + MAX_STAGE_SUB;
	}

	//ステージ超過確認
	if (MAX_STAGE_MAIN * 10 + MAX_STAGE_SUB < main * 10 + sub)return false;
	//ステージ下限確認
	if (main <= 0)return false;

	//ステージ番号を更新
	g_stageNumber = main * 10 + sub;
	return true;
}




