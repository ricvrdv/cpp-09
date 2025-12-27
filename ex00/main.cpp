#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	(void)argv;
	// Handle no argument
	if (argc < 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	// Load database into container
	std::map<std::string, double> btcDatabase;
	std::string	filename = "data.csv";
	
	std::ifstream databaseFile(filename.c_str());
	if (!databaseFile.is_open()) {
		std::cerr << "Error: could not open database file." << std::endl;
		return 1;
	}

	std::string	line;
	std::getline(databaseFile, line);

	while (std::getline(databaseFile, line)) {
		std::istringstream inputStream(line);
		std::string	date;
		std::string value;

		std::getline(inputStream, date, ',');
		std::getline(inputStream, value);

		btcDatabase[date] = std::stod(value);
	}

	for (std::map<std::string, double>::iterator it = btcDatabase.begin(); it != btcDatabase.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}

	databaseFile.close();
	return 0;
}
