#include "Base/Shader/Model.hlsli"

//ディザリングパターンマトリックス
static const int pattern[4][4] =
{
    { 0, 8, 56, 48 },
    { 32, 40, 20, 28 },
    { 60, 52, 4, 12 },
    { 16, 24, 32, 44 },
};

// ディザリング処理
float Dithering(PS_INPUT input)
{
    // 現在の座標を 4×4 の範囲でループさせる
    int x = (int) fmod(input.Pos.x, 4.0f);
    int y = (int) fmod(input.Pos.y, 4.0f);

    // ディザリングマトリックスから現在のピクセルに対応する閾値を取得
    int dither = pattern[y][x];

    // クリップ範囲の定義
    float clipRange = 1.0;

    // カメラからの距離を計算し、クリップ範囲を超える部分を取得
    float eyeToClipRange = max(0.0f, length(input.EyeVector) - clipRange);

    // クリップ割合を計算
    float clipRate = 1.0f - min(1.0f, eyeToClipRange / 12.0f);

    // ディザリング値調整
    return dither - 64 * clipRate;
}
