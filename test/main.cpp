#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error\nUsage: " << argv[0]
                  << " <positive_integer_sequence>" << std::endl;
        return 1;
    }
    // Validate input: argc >= 2 Example: ./PmergeMe 4 2 5 1 OR ./PmergeMe "4 2 5 1" OR ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
    //  - only positive integers
    //  - no duplicates
    // print "Before: ..."
    // Instantiate PmergeMe object for std::vector<int> container
    PmergeMe    vec(argc, argv);
    // Use class methods to sort the container sequence using Ford-Johnson Algorithm
    //  - Jacobsthal sequence: J(0)=0, J(1)=1, J(n)=J(n-1) + 2*J(n-2) [used to determine which pending element to insert next]
    vec.sortVector_();
    // print "After: ..."
    // print "Time to process a range of n elements with std::[..] : ... us"
    // print "Time to process a range of n elements with std::[..] : ... us"
    return 0;
}