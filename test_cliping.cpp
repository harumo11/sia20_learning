#include "clipping.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    Clipping cliped_hand_pose(-2, 4);
    std::cout << "a should be 1/3 : " << cliped_hand_pose.get_gradient() << std::endl;
    std::cout << "b should be -1/3 : " << cliped_hand_pose.get_intercepts() << std::endl;

    Clipping clipped_1(-2, 1);
    std::cout << "a : " << clipped_1.get_gradient() << std::endl;
    std::cout << "b : " << clipped_1.get_intercepts() << std::endl;

    return 0;
}
