#include "cliping_leptorino.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    double Li;
    // When Li < 0,  return 0;
    Li = -1;
    auto Lo = leptorino::cliping(Li);
    std::cout << "Lo < 0 : " << Lo << std::endl;

    // When Li > 400, return 400;
    Li = 500;
    Lo = leptorino::cliping(Li);
    std::cout << "Lo > 400 : " << Lo << std::endl;

    // When 0 <= Li <= 400, return -1 <= Lo <= +1;
    Li = 1;
    Lo = leptorino::cliping(Li);
    std::cout << "0 <= Lo <= 400 : " << Lo << std::endl;

    Li = 200;
    Lo = leptorino::cliping(Li);
    std::cout << "0 <= Lo <= 400 : " << Lo << std::endl;

    Li = 399;
    Lo = leptorino::cliping(Li);
    std::cout << "0 <= Lo <= 400 : " << Lo << std::endl;

    return 0;
}
