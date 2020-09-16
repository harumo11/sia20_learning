// long normal broomの学習を行うプログラム．
// 実際の環境で使用する
// 圧力を加えたバージョン
// ８層

#include <Gpop/Series.hpp>
#include <dynet/expr.h>
#include <dynet/io.h>
#include <dynet/training.h>
#include <fanda/Csv.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <tuple>
#include <valarray>

/**
 * @brief csvデータから教師データをランダムに抽出する．
 *
 * @return 
 * - end effector position(t)
 * - end effector position(t-1)
 * - end effector position(t-2)
 * - candy position
 * - broom position
 * - dustpan position
 * -----------------------------
 * - end effector velocity(t)
 */
std::tuple<std::vector<dynet::real>, std::vector<dynet::real>> create_one_traingin_data_point(const std::vector<CSV::CsvFile>& training_data)
{
    // 抽出するcsvを選ぶ
    std::random_device seed_gen;
    std::uniform_int_distribution<> dist(0, training_data.size() - 1);
    const int choosed_training_data_index = dist(seed_gen);
    std::cout << "|||[create_one_training_data_points] choosed train data number : " << choosed_training_data_index << " / " << training_data.size() - 1 << std::endl;
    auto choosed_training_data = training_data.at(choosed_training_data_index);

    // データポイントを作成する
    auto raw_data_points = choosed_training_data.get_random_sampling(3);
    std::cout << "|||[create_one_training_data_points] raw data point csv info " << std::endl;
    std::cout << "|||[create_one_training_data_points] column size : " << raw_data_points.column_size() << std::endl;
    std::cout << "|||[create_one_training_data_points] raw size" << raw_data_points.row_size() << std::endl;

    std::vector<dynet::real> data_point_x;
    // end effector position(t)
    for (int i = 32; i < 38; i++) {
        data_point_x.push_back(raw_data_points(2, i).get_as_double());
    }
    // end effector position(t-1)
    for (int i = 32; i < 38; i++) {
        data_point_x.push_back(raw_data_points(1, i).get_as_double());
    }
    // end effector position(t-2)
    for (int i = 32; i < 38; i++) {
        data_point_x.push_back(raw_data_points(0, i).get_as_double());
    }
    // candy position(t)
    for (int i = 0; i < 6; i++) {
        data_point_x.push_back(raw_data_points(2, i).get_as_double());
    }
    // broom position(t)
    for (int i = 12; i < 18; i++) {
        data_point_x.push_back(raw_data_points(2, i).get_as_double());
    }
    // dustpan position(t)
    for (int i = 6; i < 12; i++) {
        data_point_x.push_back(raw_data_points(2, i).get_as_double());
    }
    // leptorino
    data_point_x.push_back(raw_data_points(2, 44).get_as_double());

    std::cout << "||| choosed_training_data" << std::endl;
    //raw_data_points.print();	// ミニバッチの表示

    std::vector<dynet::real> data_point_y;
    for (int i = 38; i < 44; i++) {
        data_point_y.push_back(raw_data_points(2, i).get_as_double());
    }

    return { data_point_x, data_point_y };
}

/**
 * @brief 教師データが記録されているｃｓｖの１行目はヘッダーなので，それを取り除く
 *
 * @param training_data 教師データが格納されているcsv
 */
void remove_header_from_training_data(std::vector<CSV::CsvFile>& training_data)
{
    for (auto&& e : training_data) {
        e.remove_line(0);
    }
}

/**
 * @brief ミニバッチを作成する関数．
 * 入力次元が２でミニバッチサイズが４の場合({2}, 4), 次元が2x4=8のベクトルを入力としてComputationGraphは受け取る．
 * create_one_traiing_data_point()で作成したデータポイントをミニバッチの数だけ結合し，そのベクトルを返す．
 *
 * @param training_data 教師データ．ただしヘッダーは取り除かれたもの
 *
 * @return dynetのミニバッチ形式に沿ったミニバッチを返す
 */
