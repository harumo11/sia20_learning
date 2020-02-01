#include <iostream>
#include <memory>
#include <fanda/Csv.hpp>
#include <dynet/io.h>
#include <dynet/training.h>
#include <dynet/expr.h>

int main(int argc, char* argv[])
{
	//dynet初期化
	dynet::initialize(argc, argv);

	//データ読み込み
	CSV::CsvFile supervisor_data_csv("summary.csv");
	if (supervisor_data_csv.is_open()) {
		std::cout << "||| csv file of supervisor is opened successfully" << std::endl;
	}
	else {
		std::cout << "||| csv file of supervisor can NOT open. Please check that file" << std::endl;
	}

	//定数設定
	const unsigned int MINIBATCH_SIZE = 64;	//ミニバッチサイズ
	const unsigned int ITERATION = 50;		//１回に作成するミニバッチの数
	const unsigned int EPOCH_SIZE = 50;		//ミニバッチの作成を行う回数
	const unsigned int INPUT_DIM = 24;		//入力データの次元
	const unsigned int OUTPUT_DIM = 6;		//出力データの次元
	const unsigned int L1_DIM = 20;
	const unsigned int L2_DIM = 20;
	const unsigned int L3_DIM = 20;
	
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
	dynet::Parameter p_W4 = model.add_parameters({OUTPUT_DIM, L3_DIM});
	dynet::Parameter p_b4 = model.add_parameters({OUTPUT_DIM});

	//ノード作成
	dynet::Expression W1 = dynet::parameter(cg, p_W1);
	dynet::Expression W2 = dynet::parameter(cg, p_W2);
	dynet::Expression W3 = dynet::parameter(cg, p_W3);
	dynet::Expression W4 = dynet::parameter(cg, p_W4);
	dynet::Expression b1 = dynet::parameter(cg, p_b1);
	dynet::Expression b2 = dynet::parameter(cg, p_b2);
	dynet::Expression b3 = dynet::parameter(cg, p_b3);
	dynet::Expression b4 = dynet::parameter(cg, p_b4);

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
	dynet::Expression y_pred = W4*z3 + b4;
	dynet::Expression loss_expr = dynet::squared_distance(y_pred, y);
	dynet::Expression sum_loss = dynet::mean_batches(loss_expr);
	
	//computation graphを描画
	std::cout << "=============================================" << std::endl;
	cg.print_graphviz();
	std::cout << "=============================================" << std::endl;

	return 0;
}
