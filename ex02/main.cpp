#include "PmergeMe.hpp"

int main() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(3);
    vec.push_back(6);
    vec.push_back(1);
    vec.push_back(13);
    PmergeMe pMerge(vec);
    std::vector<int> cont = pMerge.getVec();
    for (size_t i = 0; i < cont.size(); i++) {
        std::cout << cont[i] << std::endl;
    }
}