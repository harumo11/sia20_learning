// sia20の学習・実行ようにデータを上限下限で区切るクリッピングを行うためのクラス

#include <iostream>

class Clipping {

public:
    Clipping(const double input_min, const double input_max);
    double get_cliped_value(const double);
    double get_gradient();
    double get_intercepts();

private:
    const double input_min_;
    const double input_max_;
    const double output_min_ = -1;
    const double output_max_ = 1;
    double a;
    double b;
};

/**
 * @brief コンストラクター．
 * 与えられたinput_minとinput_maxの値からクリッピングで用いる傾きと切片を
 * 計算する．
 *
 * @param input_min センサからの入力の最大値
 * @param input_max センサからの入力の最小値
 */
Clipping::Clipping(const double input_min, const double input_max)
    : input_min_(input_min)
    , input_max_(input_max)
{
    this->a = (+1 - (-1)) / (this->input_max_ - this->input_min_);
    this->b = this->output_max_ - this->a * this->input_max_;
}

double Clipping::get_cliped_value(const double row_data)
{
    return this->a * row_data + this->b;
}

double Clipping::get_gradient()
{
    return this->a;
}

double Clipping::get_intercepts()
{
    return this->b;
}
