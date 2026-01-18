#include "PmergeMe.hpp"

// Default Constructor
PmergeMe::PmergeMe(std::vector<int>& cont) {
    this->vec_ = cont;
}

// Copy Constructor
PmergeMe::PmergeMe(const PmergeMe &other) {
    *this = other;
}

// Copy Assignment Operator
PmergeMe&   PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        this->vec_ = other.vec_;
        this->deq_ = other.deq_;
    }
    return *this;
}

// Destructor
PmergeMe::~PmergeMe() {}

std::vector<int>&   PmergeMe::getVec() {
    return this->vec_;
}

void    PmergeMe::sortVector_(std::vector<int>* cont) {
    int n = cont->size();
    if (n <= 1) {
        return;
    }

    for (size_t i = 0; cont->size(); i++) {
        std::cout << *cont[i] << std::endl;
    }
 
    std::vector<std::pair<int, int> >    pairs;
    int     stray = -1;
    bool    hasStray = false;
    if (n % 2 != 0) {
        hasStray = true;     
    }

    if (hasStray) {
        stray = cont->back();
        cont->pop_back();
    }

    for (size_t i = 0; i < cont->size(); i += 2) {
        if (cont[i] > cont[i + 1]) {
            pairs.push_back(std::make_pair(cont[i], cont[i + 1]));
        }
        else {
            pairs.push_back(std::make_pair(cont[i + 1], cont[i]));
        }
    }

    std::vector<int>    winners;
    for (size_t i = 0; i < pairs.size(); i++) {
        winners.push_back(pairs[i].first);
    }
    winners.push_back(stray);
}

void    PmergeMe::run(std::vector<int>& cont) {
    sortVector_(&cont);
    for (size_t i = 0; i < cont.size(); i++) {
        std::cout << cont[i] << std::endl;
    }
}