#include <iostream>
#include <random>
#include <fanda/Csv.hpp>

int main(int argc, char const* argv[])
{
	CSV::CsvFile csv("edit.csv");

	//１．０〜２３４１の中からランダムな数字を選択
	std::random_device rnd;
	std::uniform_int_distribution<int> uniform_dist(0, 2341);
	for (int i = 0; i < 8; i++) {
		int index = uniform_dist(rnd);
		std::cout << "||| " << index << std::endl;
		std::cout << csv(index, 0).get_as_double() << std::endl;
	}
	
	return 0;
}
