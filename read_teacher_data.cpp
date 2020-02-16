#include <iostream>
#include <fanda/Csv.hpp>

int main(int argc, char const* argv[])
{
	
	//教師データの入ったcsvファイルを読み込む
	CSV::CsvFile csv("edit.csv");
	if (csv.is_open()) {
		std::cout << "||| the csv file of teacher data can be opened" << std::endl;
	}
	else {
		std::cout << "||| the csv file of teacher data can NOT be opened" << std::endl;
	}

	//教師データのサイズを見る
	std::cout << "collumn : " << csv.collumn_size() << std::endl;
	std::cout << "raw : " << csv.raw_size() << std::endl;

	//教師データのcsvファイルを表示
	//csv.print();
	
	//教師データをランダムサンプリング
	auto new_csv = csv.get_random_sampling(3);
	new_csv.print();

	return 0;
}
