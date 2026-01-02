#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	// 1. Handle no argument
	if (argc < 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	// 2. Load database into container
	std::map<std::string, double> btcDatabase;
	if (!loadDatabase("data.csv", btcDatabase)) {
		return 1;
	}

	std::ifstream	inputFile(argv[1]);
	if (!inputFile.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
        return 1;
	}

	std::string	line;
	if (!std::getline(inputFile, line)) {
		std::cerr << "Error: input file is empty." << std::endl;
        return 1;
	}

	if (line.compare("date | value") != 0) {
		std::cerr << "Error: wrong input file header." << std::endl;
		return false;
	}
	
	for (std::map<std::string, double>::iterator it = btcDatabase.begin(); it != btcDatabase.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
	return 0;
}
