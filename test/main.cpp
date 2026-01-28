#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error\nUsage: " << argv[0]
                  << " <positive_integer_sequence>" << std::endl;
        return 1;
    }
    PmergeMe sorter;
    // Check if input is a valid sequence
    sorter.validateInput(argc, argv);
    
    // Display unsorted input sequence
    std::cout << "Before: " << sorter.getInputSequence() << std::endl;

    // Create containers with the valid sequence
    sorter.buildContainers();

    std::vector<int> vec = sorter.getVector();
    sorter.mergeInsertionVector(vec);
    //printContainer(generateJacobsthalSeq(20));
    //printContainer(sorter.getVector());
    //printContainer(sorter.getDeque());

    // Handle input errors, maybe with try / catch
    // Validate input: argc >= 2 Example: ./PmergeMe 4 2 5 1 OR ./PmergeMe "4 2 5 1" OR ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
    //  - only positive integers
    //  - no duplicates
    // print "Before: ..."
    //std::cout << "Before: " << sorter.getInputSequence() << std::endl;
    // Use class methods to sort the container sequence using Ford-Johnson Algorithm
    //  - Jacobsthal sequence: J(0)=0, J(1)=1, J(n)=J(n-1) + 2*J(n-2) [used to determine which pending element to insert next]
    //sorter.sortVector();
    //sorter.sortDeque();
    // print "After: ..."
    //std::cout << "After: " << sorter.getSortedSequence() << std::endl;
    // print "Time to process a range of n elements with std::[..] : ... us"
    // print "Time to process a range of n elements with std::[..] : ... us"
    return 0;
}
