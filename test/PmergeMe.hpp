#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <cstdlib>
# include <climits>
# include <vector>
# include <deque>
# include <set>

class PmergeMe {
    private:
        std::string inputSequence_;
        std::vector<int> vec_;
        std::deque<int> deq_;

        //std::string sortedSequence_;
        // Should I store the sequence in unsortedVec_ and sortedVec_?

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();
        //PmergeMe(int argc, char **argv);
        
        void    validateInput(int argc, char **argv);
        void    buildContainers();
        const std::string &getInputSequence() const;
        const std::vector<int>& getVector() const;
        const std::deque<int>& getDeque() const;

        //const std::vector<int>& getVec() const;
        //void    displayCont() const;
        //void    displaySeq(std::vector<int>& cont) const;
        //void    displaySeq2(std::vector<size_t>& cont) const;
        //void    sortVector_();
        //size_t  binarySearchInsert(const std::vector<int>& cont, int value, size_t left, size_t right);
};

const std::vector<size_t> generateJacobsthalSeq(size_t n);

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
