#include "clipping_data.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    //double Li;
    //// When Li < 0,  return 0;
    //Li = -1;
    //auto Lo = leptorino::cliping(Li);
    //std::cout << "Lo < 0 : " << Lo << std::endl;

    //// When Li > 400, return 400;
    //Li = 500;
    //Lo = leptorino::cliping(Li);
    //std::cout << "Lo > 400 : " << Lo << std::endl;

    //// When 0 <= Li <= 400, return -1 <= Lo <= +1;
    //Li = 1;
    //Lo = leptorino::cliping(Li);
    //std::cout << "0 <= Lo <= 400 : " << Lo << std::endl;

    //Li = 200;
    //Lo = leptorino::cliping(Li);
    //std::cout << "0 <= Lo <= 400 : " << Lo << std::endl;

    //Li = 399;
    //Lo = leptorino::cliping(Li);
    //std::cout << "0 <= Lo <= 400 : " << Lo << std::endl;


	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << dirt_x::clipping(-1) << std::endl;
	std::cout << "1 = " << dirt_x::clipping(0.6) << std::endl;
	std::cout << "u = " << dirt_x::clipping(0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << dirt_y::clipping(0.2) << std::endl;
	std::cout << " 1 = " << dirt_y::clipping(0.4) << std::endl;
	std::cout << " u = " << dirt_y::clipping(0.3) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << dirt_z::clipping(0.9) << std::endl;
	std::cout << " 1 = " << dirt_z::clipping(1.2) << std::endl;
	std::cout << " u = " << dirt_z::clipping(1.0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << broom_x::clipping(-0.5) << std::endl;
	std::cout << " 1 = " << broom_x::clipping(0.4)  << std::endl;
	std::cout << " u = " << broom_x::clipping(0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << broom_y::clipping(-0.3) << std::endl;
	std::cout << " 1 = " << broom_y::clipping(0.1) << std::endl;
	std::cout << " u = " << broom_y::clipping(0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << broom_z::clipping(0.7) << std::endl;
	std::cout << " 1 = " << broom_z::clipping(1.1) << std::endl;
	std::cout << " u = " << broom_z::clipping(0.9) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << broom_r::clipping(-3) << std::endl;
	std::cout << " 1 = " << broom_r::clipping(-2) << std::endl;
	std::cout << " u = " << broom_r::clipping(-2.5) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << broom_p::clipping(-0.5) << std::endl;
	std::cout << " 1 = " << broom_p::clipping(0.2) << std::endl;
	std::cout << " u = " << broom_p::clipping(0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << broom_w::clipping(-0.5) << std::endl;
	std::cout << " 1 = " << broom_w::clipping(0.8) << std::endl;
	std::cout << " u = " << broom_w::clipping(0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << pose_state_x::clipping(0.4) << std::endl;
	std::cout << " 1 = " << pose_state_x::clipping(0.9) << std::endl;
	std::cout << " u = " << pose_state_x::clipping(0.5) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << pose_state_y::clipping(-0.2) << std::endl;
	std::cout << " 1 = " << pose_state_y::clipping(0.5) << std::endl;
	std::cout << " u = " << pose_state_y::clipping(0.0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << pose_state_z::clipping(0.8) << std::endl;
	std::cout << " 1 = " << pose_state_z::clipping(1.2) << std::endl;
	std::cout << " u = " << pose_state_z::clipping(0.9) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << pose_state_r::clipping(-3.0) << std::endl;
	std::cout << " 1 = " << pose_state_r::clipping(1.0) << std::endl;
	std::cout << " u = " << pose_state_r::clipping(0.0) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << pose_state_p::clipping(-1.8) << std::endl;
	std::cout << " 1 = " << pose_state_p::clipping(-0.5) << std::endl;
	std::cout << " u = " << pose_state_p::clipping(-1) << std::endl;

	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "-1 = " << pose_state_w::clipping(-3.0) << std::endl;
	std::cout << " 1 = " << pose_state_w::clipping(2.0) << std::endl;
	std::cout << " u = " << pose_state_w::clipping(-1) << std::endl;
    return 0;
}
