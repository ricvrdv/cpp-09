#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <cstdlib>
# include <climits>
# include <vector>
# include <deque>
# include <set>
# include <algorithm>

class PmergeMe {
    private:
        std::string inputSequence_;
        std::vector<int> vec_;
        std::deque<int> deq_;

        void    mergeInsertSortVector(std::vector<int>& vec);
        void    sortPairsVector(std::vector<std::pair<int, int> >& pairs);
        void    generateInsertionSequence(size_t size, std::vector<int>& insertionSequence);

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();
        
        void    validateInput(int argc, char **argv);
        void    buildContainers();
        void    sortContainers();
        const std::string &getInputSequence() const;
        const std::vector<int>& getVector() const;
        const std::deque<int>& getDeque() const;
};

template <typename Container>
void    printContainer(const Container& cont) {
    bool first = true;

    for (typename Container::const_iterator it = cont.begin(); it != cont.end(); it++) {
        if (!first) {
            std::cout << " ";
        }
        std::cout << *it;
        first = false;
    }
    std::cout << std::endl;
}

#endif
