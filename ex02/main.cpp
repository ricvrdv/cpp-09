#include "PmergeMe.hpp"

/*
 * PmergeMe - Ford-Johnson Merge-Insert Sort Implementation
 * 
 * Compares the performance of the Ford-Johnson algorithm using two different
 * STL containers: std::vector and std::deque. The program validates input,
 * sorts identical sequences using both containers, and reports timing metrics
 * to demonstrate performance differences between contiguous (vector) and
 * chunked (deque) memory layouts.
 */

void    printTimingResult(const std::string& containerName, size_t size, double time) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Time to process a range of "
        << size 
        << " elements with " << containerName << " : "
        << time
        << " us" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error\nUsage: " << argv[0]
                  << " <positive_integer_sequence>" << std::endl;
        return 1;
    }
    
    PmergeMe sorter;
    
    try {
        sorter.validateInput(argc, argv);
    }
    catch (std::exception &e) {
        std::cerr << "Error\n" << e.what() << std::endl;
        return 1;
    }

    // Build containers, sort them, and measure performance for each
    sorter.sortContainers();

    // Verify both implementations produce identical results
    std::vector<int> sortedVec = sorter.getVector();
    std::deque<int> sortedDeq = sorter.getDeque();

    if (!sorter.sequencesEqual(sortedVec, sortedDeq)) {
        std::cerr << "Error\nContainers have different sequences" << std::endl;
        return 1;
    }

    // Display unsorted input sequence
    std::cout << "Before: " << sorter.getInputSequence() << std::endl;

    // Display sorted sequence
    std::cout << "After: ";
    sorter.printContainer(sortedVec);

    printTimingResult("std::vector", sorter.getVector().size(), sorter.getTimeVector());
    printTimingResult("std::deque ", sorter.getDeque().size(), sorter.getTimeDeque());

    return 0;
}
