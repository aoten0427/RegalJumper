#include "Base/Shader/Model.hlsli"

//�f�B�U�����O�p�^�[���}�g���b�N�X
static const int pattern[4][4] =
{
    { 0, 8, 56, 48 },
    { 32, 40, 20, 28 },
    { 60, 52, 4, 12 },
    { 16, 24, 32, 44 },
};

// �f�B�U�����O����
float Dithering(PS_INPUT input)
{
    // ���݂̍��W�� 4�~4 �͈̔͂Ń��[�v������
    int x = (int) fmod(input.Pos.x, 4.0f);
    int y = (int) fmod(input.Pos.y, 4.0f);

    // �f�B�U�����O�}�g���b�N�X���猻�݂̃s�N�Z���ɑΉ�����臒l���擾
    int dither = pattern[y][x];

    // �N���b�v�͈͂̒�`
    float clipRange = 1.0;

    // �J��������̋������v�Z���A�N���b�v�͈͂𒴂��镔�����擾
    float eyeToClipRange = max(0.0f, length(input.EyeVector) - clipRange);

    // �N���b�v�������v�Z
    float clipRate = 1.0f - min(1.0f, eyeToClipRange / 12.0f);

    // �f�B�U�����O�l����
    return dither - 64 * clipRate;
}
