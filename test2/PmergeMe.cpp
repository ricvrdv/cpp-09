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

// Sort containers
void    PmergeMe::sortContainers() {
    // Sorting Vector
    // Clock start
    clock_t startVec = clock();
    // Merge Insertion Sort Vector
    mergeInsertSortVector(vec_);
    // Clock end
    clock_t endVec = clock();
    double timeTakenVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec_.size() << " elements with std::vector : " << timeTakenVec << " us" << std::endl;

    // Sorting Deque
    // Clock start
    // Merge Insertion Sort Deque
    // Clock end

    // Print time taken for both sorts
}

void    PmergeMe::sortPairsVector(std::vector<std::pair<int, int> >& pairs) {
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first < pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
}

void    PmergeMe::generateInsertionSequence(size_t size, std::vector<int>& insertionSequence) {
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

void    PmergeMe::mergeInsertSortVector(std::vector<int>& vec) {
    static int callCount = 0;
    callCount++;
    std::cout << "Call #" << callCount << ", size: " << vec.size() << std::endl;
    
    
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

// Get the input sequence as a string
const std::string&  PmergeMe::getInputSequence() const {
    return inputSequence_;
}

const std::vector<int>& PmergeMe::getVector() const {
    return vec_;
}

const std::deque<int>& PmergeMe::getDeque() const {
    return deq_;
}
