#include "PmergeMe.hpp"

// Default Constructor
PmergeMe::PmergeMe() {}

// Copy Constructor
PmergeMe::PmergeMe(const PmergeMe &other) : vec_(other.vec_) {}

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

// Helper function to check if number is a positive integer
bool PmergeMe::isDigitsOnly(const std::string &s) {
    if (s.empty()) {
        return false;
    }

    for (size_t i = 0; i < s.length(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    return true;
}

// Helper function to convert string to int
int     PmergeMe::toInt(const std::string &s) {
    char *endptr;
    long value;

    value = std::strtol(s.c_str(), &endptr, 10);
    if (*endptr != '\0') {
        throw InvalidInputException("Invalid number format");
    }
    if (value <= 0) {
        throw InvalidInputException("Number must be positive");
    }
    if (value > INT_MAX) {
        throw InvalidInputException("Number exceeds maximum value");
    }
    
    return static_cast<int>(value);
}

// Validate input and build input sequence string
void    PmergeMe::validateInput(int argc, char **argv) {
    std::set<int> seen;
    std::ostringstream oss;
    bool isFirstElement = true;

    for (int i = 1; i < argc; i++) {
        std::istringstream iss(argv[i]);
        std::string token;

        while (iss >> token) {
            if (!isDigitsOnly(token)) {
                throw InvalidInputException("Invalid token: must be positive integer");
            }
            int value = toInt(token);

            if (!seen.insert(value).second)
                throw DuplicateValueException();

            if (!isFirstElement) {
                oss << " ";
            }
            oss << value;
            isFirstElement = false;
        }
    }
    if (isFirstElement)
        throw EmptyInputException();

    inputSequence_ = oss.str();
}

// Sort containers
void    PmergeMe::sortContainers() {
    // Measure vector: build container + sort
    clock_t startVec = clock();
    std::istringstream issVec(inputSequence_);
    int value;
    vec_.clear();
    while (issVec >> value) {
        vec_.push_back(value);
    }
    mergeInsertSortVector(vec_);
    clock_t endVec = clock();
    timeTakenVec_ = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
 
    // Measure deque: build container + sort
    clock_t startDeq = clock();
    std::istringstream issDeq(inputSequence_);
    deq_.clear();
    while (issDeq >> value) {
        deq_.push_back(value);
    }
    mergeInsertSortDeque(deq_);
    clock_t endDeq = clock();
    timeTakenDeq_ = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;
}

/*================================================================================
    FORD-JOHNSON MERGE-INSERTION SORT - VECTOR IMPLEMENTATION
    
    Steps:
    1. Pair elements and ensure larger element is first in each pair
    2. Recursively sort the sequence of larger elements
    3. Insert smaller elements using Jacobsthal sequence ordering
       to minimize comparisons during binary insertion
================================================================================*/

void    PmergeMe::sortPairsVector(std::vector<std::pair<int, int> >& pairs) {
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first < pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
}

void    PmergeMe::mergeInsertSortVector(std::vector<int>& vec) {
    if (vec.size() <= 1) {
        return;
    }
    
    // Group elements into pairs
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
    }

    // Check for unpaired element
    int unpaired = 0;
    if (vec.size() % 2 != 0) {
        unpaired = vec.back();
    }

    // Sort each pair (larger first)
    sortPairsVector(pairs);

    // Recursively sort the larger elements of each pair
    std::vector<int> sortedSequence;
    for (size_t i = 0; i < pairs.size(); i++) {
        sortedSequence.push_back(pairs[i].first);
    }
    if (sortedSequence.size() > 1) {
        mergeInsertSortVector(sortedSequence);
    }

    // Sequence of the smaller elements to be inserted into the sorted sequence
    std::vector<int> remainingElements;
    for (size_t i = 0; i < pairs.size(); i++) {
        remainingElements.push_back(pairs[i].second);
    }

    // Insert at the start of the sorted sequence the element that was paired 
    // with the first and smallest element of the sequence
    if (!remainingElements.empty()) {
        sortedSequence.insert(sortedSequence.begin(), remainingElements[0]);
    }

    // Generate insertion order using Jacobsthal numbers for the insertion sequence
    std::vector<int> insertionOrder;
    std::vector<int> insertionSequence;
    generateInsertionSequence(remainingElements.size(), insertionSequence);

    for (size_t i = 1; i < insertionSequence.size(); i++) {
        int start = insertionSequence[i-1];
        int end = std::min(insertionSequence[i], static_cast<int>(remainingElements.size()));
        for (int j = end - 1; j >= start; j--) {
            insertionOrder.push_back(j);
        }
    }

    // Insert remaining elements into the sorted sequence
    for (size_t i = 0; i < insertionOrder.size(); i++) {
        int index = insertionOrder[i];
        if (index < static_cast<int>(remainingElements.size())) {
            int valueToInsert = remainingElements[index];
            // Binary search to find the correct position to insert
            std::vector<int>::iterator pos = std::lower_bound(sortedSequence.begin(), sortedSequence.end(), valueToInsert);
            sortedSequence.insert(pos, valueToInsert);
        }
    }

    if (unpaired != 0) {
        // Insert the unpaired element
        std::vector<int>::iterator pos = std::lower_bound(sortedSequence.begin(), sortedSequence.end(), unpaired);
        sortedSequence.insert(pos, unpaired);
    }

    // Update the original vector with the sorted sequence
    vec = sortedSequence;
}

/*================================================================================
    FORD-JOHNSON MERGE-INSERTION SORT - DEQUE IMPLEMENTATION
    
    Identical algorithm to vector version, using std::deque for comparison
    of performance characteristics between contiguous and chunked memory.
================================================================================*/

void    PmergeMe::sortPairsDeque(std::deque<std::pair<int, int> >& pairs) {
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first < pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
}

void    PmergeMe::mergeInsertSortDeque(std::deque<int>& deq) {
    if (deq.size() <= 1) {
        return;
    }
    
    // Group elements into pairs
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
    }

    // Check for unpaired element
    int unpaired = 0;
    if (deq.size() % 2 != 0) {
        unpaired = deq.back();
    }

    // Sort each pair (larger first)
    sortPairsDeque(pairs);

    // Recursively sort the larger elements of each pair
    std::deque<int> sortedSequence;
    for (size_t i = 0; i < pairs.size(); i++) {
        sortedSequence.push_back(pairs[i].first);
    }
    if (sortedSequence.size() > 1) {
        mergeInsertSortDeque(sortedSequence);
    }

    // Sequence of the smaller elements to be inserted into the sorted sequence
    std::deque<int> remainingElements;
    for (size_t i = 0; i < pairs.size(); i++) {
        remainingElements.push_back(pairs[i].second);
    }

    // Insert at the start of the sorted sequence the element that was paired 
    // with the first and smallest element of the sequence
    if (!remainingElements.empty()) {
        sortedSequence.insert(sortedSequence.begin(), remainingElements[0]);
    }

    // Generate insertion order using Jacobsthal numbers for the insertion sequence
    std::deque<int> insertionOrder;
    std::deque<int> insertionSequence;
    generateInsertionSequence(remainingElements.size(), insertionSequence);

    for (size_t i = 1; i < insertionSequence.size(); i++) {
        int start = insertionSequence[i-1];
        int end = std::min(insertionSequence[i], static_cast<int>(remainingElements.size()));
        for (int j = end - 1; j >= start; j--) {
            insertionOrder.push_back(j);
        }
    }

    // Insert remaining elements into the sorted sequence
    for (size_t i = 0; i < insertionOrder.size(); i++) {
        int index = insertionOrder[i];
        if (index < static_cast<int>(remainingElements.size())) {
            int valueToInsert = remainingElements[index];
            // Binary search to find the correct position to insert
            std::deque<int>::iterator pos = std::lower_bound(sortedSequence.begin(), sortedSequence.end(), valueToInsert);
            sortedSequence.insert(pos, valueToInsert);
        }
    }

    if (unpaired != 0) {
        // Insert the unpaired element
        std::deque<int>::iterator pos = std::lower_bound(sortedSequence.begin(), sortedSequence.end(), unpaired);
        sortedSequence.insert(pos, unpaired);
    }

    // Update the original vector with the sorted sequence
    deq = sortedSequence;
}

const std::string&  PmergeMe::getInputSequence() const {
    return inputSequence_;
}

const double &PmergeMe::getTimeVector() const {
    return timeTakenVec_;
}

const double &PmergeMe::getTimeDeque() const {
    return timeTakenDeq_;
}

const std::vector<int>& PmergeMe::getVector() const {
    return vec_;
}

const std::deque<int>& PmergeMe::getDeque() const {
    return deq_;
}

/*================================================================================
    CUSTOM EXCEPTIONS
================================================================================*/

PmergeMe::InvalidInputException::InvalidInputException(const std::string& msg) : message_(msg) {}

PmergeMe::InvalidInputException::~InvalidInputException() throw() {}

const char  *PmergeMe::InvalidInputException::what() const throw() {
    return message_.c_str();
}

const char  *PmergeMe::DuplicateValueException::what() const throw() {
    return "Duplicate value found";
}

const char  *PmergeMe::EmptyInputException::what() const throw() {
    return "Empty input sequence";
}