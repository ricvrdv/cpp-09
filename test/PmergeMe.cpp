#include "PmergeMe.hpp"

// Default Constructor
PmergeMe::PmergeMe() {}

// Parametric Constructor
PmergeMe::PmergeMe(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        int num = std::strtol(argv[i], NULL, 10);
        this->vec_.push_back(num);
    }
}

// Copy Constructor
PmergeMe::PmergeMe(const PmergeMe &other) : vec_(other.vec_) {}

// Copy Assignment Operator
PmergeMe&   PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        this->vec_ = other.vec_;
        //this->deq_ = other.deq_;
    }
    return *this;
}

// Destructor
PmergeMe::~PmergeMe() {}

const std::vector<int>&   PmergeMe::getVec() const {
    return this->vec_;
}

void    PmergeMe::displayCont() const {
    if (vec_.empty()) {
        std::cout << "Vector is empty" << std::endl;
        return;
    }
    for (size_t i = 0; i < vec_.size(); i++) {
        std::cout << vec_[i];
        if (i < vec_.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void    PmergeMe::displaySeq(std::vector<int>& cont) const {
    for (size_t i = 0; i < cont.size(); i++) {
        std::cout << cont[i];
        if (i < cont.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void    PmergeMe::displaySeq2(std::vector<size_t>& cont) const {
    for (size_t i = 0; i < cont.size(); i++) {
        std::cout << cont[i];
        if (i < cont.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

std::vector<size_t> generateJacobsthalSeq(size_t n) {
    std::vector<size_t> seq;
    seq.push_back(1);
    seq.push_back(3);
    while (seq.back() < n) {
        size_t next = seq[seq.size() -1] + 2 * seq[seq.size() - 2];
        seq.push_back(next);
    }
    return seq;
}

void    PmergeMe::sortVector_() {
    size_t vecSize = vec_.size();
    if (vecSize <= 1) {
        return;
    }

    std::vector<std::pair<int, int> >    pairs;
    int     stray = -1;
    bool    hasStray = false;
    if (vecSize % 2 != 0) {
        hasStray = true;     
    }

    if (hasStray) {
        stray = vec_.back();
        vec_.pop_back();
    }

    for (size_t i = 0; i < vec_.size(); i += 2) {
        if (vec_[i] > vec_[i + 1]) {
            pairs.push_back(std::make_pair(vec_[i], vec_[i + 1]));
        }
        else {
            pairs.push_back(std::make_pair(vec_[i + 1], vec_[i]));
        }
    }

    for (size_t i = 0; i < pairs.size(); i++) {
        std::cout << "(" << pairs[i].first << " " << pairs[i].second << ") ";
    }

    if (hasStray) {
        std::cout << stray << std::endl;
    }

    std::cout << std::endl;

    std::vector<int>    mainChain;
    for (size_t i = 0; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].first);
    }
    displaySeq(mainChain);
    if (mainChain.size() > 1) {
        PmergeMe sorter;
        sorter.vec_ = mainChain;
        sorter.sortVector_();
        mainChain = sorter.vec_;
    }
    displaySeq(mainChain);

    std::vector<int>    pendingChain;
    for (std::vector<int>::iterator itMain = mainChain.begin(); itMain != mainChain.end(); itMain++) {
        for (std::vector< std::pair<int, int> >::iterator itPair = pairs.begin(); itPair != pairs.end(); itPair++) {
            if (itPair->first == *itMain) {
                pendingChain.push_back(itPair->second);
                break;
            }
        }
    }
    std::cout << "Pending: ";
    displaySeq(pendingChain);

    std::vector<size_t> jacobSeq = generateJacobsthalSeq(pendingChain.size());
    std::cout << "Jacobsthal Sequence: ";
    displaySeq2(jacobSeq);
    size_t  inserted = 0;
    for (size_t j = 0; j < jacobSeq.size() && inserted < pendingChain.size(); j++) {
        size_t index = std::min(jacobSeq[j], pendingChain.size());
        for (; inserted < index; inserted++) {
            size_t pos = binarySearchInsert(mainChain, pendingChain[inserted], 0, mainChain.size());
            mainChain.insert(mainChain.begin() + pos, pendingChain[inserted]);
        }
    }

    /* if (!pendingChain.empty()) {
        int firstPending = pendingChain[0];
        size_t pos = binarySearchInsert(mainChain, firstPending, 0, mainChain.size());
        mainChain.insert(mainChain.begin() + pos, firstPending);
        displaySeq(mainChain);
    } */

    if (hasStray) {
        size_t pos = binarySearchInsert(mainChain, stray, 0, mainChain.size());
        mainChain.insert(mainChain.begin() + pos, stray);
    }

    vec_ = mainChain;
    displaySeq(vec_);
}

size_t  PmergeMe::binarySearchInsert(const std::vector<int>& cont, int value, size_t left, size_t right) {
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (cont[mid] < value) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return left;
}
