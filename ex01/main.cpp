#include "RPN.hpp"

int main( int argc, char **argv ) {
    if ( argc != 2 ) {
        std::cerr << "Error\nUsage: ./RPN \"...\"" << std::endl;
        return 1;
    }

    std::string expr = argv[1];
    for ( size_t i = 0; i < expr.size(); i++ ) {
        char c = expr[i];
        if ( !std::isdigit(c) && std::string("+-*/ ").find(c) == std::string::npos ) {
            std::cerr << "Error" << std::endl;
            return 1;
        }
    }

    try {
        RPN rpn;
        int result = rpn.evaluate(expr);
        std::cout << result << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
