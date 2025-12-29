#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	(void)argv;
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
	
	for (std::map<std::string, double>::iterator it = btcDatabase.begin(); it != btcDatabase.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
	return 0;
}
