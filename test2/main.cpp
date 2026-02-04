#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error\nUsage: " << argv[0]
                  << " <positive_integer_sequence>" << std::endl;
        return 1;
    }
    
    PmergeMe sorter;
    // Check if input is a valid sequence
    try {
        sorter.validateInput(argc, argv);
    }
    catch (std::exception &e) {
        std::cerr << "Error\n" << e.what() << std::endl;
        return 1;
    }
    
    // Create containers with the valid sequence
    sorter.buildContainers();

    // Sort containers and measure time taken
    sorter.sortContainers();

    // Check if sorted sequence is the same in each container
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

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of "
        << sorter.getVector().size()
        << " elements with std::vector : "
        << sorter.getTimeVector()
        << " us" << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of "
        << sorter.getDeque().size()
        << " elements with std::deque : "
        << sorter.getTimeDeque()
        << " us" << std::endl;

    return 0;
}
