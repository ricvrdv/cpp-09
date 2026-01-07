#include "RPN.hpp"

int main( int argc, char **argv ) {
    if ( argc != 2 ) {
        std::cerr << "Error\nUsage: ./RPN \"...\"" << std::endl;
    }

    //if character other than "0123456789+-*/ " print Error in std::cerr
    "8 9 * 9 - 9 - 9 - 4 - 1 +"

    [8] skip " " [8, 9] skip " " if "+-*/" {8 * 9} [72] skip " " [72, 9] skip " " if "+-*/" {72 - 9} ...

    return 0;
}
