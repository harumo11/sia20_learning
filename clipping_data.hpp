#include <iostream>

//namespace leptorino {
//double cliping(const double leptorino_row_data)
//{
//    if (leptorino_row_data < 0) {
//        return -1;
//    } else if (leptorino_row_data > 400) {
//        return 1;
//    } else {
//        return (1.0 / 200) * leptorino_row_data - 1;
//    }
//}
//} // namespace leptorino

namespace dirt_x {
	double clipping(const double raw_data){
		if (raw_data < -0.25) {
			return -1;
		}
		else if (raw_data > 0.55){
			return 1;
		}
		else {
			return 2.5 * raw_data + (-0.375);
		}
	}
} // namespace dirt_x

namespace dirt_y {
	double clipping(const double raw_data){
		if (raw_data < 0.2) {
			return -1;
		}
		else if (raw_data > 0.4){
			return 1;
		}
		else {
			return 10 * raw_data + (-3);
		}
	}
} // namespace dirt_y

namespace dirt_z {
	double clipping(const double raw_data){
		if (raw_data < 0.9) {
			return -1;
		}
		else if (raw_data > 1.2){
			return 1;
		}
		else {
			return 6.67 * raw_data + (-7);
		}
	}
} // namespace dirt_z

namespace broom_x {
	double clipping(const double raw_data){
		if (raw_data < -0.5) {
			return -1;
		}
		else if (raw_data > 0.4){
			return 1;
		}
		else {
			return 2.22 * raw_data + (0.111);
		}
	}
} // namespace broom_x

namespace broom_y {
	double clipping(const double raw_data){
		if (raw_data < -0.3) {
			return -1;
		}
		else if (raw_data > 0.1){
			return 1;
		}
		else {
			return 5 * raw_data + (0.5);
		}
	}
} // namespace broom_y

namespace broom_z {
	double clipping(const double raw_data){
		if (raw_data < 0.7) {
			return -1;
		}
		else if (raw_data > 1.1){
			return 1;
		}
		else {
			return 5 * raw_data + (-4.5);
		}
	}
} // namespace broom_z

namespace broom_r {
	double clipping(const double raw_data){
		if (raw_data < -3) {
			return -1;
		}
		else if (raw_data > -2){
			return 1;
		}
		else {
			return 2 * raw_data + (5);
		}
	}
} // namespace broom_r

namespace broom_p {
	double clipping(const double raw_data){
		if (raw_data < -0.5) {
			return -1;
		}
		else if (raw_data > 0.2){
			return 1;
		}
		else {
			return 2.85 * raw_data + (0.428);
		}
	}
} // namespace broom_p

namespace broom_w {
	double clipping(const double raw_data){
		if (raw_data < -0.5) {
			return -1;
		}
		else if (raw_data > 0.8){
			return 1;
		}
		else {
			return 1.53 * raw_data + (-0.23);
		}
	}
} // namespace broom_w

namespace pose_state_x {
	double clipping(const double raw_data){
		if (raw_data < 0.4) {
			return -1;
		}
		else if (raw_data > 0.9){
			return 1;
		}
		else {
			return 4 * raw_data + (-2.6);
		}
	}
} // namespace pose_state_x

namespace pose_state_y {
	double clipping(const double raw_data){
		if (raw_data < -0.2) {
			return -1;
		}
		else if (raw_data > 0.5){
			return 1;
		}
		else {
			return 2.85 * raw_data + (-0.42);
		}
	}
} // namespace pose_state_y

namespace pose_state_z {
	double clipping(const double raw_data){
		if (raw_data < 0.8) {
			return -1;
		}
		else if (raw_data > 1.2){
			return 1;
		}
		else {
			return 5 * raw_data + (-5);
		}
	}
} // namespace pose_state_z

namespace pose_state_r {
	double clipping(const double raw_data){
		if (raw_data < -3.0) {
			return -1;
		}
		else if (raw_data > 1.0){
			return 1;
		}
		else {
			return 0.5 * raw_data + (0.5);
		}
	}
} // namespace pose_state_r

namespace pose_state_p {
	double clipping(const double raw_data){
		if (raw_data < -1.8) {
			return -1;
		}
		else if (raw_data > -0.5){
			return 1;
		}
		else {
			return 1.53 * raw_data + (1.77);
		}
	}
} // namespace pose_state_p

namespace pose_state_w {
	double clipping(const double raw_data){
		if (raw_data < -3.0) {
			return -1;
		}
		else if (raw_data > 2.0){
			return 1;
		}
		else {
			return 0.4 * raw_data + (0.2);
		}
	}
} // namespace pose_state_w