std::tuple<std::vector<dynet::real>, std::vector<dynet::real>> create_one_minibatch(const std::vector<CSV::CsvFile>& training_data, const unsigned int minibatch_size)
{
    std::vector<dynet::real> minibatch_x, minibatch_y;

    for (int i = 0; i < minibatch_size; i++) {
        auto [data_point_x, data_point_y] = create_one_traingin_data_point(training_data);
        minibatch_x.insert(minibatch_x.end(), data_point_x.begin(), data_point_x.end());
        minibatch_y.insert(minibatch_y.end(), data_point_y.begin(), data_point_y.end());
    }
    std::cout << "||| [create_one_minibatch] "
              << "size of minibatch_x : " << minibatch_x.size() << std::endl;
    std::cout << "||| [create_one_minibatch] "
              << "size of minibatch_y : " << minibatch_y.size() << std::endl;
    return { minibatch_x, minibatch_y };
}

int main(int argc, char* argv[])
{
    // 設定
    const std::string training_data_dir_path = "../long_normal_broom_training_data";

    // 教師データの成否データ読み込み
    CSV::CsvFile training_data_state_file("../long_normal_broom_training_data/status.csv");
    if (!training_data_state_file.is_open()) {
        std::cout << "||| Could not opne the training state file" << std::endl;
        std::cout << "||| Exit" << std::endl;
        std::exit(1);
    } else {
        std::cout << "||| Open the training state file successfully" << std::endl;
        std::cout << "||| CSV Colmun size : " << training_data_state_file.column_size() << std::endl;
        std::cout << "||| CSV Row size : " << training_data_state_file.column_size() << std::endl;
        //training_data_state_file.print(); // 学習の成否を記録したファイルの中身を表示
    }

    // 教師データの成否データに基づき教師データを読み込む
    // もしくは，
    // 教師データの成否データに基づきValidationデータを読み込む
    std::vector<CSV::CsvFile> training_data;
    std::vector<CSV::CsvFile> validation_data;
    for (int i = 0; i < training_data_state_file.row_size(); i++) {
        const std::string trianing_status = training_data_state_file(i, 1).get_as_string();
        if (trianing_status == "TRUE") {
            std::string csv_file_name = training_data_dir_path + "/log_" + std::to_string(i) + ".csv";
            training_data.emplace_back(CSV::CsvFile(csv_file_name));
        } else if (trianing_status == "VALIDATION") {
            std::string csv_file_name = training_data_dir_path + "/log_" + std::to_string(i) + ".csv";
            validation_data.emplace_back(CSV::CsvFile(csv_file_name));
        }
    }
    std::cout << "||| the amount of training data file : " << training_data.size() << std::endl;
    std::cout << "||| the amount of validation data file : " << validation_data.size() << std::endl;
    // csvファイルのデータからヘッダーを取り除く
    remove_header_from_training_data(training_data);
    remove_header_from_training_data(validation_data);
    // create_one_training_data_point()の動作チェック
    //auto [input_x, output_y] = create_one_traingin_data_point(training_data);
    //std::cout << "||| input_x" << std::endl;
    //for (auto e : input_x) {
    //    std::cout << "||| " << e << std::endl;
    //}
    //std::cout << "||| output_y" << std::endl;
    //for (auto e : output_y) {
    //    std::cout << "||| " << e << std::endl;
    //}

    // dynet定数
    // config1
    const int MINIBATCH_SIZE = 2; //ミニバッチのを構成するデータポイントの数
    const int ITERATION = 10000; //全エポックを使い切る学習を何回行うかを決める数
    const int EPOCH_SIZE = 1250*ITERATION; //ミニバッチを何個作成するかを規定する数
    const int INPUT_LAYER_DIMENSION = 37;
    const int HIDEN_LAYER_DIMENSION = 20;
    const int OUTPUT_LAYER_DIMENSION = 6;

    // dynet初期化
    // config2
    dynet::DynetParams params;
    //params.autobatch = 0; // 自動ミニバッチ機能
    params.weight_decay = 0.000001; // 正則化
	params.cpu_requested = true;
    dynet::initialize(params);

    // dynet最適化手法の選択
    // config3
    dynet::ParameterCollection parameter_collection;
    dynet::SimpleSGDTrainer trainer(parameter_collection);
    trainer.learning_rate = 0.000001;

    // dynetグラフ
    dynet::ComputationGraph computation_graph;
    // 1st layer
    dynet::Parameter p_W1 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, INPUT_LAYER_DIMENSION }, 0, "W1");
    dynet::Parameter p_b1 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b1");
    // 2nd layer
    dynet::Parameter p_W2 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W2");
    dynet::Parameter p_b2 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b2");
    // 3rd layer
    dynet::Parameter p_W3 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W3");
    dynet::Parameter p_b3 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b3");
    // 4th layer
    dynet::Parameter p_W4 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W4");
    dynet::Parameter p_b4 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b4");
    // 5th layer
    dynet::Parameter p_W5 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W5");
    dynet::Parameter p_b5 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b5");
    // 6th layer
    dynet::Parameter p_W6 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W6");
    dynet::Parameter p_b6 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b6");
    // 7th layer
    dynet::Parameter p_W7 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W7");
    dynet::Parameter p_b7 = parameter_collection.add_parameters({ HIDEN_LAYER_DIMENSION }, 0, "b7");
    // 8th layer(output layer)
    dynet::Parameter p_W8 = parameter_collection.add_parameters({ OUTPUT_LAYER_DIMENSION, HIDEN_LAYER_DIMENSION }, 0, "W8");
    dynet::Parameter p_b8 = parameter_collection.add_parameters({ OUTPUT_LAYER_DIMENSION }, 0, "b8");

    // dynetノード作成
    // 1st layer
    dynet::Expression W1 = dynet::parameter(computation_graph, p_W1);
    dynet::Expression b1 = dynet::parameter(computation_graph, p_b1);
    // 2nd layer
    dynet::Expression W2 = dynet::parameter(computation_graph, p_W2);
    dynet::Expression b2 = dynet::parameter(computation_graph, p_b2);
    // 3rd layer
    dynet::Expression W3 = dynet::parameter(computation_graph, p_W3);
    dynet::Expression b3 = dynet::parameter(computation_graph, p_b3);
    // 4th layer
    dynet::Expression W4 = dynet::parameter(computation_graph, p_W4);
    dynet::Expression b4 = dynet::parameter(computation_graph, p_b4);
    // 5th layer
    dynet::Expression W5 = dynet::parameter(computation_graph, p_W5);
    dynet::Expression b5 = dynet::parameter(computation_graph, p_b5);
    // 6th layer
    dynet::Expression W6 = dynet::parameter(computation_graph, p_W6);
    dynet::Expression b6 = dynet::parameter(computation_graph, p_b6);
    // 7th layer
    dynet::Expression W7 = dynet::parameter(computation_graph, p_W7);
    dynet::Expression b7 = dynet::parameter(computation_graph, p_b7);
    // 8th layer(output layer)
    dynet::Expression W8 = dynet::parameter(computation_graph, p_W8);
    dynet::Expression b8 = dynet::parameter(computation_graph, p_b8);

    // 入出力設定
    dynet::Dim x_dimension({ INPUT_LAYER_DIMENSION }, MINIBATCH_SIZE);
    dynet::Dim y_dimension({ OUTPUT_LAYER_DIMENSION }, MINIBATCH_SIZE);
    std::cout << "||| "
              << "x dimension : " << x_dimension << "\t"
              << "y dimension : " << y_dimension << std::endl;
    auto x_value_ptr = std::make_shared<std::vector<dynet::real>>(); // 教師データのミニバッチのポインタ（入力）
    auto y_value_ptr = std::make_shared<std::vector<dynet::real>>(); // 教師データのミニバッチのポインタ（出力）
    dynet::Expression x = dynet::input(computation_graph, x_dimension, x_value_ptr.get());
    dynet::Expression y = dynet::input(computation_graph, y_dimension, y_value_ptr.get());

    // dynet計算グラフの構築
    dynet::Expression z1 = dynet::rectify(W1 * x + b1);
    dynet::Expression z2 = dynet::rectify(W2 * z1 + b2);
    dynet::Expression z3 = dynet::rectify(W3 * z2 + b3);
    dynet::Expression z4 = dynet::rectify(W4 * z3 + b4);
    dynet::Expression z5 = dynet::rectify(W5 * z4 + b5);
    dynet::Expression z6 = dynet::rectify(W6 * z5 + b6);
    dynet::Expression z7 = dynet::rectify(W7 * z6 + b7);
    dynet::Expression y_pred = W8 * z7 + b8;
    dynet::Expression loss_expr = dynet::squared_distance(y_pred, y);
    dynet::Expression mean_loss = dynet::mean_batches(loss_expr);

    // dynetグラフ描画
    std::cout << "----------------------------------------------------------" << std::endl;
    computation_graph.print_graphviz();
    std::cout << "----------------------------------------------------------" << std::endl;

    // Gpopで表示
    Gpop::Series train_plot("error");
    train_plot.set_x_label("minibatch");
    train_plot.set_y_label("error");
    train_plot.limit_max_number(800);
    Gpop::Series validation_plot("validation error");
    validation_plot.set_x_label("epoch");
    validation_plot.set_y_label("error");
    validation_plot.limit_max_number(800);

    // １エポックだけ学習
    for (int epoch_iteratior = 0; epoch_iteratior < EPOCH_SIZE; epoch_iteratior++) {
        std::cout << "||| Epoch : " << epoch_iteratior << " / " << EPOCH_SIZE << std::endl;
        // 1ミニバッチだけ学習
        for (int minibatch_iterator = 0; minibatch_iterator < MINIBATCH_SIZE; minibatch_iterator++) {
            std::cout << "\t||| Minibatch : " << minibatch_iterator << std::endl;

            // dynetミニバッチを初期化
            x_value_ptr->clear();
            y_value_ptr->clear();

            // dynet ミニバッチ１つを作成し代入
            auto [input_x, output_y] = create_one_minibatch(training_data, MINIBATCH_SIZE);
            x_value_ptr->assign(input_x.begin(), input_x.end());
            y_value_ptr->assign(output_y.begin(), output_y.end());

            // フォワードプロパゲーション
            double error = dynet::as_scalar(computation_graph.forward(mean_loss));
            std::cout << "||| mean_loss " << dynet::as_scalar(mean_loss.value()) << std::endl;

            // バックプロパゲーション
            computation_graph.backward(mean_loss);

            // 勾配アップデート
            trainer.update();

            // エラー表示
            std::cout << "||| train error " << error << std::endl;

            // errorを表示
            train_plot.plot(error);
            train_plot.pause();
        }

        // validation用の計算グラフを作成
        auto [validation_input_x, validation_input_y] = create_one_minibatch(validation_data, MINIBATCH_SIZE);
        x_value_ptr->assign(validation_input_x.begin(), validation_input_x.end());
        y_value_ptr->assign(validation_input_y.begin(), validation_input_y.end());

        // フォワードプロパゲーション
        double validation_error = dynet::as_scalar(computation_graph.forward(mean_loss));
        std::cout << "||| validation error " << validation_error << std::endl;
        validation_plot.plot(validation_error);
        validation_plot.pause();
    }

    // モデルを保存
    dynet::TextFileSaver saver("train3_2.model");
    saver.save(parameter_collection);
    return 0;
}
