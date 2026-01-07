#include "RPN.hpp"

// Default Constructor
RPN::RPN() {}

// Copy Constructor
RPN::RPN( const RPN &other ) {
    *this = other;
}

// Copy Assignment Operator
RPN&    RPN::operator=( const RPN &other ) {
    if (this == &other ) {
    }
    return *this;
}

// Destructor
RPN::~RPN() {}
