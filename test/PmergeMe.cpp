#include "PmergeMe.hpp"

// Default Constructor
PmergeMe::PmergeMe() {}

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

// Helper function to check if number is a positive integer
bool isPositiveInteger(const std::string &s) {
    if (s.empty()) {
        return false;
    }

    for (size_t i = 0; i < s.length(); i++) {
        if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

// Helper function to convert string to int
int     toInt(const std::string &s) {
    std::istringstream iss(s);
    long value;

    iss >> value;
    if (iss.fail() || !iss.eof()) {
        throw std::runtime_error("Invalid number");
    }
    if (value <= 0 || value > INT_MAX)
        throw std::runtime_error("Out of range");
    return static_cast<int>(value);
}

// Validate input and build input sequence string
void    PmergeMe::validateInput(int argc, char **argv) {
    std::set<int> seen;
    std::ostringstream oss;
    bool first = true;

    for (int i = 1; i < argc; i++) {
        std::istringstream iss(argv[i]);
        std::string token;

        while (iss >> token) {
            if (!isPositiveInteger(token)) {
                throw std::runtime_error("Invalid token");
            }
            int value = toInt(token);

            if (!seen.insert(value).second)
                throw std::runtime_error("Duplicate");

            if (!first) {
                oss << " ";
            }
            oss << value;
            first = false;
        }
    }
    if (first)
        throw std::runtime_error("Empty input");

    inputSequence_ = oss.str();
}

// Build containers from the input sequence
void    PmergeMe::buildContainers() {
    std::istringstream iss(inputSequence_);
    int value;

    vec_.clear();
    deq_.clear();
    while (iss >> value) {
        vec_.push_back(value);
        deq_.push_back(value);
    }
}

// Get the input sequence as a string
const std::string&  PmergeMe::getInputSequence() const {
    return inputSequence_;
}

// Generate Jacobsthal sequence
// Jacobsthal sequence: J(0)=0, J(1)=1, J(n)=J(n-1) + 2*J(n-2)
const std::vector<size_t> generateJacobsthalSeq(size_t n) {
    std::vector<size_t> jacobsthalSeq;

    if (n == 0) {
        return jacobsthalSeq;
    }
    jacobsthalSeq.reserve(n);
    jacobsthalSeq.push_back(0);
    if (n == 1) {
        return jacobsthalSeq;
    }
    jacobsthalSeq.push_back(1);
    for (size_t i = 2; i < n; i++) {
        jacobsthalSeq.push_back(jacobsthalSeq[i - 1] + 2 * jacobsthalSeq[i - 2]);
    }
    return jacobsthalSeq;
}

const std::vector<int>& PmergeMe::getVector() const {
    return vec_;
}

const std::deque<int>& PmergeMe::getDeque() const {
    return deq_;
}

static void makePairs(const std::vector<int> &input,
    std::vector<ElementPair> &pairs,
    bool &hasOdd, ValueIndex &oddElement) {
    pairs.clear();
    hasOdd = false;

    std::size_t n = input.size();
    std::size_t i = 0;
}

void    PmergeMe::mergeInsertionVector(std::vector<int>& vec) {

}

// // Parametric Constructor
// PmergeMe::PmergeMe(int argc, char **argv) {
//     for (int i = 1; i < argc; i++) {
//         int num = std::strtol(argv[i], NULL, 10);
//         this->vec_.push_back(num);
//     }
// }

// const std::vector<int>&   PmergeMe::getVec() const {
//     return this->vec_;
// }

// void    PmergeMe::displayCont() const {
//     if (vec_.empty()) {
//         std::cout << "Vector is empty" << std::endl;
//         return;
//     }
//     for (size_t i = 0; i < vec_.size(); i++) {
//         std::cout << vec_[i];
//         if (i < vec_.size() - 1) {
//             std::cout << " ";
//         }
//     }
//     std::cout << std::endl;
// }

// void    PmergeMe::displaySeq(std::vector<int>& cont) const {
//     for (size_t i = 0; i < cont.size(); i++) {
//         std::cout << cont[i];
//         if (i < cont.size() - 1) {
//             std::cout << " ";
//         }
//     }
//     std::cout << std::endl;
// }

// void    PmergeMe::displaySeq2(std::vector<size_t>& cont) const {
//     for (size_t i = 0; i < cont.size(); i++) {
//         std::cout << cont[i];
//         if (i < cont.size() - 1) {
//             std::cout << " ";
//         }
//     }
//     std::cout << std::endl;
// }

// std::vector<size_t> generateJacobsthalSeq(size_t n) {
//     std::vector<size_t> seq;
//     seq.push_back(1);
//     seq.push_back(3);
//     while (seq.back() < n) {
//         size_t next = seq[seq.size() -1] + 2 * seq[seq.size() - 2];
//         seq.push_back(next);
//     }
//     return seq;
// }

// void    PmergeMe::sortVector_() {
//     size_t vecSize = vec_.size();
//     if (vecSize <= 1) {
//         return;
//     }

//     std::vector<std::pair<int, int> >    pairs;
//     int     stray = -1;
//     bool    hasStray = false;
//     if (vecSize % 2 != 0) {
//         hasStray = true;     
//     }

//     if (hasStray) {
//         stray = vec_.back();
//         vec_.pop_back();
//     }

//     for (size_t i = 0; i < vec_.size(); i += 2) {
//         if (vec_[i] > vec_[i + 1]) {
//             pairs.push_back(std::make_pair(vec_[i], vec_[i + 1]));
//         }
//         else {
//             pairs.push_back(std::make_pair(vec_[i + 1], vec_[i]));
//         }
//     }

//     for (size_t i = 0; i < pairs.size(); i++) {
//         std::cout << "(" << pairs[i].first << " " << pairs[i].second << ") ";
//     }

//     if (hasStray) {
//         std::cout << stray << std::endl;
//     }

//     std::cout << std::endl;

//     std::vector<int>    mainChain;
//     for (size_t i = 0; i < pairs.size(); i++) {
//         mainChain.push_back(pairs[i].first);
//     }
//     displaySeq(mainChain);
//     if (mainChain.size() > 1) {
//         PmergeMe sorter;
//         sorter.vec_ = mainChain;
//         sorter.sortVector_();
//         mainChain = sorter.vec_;
//     }
//     displaySeq(mainChain);

//     std::vector<int>    pendingChain;
//     for (std::vector<int>::iterator itMain = mainChain.begin(); itMain != mainChain.end(); itMain++) {
//         for (std::vector< std::pair<int, int> >::iterator itPair = pairs.begin(); itPair != pairs.end(); itPair++) {
//             if (itPair->first == *itMain) {
//                 pendingChain.push_back(itPair->second);
//                 break;
//             }
//         }
//     }
//     std::cout << "Pending: ";
//     displaySeq(pendingChain);

//     std::vector<size_t> jacobSeq = generateJacobsthalSeq(pendingChain.size());
//     std::cout << "Jacobsthal Sequence: ";
//     displaySeq2(jacobSeq);
//     size_t  inserted = 0;
//     for (size_t j = 0; j < jacobSeq.size() && inserted < pendingChain.size(); j++) {
//         size_t index = std::min(jacobSeq[j], pendingChain.size());
//         for (; inserted < index; inserted++) {
//             size_t pos = binarySearchInsert(mainChain, pendingChain[inserted], 0, mainChain.size());
//             mainChain.insert(mainChain.begin() + pos, pendingChain[inserted]);
//         }
//     }

//     /* if (!pendingChain.empty()) {
//         int firstPending = pendingChain[0];
//         size_t pos = binarySearchInsert(mainChain, firstPending, 0, mainChain.size());
//         mainChain.insert(mainChain.begin() + pos, firstPending);
//         displaySeq(mainChain);
//     } */

//     if (hasStray) {
//         size_t pos = binarySearchInsert(mainChain, stray, 0, mainChain.size());
//         mainChain.insert(mainChain.begin() + pos, stray);
//     }

//     vec_ = mainChain;
//     displaySeq(vec_);
// }

// size_t  PmergeMe::binarySearchInsert(const std::vector<int>& cont, int value, size_t left, size_t right) {
//     while (left < right) {
//         size_t mid = left + (right - left) / 2;
//         if (cont[mid] < value) {
//             left = mid + 1;
//         }
//         else {
//             right = mid;
//         }
//     }
//     return left;
// }

