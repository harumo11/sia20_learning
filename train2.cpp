#include <iostream>
#include <fstream>
#include <memory>
#include <fanda/Csv.hpp>
#include <dynet/io.h>
#include <dynet/training.h>
#include <dynet/expr.h>
#include <Gpop/Series.hpp>

void save_vector(const std::vector<double>& vec){
	std::ofstream file("loss.csv");

	for (auto e : vec){
		file << e << std::endl;
	}
}

std::vector<dynet::real> csv_line_to_vector(CSV::CsvFile csv, const unsigned int num){
	std::vector<dynet::real> return_vec;
	for (int i = 0; i < csv.raw_size(); i++) {
		return_vec.push_back((dynet::real)csv(num, i).get_as_double());
	}
	return return_vec;
}

std::vector<dynet::real> extract_posexyz(CSV::CsvFile csv, const unsigned int num){
	std::vector<dynet::real> return_vec;
	return_vec.push_back((dynet::real)csv(num, 9).get_as_double());
	return_vec.push_back((dynet::real)csv(num, 10).get_as_double());
	return_vec.push_back((dynet::real)csv(num, 11).get_as_double());
	return return_vec;
}

int main(int argc, char* argv[])
{
	//dynet初期化
	dynet::DynetParams params;
	params.weight_decay = 0.0001;
	dynet::initialize(params);

	//データ読み込み
	CSV::CsvFile supervisor_data_csv("edit.csv");
	if (supervisor_data_csv.is_open()) {
		std::cout << "||| csv file of supervisor is opened successfully" << std::endl;
		std::cout << "||| csv file collumn size : " << supervisor_data_csv.collumn_size() << std::endl;
		std::cout << "||| csv file raw size : " << supervisor_data_csv.raw_size() << std::endl;
	}
	else {
		std::cout << "||| csv file of supervisor can NOT open. Please check that file" << std::endl;
	}

	//定数設定
	const unsigned int MINIBATCH_SIZE = 8;	//ミニバッチサイズ
	const unsigned int ITERATION = 850;		//１回に作成するミニバッチの数
	const unsigned int EPOCH_SIZE = 5;		//ミニバッチの作成を行う回数
	const unsigned int INPUT_DIM = 18;		//入力データの次元
	const unsigned int OUTPUT_DIM = 1;		//出力データの次元
	const unsigned int L1_DIM = 15;
	const unsigned int L2_DIM = 15;
	const unsigned int L3_DIM = 15;
	const unsigned int L4_DIM = 15;
	const unsigned int L5_DIM = 15;
	const unsigned int L6_DIM = 15;
	const unsigned int L7_DIM = 15;
	
	//パラメータ作成（入力以外）
	dynet::ComputationGraph cg;
	dynet::ParameterCollection model;
	dynet::SimpleSGDTrainer trainer(model);
	////L1
	dynet::Parameter p_W1 = model.add_parameters({L1_DIM, INPUT_DIM});
	dynet::Parameter p_b1 = model.add_parameters({L1_DIM});
	////L2
	dynet::Parameter p_W2 = model.add_parameters({L2_DIM, L1_DIM});
	dynet::Parameter p_b2 = model.add_parameters({L2_DIM});
	/////L3
	dynet::Parameter p_W3 = model.add_parameters({L3_DIM, L2_DIM});
	dynet::Parameter p_b3 = model.add_parameters({L3_DIM});
	/////L4
	dynet::Parameter p_W4 = model.add_parameters({L4_DIM, L3_DIM});
	dynet::Parameter p_b4 = model.add_parameters({L4_DIM});
	/////L5
	dynet::Parameter p_W5 = model.add_parameters({L5_DIM, L4_DIM});
	dynet::Parameter p_b5 = model.add_parameters({L5_DIM});
	////L6
	dynet::Parameter p_W6 = model.add_parameters({L6_DIM, L5_DIM});
	dynet::Parameter p_b6 = model.add_parameters({L6_DIM});
	////L7
	dynet::Parameter p_W7 = model.add_parameters({L7_DIM, L6_DIM});
	dynet::Parameter p_b7 = model.add_parameters({L7_DIM});
	////L8
	dynet::Parameter p_W8 = model.add_parameters({OUTPUT_DIM, L7_DIM});
	

	//ノード作成
	dynet::Expression W1 = dynet::parameter(cg, p_W1);
	dynet::Expression W2 = dynet::parameter(cg, p_W2);
	dynet::Expression W3 = dynet::parameter(cg, p_W3);
	dynet::Expression W4 = dynet::parameter(cg, p_W4);
	dynet::Expression W5 = dynet::parameter(cg, p_W5);
	dynet::Expression W6 = dynet::parameter(cg, p_W6);
	dynet::Expression W7 = dynet::parameter(cg, p_W7);
	dynet::Expression W8 = dynet::parameter(cg, p_W8);
	dynet::Expression b1 = dynet::parameter(cg, p_b1);
	dynet::Expression b2 = dynet::parameter(cg, p_b2);
	dynet::Expression b3 = dynet::parameter(cg, p_b3);
	dynet::Expression b4 = dynet::parameter(cg, p_b4);
	dynet::Expression b5 = dynet::parameter(cg, p_b5);
	dynet::Expression b6 = dynet::parameter(cg, p_b6);
	dynet::Expression b7 = dynet::parameter(cg, p_b7);

	//入出力設定
	dynet::Dim x_dim({INPUT_DIM}, MINIBATCH_SIZE);
	dynet::Dim y_dim({OUTPUT_DIM}, MINIBATCH_SIZE);
	std::cout << "||| " << "x dim " << x_dim << " y_dim " << y_dim << std::endl;
	auto x_value_ptr = std::make_shared<std::vector<dynet::real>>();	//教師データのミニバッチのポインタ（入力）
	auto y_value_ptr = std::make_shared<std::vector<dynet::real>>();	//教師データのミニバッチのポインタ（出力）
	////ノード作成
	dynet::Expression x = dynet::input(cg, x_dim, x_value_ptr.get());
	dynet::Expression y = dynet::input(cg, y_dim, y_value_ptr.get());

	//computation graphの構築
	dynet::Expression z1 = dynet::rectify(W1*x  + b1);
	dynet::Expression z2 = dynet::rectify(W2*z1 + b2);
	dynet::Expression z3 = dynet::rectify(W3*z2 + b3);
	dynet::Expression z4 = dynet::rectify(W4*z3 + b4);
	dynet::Expression z5 = dynet::rectify(W5*z4 + b5);
	dynet::Expression z6 = dynet::rectify(W6*z5 + b6);
	dynet::Expression z7 = dynet::rectify(W7*z6 + b7);
	dynet::Expression y_pred = W8*z7;
	dynet::Expression loss_expr = dynet::squared_distance(y_pred, y);
	dynet::Expression sum_loss = dynet::mean_batches(loss_expr);
	
	//computation graphを描画
	std::cout << "=============================================" << std::endl;
	cg.print_graphviz();
	std::cout << "=============================================" << std::endl;

	//プロット準備
	Gpop::Series plot;
	std::vector<double> loss_vec;

	//学習を実行
	for (int epoch = 0; epoch < EPOCH_SIZE; epoch++) {
		for (int iteration = 0; iteration < ITERATION; iteration++) {
			//エポック数を表示
			std::cout << "||| " << "epoch : " << epoch << " / " << EPOCH_SIZE << std::endl;
			//イテレーション数を表示
			std::cout << "||| " << "iteration : " << iteration << " / " << ITERATION << std::endl;

			//ミニバッチを初期化
			x_value_ptr->clear();
			y_value_ptr->clear();

			//ミニバッチを１つ作成
			for (int i = 0; i < MINIBATCH_SIZE; i++) {
				//教師データから１行だけ読み出す
				std::random_device rnd;
				std::uniform_int_distribution<> uniform_dist(0, 2341);
				auto line_vec0 = csv_line_to_vector(supervisor_data_csv, uniform_dist(rnd));
				auto line_vec1 = extract_posexyz(supervisor_data_csv, uniform_dist(rnd)+1);
				auto line_vec2 = extract_posexyz(supervisor_data_csv, uniform_dist(rnd)+2);
				//出力データ作成
				y_value_ptr->push_back(line_vec0.back());
				line_vec0.pop_back();
				//入力データ作成
				std::cout << "||| line_vec0 size " << line_vec0.size() << std::endl;
				for (auto e : line_vec0){	//t
					x_value_ptr->push_back(e);
				}
				std::cout << "||| line_vec1 size " << line_vec1.size() << std::endl;
				for (auto e : line_vec1){	//t-1
					x_value_ptr->push_back(e);	
				}
				std::cout << "||| line_vec2 size " << line_vec2.size() << std::endl;
				for (auto e : line_vec2){	//t-2
					x_value_ptr->push_back(e);
				}
			}
			std::cout << "||| x_value_ptr size " << x_value_ptr->size() << std::endl;
			std::cout << "||| y_value_ptr size " << y_value_ptr->size() << std::endl;

			//ミニバッチ１つに対して学習を実行
			double loss = dynet::as_scalar(cg.forward(sum_loss));
			cg.backward(sum_loss);
			trainer.update();
			loss_vec.push_back(loss);
		}
	}

	plot.plot(loss_vec);
	plot.show();
	std::cin.get();

	save_vector(loss_vec);
	std::cout << "||| final loss : " << loss_vec.back() << std::endl;

	dynet::TextFileSaver s("tmp.model");
	s.save(model);

	return 0;
}
