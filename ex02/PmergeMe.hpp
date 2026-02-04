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
# include <exception>

class PmergeMe {
    private:
        std::string inputSequence_;
        std::vector<int> vec_;
        std::deque<int> deq_;
        double  timeTakenVec_;
        double  timeTakenDeq_;

        void    mergeInsertSortVector(std::vector<int>& vec);
        void    sortPairsVector(std::vector<std::pair<int, int> >& pairs);

        void    mergeInsertSortDeque(std::deque<int>& deq);
        void    sortPairsDeque(std::deque<std::pair<int, int> >& pairs);

        template <typename Container>
        void    generateInsertionSequence(size_t size, Container &insertionSequence);

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();
        
        void    validateInput(int argc, char **argv);
        void    buildContainers();
        void    sortContainers();
        
        template <typename Container1, typename Container2>
        bool    sequencesEqual(const Container1 &seq1, const Container2 &seq2);

        template <typename Container>
        void    printContainer(const Container& cont) const;

        const std::string &getInputSequence() const;
        const double &getTimeVector() const;
        const double &getTimeDeque() const;
        const std::vector<int>& getVector() const;
        const std::deque<int>& getDeque() const;
};

template <typename Container>
void    PmergeMe::generateInsertionSequence(size_t size, Container &insertionSequence) {
    insertionSequence.clear();
    if (size <= 0) {
        return;
    }
            
    insertionSequence.push_back(1);
    if (size <= 1) {
        return;
    }
    
    insertionSequence.push_back(3);
    if (size <= 2) {
        return;
    }
    
    for (size_t i =2; i < size; i++) {
        size_t next = insertionSequence[i-1] + 2 * insertionSequence[i-2];
        if (next > size) {
            break;
        }
        insertionSequence.push_back(next);
    }
}

template <typename Container1, typename Container2>
bool    PmergeMe::sequencesEqual(const Container1 &seq1, const Container2 &seq2) {
    if (seq1.size() != seq2.size()) {
        return false;
    }

    typename Container1::const_iterator it1 =seq1.begin();
    typename Container2::const_iterator it2 =seq2.begin();

    while (it1 != seq1.end() && it2 != seq2.end()) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }

    return true;
}

template <typename Container>
void    PmergeMe::printContainer(const Container& cont) const {
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
