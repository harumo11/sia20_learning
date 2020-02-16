//このプログラムは教師データを作成するツールです．
//与えられた教師データから連続する３行をランダムに抜き出し，
//それを新しい教師データとしてファイルに保存します．

#include <iostream>
#include <fanda/Csv.hpp>

int main(int argc, char const* argv[])
{
	//教師データの入ったcsvファイルを読み込む
	CSV::CsvFile input_csv("input.csv");
	return 0;
}
