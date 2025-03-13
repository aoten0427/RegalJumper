// ================================================================ 
// ファイル名 : Time.cpp
// 作成者 : 景山碧天
// 説明 :  時間表示
// ================================================================
#include"pch.h"
#include"Time.h"
#include"Base/Scene/Scene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
Time::Time(Canvas* canvas):UserInterface(canvas)
	,
	m_count{0},
	m_numbers{},
	m_colon{nullptr},
	m_dot{},
	m_startX{},
	m_positionY{},
	m_size{},
	m_isNone{false}
{
	using namespace DirectX::SimpleMath;
	//本体は消す
	SetActive(false);
	//番号生成
	for (int i = 0; i < 6; i++)
	{
		m_numbers[i] = GetScene()->AddObject<UserInterface>(canvas, "Numbers", 4);
	}
	//コロン生成
	m_colon = GetScene()->AddObject<UserInterface>(canvas, "Colon", 4);
	//ドット生成
	m_dot = GetScene()->AddObject<UserInterface>(canvas, "Dot", 4);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Time::ObjectUpdate(float deltatime)
{
	if (m_isNone)return;
	UNREFERENCED_PARAMETER(deltatime);
	float absValue = std::fabs(m_count);
	// 小数点以下の桁数を除いた整数部分
	int integerPart = static_cast<int>(absValue);
	// 小数部分を取得
	float decimalPart = absValue - static_cast<float>(integerPart);
	//分を取得
	int minutePart = integerPart / 60;
	//秒数取得
	integerPart %= 60;

	int digits[6];
	digits[0] = minutePart / 10;//10分
	digits[1] = minutePart % 10;//1分
	digits[2] = integerPart / 10;//10秒
	digits[3] = integerPart % 10;//1秒
	decimalPart *= 10;
	digits[4] = static_cast<int>(decimalPart) % 10;//少数第一
	decimalPart *= 10;
	digits[5] = static_cast<int>(decimalPart) % 10;//少数第二

	//値に合わせて切り取り範囲設定
	for (int i = 0; i < 6; i++)
	{
		m_numbers[i]->SetClipRange(DirectX::SimpleMath::Vector4(digits[i] / 10.0f, 0, 0.1f, 1.0f));
	}
}

/// <summary>
/// 色設定
/// </summary>
/// <param name="color">色</param>
void Time::SetTimeColor(const DirectX::SimpleMath::Vector4 color)
{
	for (int i = 0; i < 6; i++)
	{
		m_numbers[i]->SetColor(color);
	}
	m_dot->SetColor(color);
	m_colon->SetColor(color);
}

/// <summary>
/// 値なしを設定
/// </summary>
/// <param name="none"></param>
void Time::SetNone(bool none)
{
	m_isNone = none;
	if (m_isNone)
	{
		for (int i = 0; i < 6; i++)
		{
			m_numbers[i]->SetTexture("Hyphen");
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			m_numbers[i]->SetTexture("Numbers");
		}
	}
}

/// <summary>
/// 描画位置を設定
/// </summary>
void Time::SetView()
{
	using namespace DirectX::SimpleMath;
	for (int i = 0; i < 6; i++)
	{
		//2つごとに間をあける
		float addpos = (i / 2) * m_size.x / 4;
		m_numbers[i]->SetPosition(Vector2(m_startX + i * (m_size.x) + addpos, m_positionY));
		m_numbers[i]->SetSize(m_size);
	}
	//コロン位置設定
	m_colon->SetPosition(Vector2(m_startX + (3.25f * m_size.x / 2), m_positionY));
	m_colon->SetSize(m_size);
	//ドット位置設定
	m_dot->SetPosition(Vector2(m_startX + (7.8f * m_size.x / 2), m_positionY));
	m_dot->SetSize(m_size);
}
