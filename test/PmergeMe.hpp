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
        std::string sortedSequence_;
        
        std::vector<int> vec_;
        // Should I store the sequence in unsortedVec_ and sortedVec_?

    public:
        PmergeMe();
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();

        const std::vector<int>& getVec() const;
        void    displayCont() const;
        void    displaySeq(std::vector<int>& cont) const;
        void    displaySeq2(std::vector<size_t>& cont) const;
        void    sortVector_();
        size_t  binarySearchInsert(const std::vector<int>& cont, int value, size_t left, size_t right);
        void    validateInput(int argc, char **argv);
        void    buildContainers();
        const std::string &getInputSequence() const;
};

#endif
