#include "moveAverage.hpp"

float MovingAverage::update(float now_val)
{
    // 1. 新しい値をバッファに書き込む (循環バッファ)
    storage[current_target] = now_val;
    current_target = (current_target + 1) % num_elements;

    // 2. データ点数のカウント（上限はウィンドウサイズ）
    if (count < num_elements)
        count++;

    // 3. 移動平均の計算
    float sum = 0;
    // 蓄積されたデータ点数分だけ合計する
    for (int i = 0; i < count; i++)
    {
        sum += storage[i];
    }

    // 整数除算で平均を出す
    return sum / count;
}

void EMAfilter::EMA_init(float alpha)
{
    _alpha = alpha;
}

void EMAfilter::EMA_calculate(float now_data)
{
    _now_data = now_data;
    _filtered = _now_data * _alpha + _filtered * (1 - _alpha);
}