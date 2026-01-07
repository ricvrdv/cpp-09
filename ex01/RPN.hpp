#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <stack>
# include <exception>

class RPN {
    private:
        std::stack<int> stack_;

    public:
        RPN();
        RPN( const RPN &other );
        RPN& operator=( const RPN &other );
        ~RPN();

        int evaluate( const std::string &str );
};

#endif
