#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	// 1. Handle no argument
	if (argc < 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	// 2. Load database into container
	BitcoinExchange	btc;
	if (!btc.loadDatabase("data.csv")) {
		return 1;
	}

	// 3. Handle input file
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
		return 1;
	}

	/*for (std::map<std::string, double>::iterator it = btc.getDatabase().begin(); it != btc.getDatabase().end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}*/

	while (std::getline(inputFile, line)) {
		btc.processInputLine(line);
	}

	inputFile.close();
	return 0;
}
