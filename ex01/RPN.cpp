#include "RPN.hpp"

// Default Constructor
RPN::RPN() {}

// Copy Constructor
RPN::RPN( const RPN &other ) {
    *this = other;
}

// Copy Assignment Operator
RPN&    RPN::operator=( const RPN &other ) {
    if ( this != &other ) {
        this->stack_ = other.stack_;
    }
    return *this;
}

// Destructor
RPN::~RPN() {}

// Member Function
int RPN::evaluate( const std::string &str ) {
    std::istringstream inputStream(str);
    std::string token;
    
    while ( inputStream >> token ) {
        if ( token.size() == 1 && std::isdigit(token[0]) ) {
            this->stack_.push(token[0] - '0');
        }
        else if ( token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos ) {
            if ( this->stack_.size() < 2 ) {
                throw std::runtime_error("Error");
            }
            
            int rightOp = this->stack_.top();
            this->stack_.pop();
            int leftOp = this->stack_.top();
            this->stack_.pop();

            switch (token[0]) {
                case '+':
                    this->stack_.push(leftOp + rightOp);
                    break;
                case '-':
                    this->stack_.push(leftOp - rightOp);
                    break;
                case '*':
                    this->stack_.push(leftOp * rightOp);
                    break;
                case '/':
                    if (rightOp == 0) {
                        throw std::runtime_error("Error");
                    }
                    this->stack_.push(leftOp / rightOp);
                    break;
            }
        }
        else {
            throw std::runtime_error("Error");
        }
    }

    if (this->stack_.size() != 1) {
        throw std::runtime_error("Error");
    }

    return this->stack_.top();
}
