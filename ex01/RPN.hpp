#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>

class RPN {
    private:

    public:
        RPN();
        RPN( const RPN &other );
        RPN& operator=( const RPN &other );
        ~RPN();
};

#endif
