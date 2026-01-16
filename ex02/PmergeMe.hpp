#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>

class PmergeMe {
    private:
        std::vector<int>    vec_;
        std::deque<int>     deq_;

        void    sortVector_(std::vector<int>& cont);

    public:
        PmergeMe(std::vector<int>& cont);
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();

        std::vector<int>&   getVec();
};

#endif