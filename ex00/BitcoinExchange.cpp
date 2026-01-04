# include "BitcoinExchange.hpp"

// Default Constructor
BitcoinExchange::BitcoinExchange() {}

// Copy Constructor
BitcoinExchange::BitcoinExchange( const BitcoinExchange &other ) {
    *this = other;
}

// Copy Assignment Operator
BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange &other ) {
    if (this != &other) {
        this->database_ = other.database_;
    }
    return *this;
}

// Destructor
BitcoinExchange::~BitcoinExchange() {}

// Public Member functions
bool    BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream   databaseFile(filename.c_str());
    if (!databaseFile.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return false;
    }

    std::string	line;
    if (!std::getline(databaseFile, line)) {
        std::cerr << "Error: database file is empty." << std::endl;
        return false;
    }

    if (line.compare("date,exchange_rate") != 0) {
		std::cerr << "Error: wrong database file header." << std::endl;
		return false;
	}

    while (std::getline(databaseFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream inputStream(line);
		std::string	date;
		std::string valueStr;

        if (!std::getline(inputStream, date, ',')) {
			std::cerr << "Error: invalid line in database." << std::endl;
            return false;
		}

		if (!std::getline(inputStream, valueStr)) {
            std::cerr << "Error: missing value." << std::endl;
			return false;
		}

        // Validate date (YYYY-MM-DD)
		if (!isValidDate(date)) {
			std::cerr << "Error: invalid date in database => " << date << std::endl;
			return false;
		}

        // Validate exchange rate value
		double	value;
		if (!isValidValue(valueStr, value, false)) {
			return false;
		}

        this->database_[date] = value;
    }

    databaseFile.close();
    return true;
}

void    BitcoinExchange::processInputLine(const std::string& line) const {
    if (line.empty()) {
        return;
    }

    std::istringstream  inputLine(line);
    std::string date;
    std::string valueStr;

    if (!std::getline(inputLine, date, '|')) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    if (!std::getline(inputLine, valueStr)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    while (!date.empty() && std::isspace(date[0])) date.erase(0, 1);
	while (!date.empty() && std::isspace(date[date.size()-1])) date.erase(date.size()-1);
	while (!valueStr.empty() && std::isspace(valueStr[0])) valueStr.erase(0, 1);
	while (!valueStr.empty() && std::isspace(valueStr[valueStr.size()-1])) valueStr.erase(valueStr.size()-1);

    if (!isValidDate(date)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    double  value;
    if (!isValidValue(valueStr, value, true)) {
        return;
    }

    std::map<std::string, double>::const_iterator it = database_.lower_bound(date);
    if (it == database_.end() || it->first != date) {
        if (it == database_.begin()) {
            return;
        }
        it--;
    }

    std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
}

// Private Member Functions
bool    BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    // Extract year, month, and day
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    static const int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    // Check if year is a leap year
    if (month == 2) {
        bool leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        
        if (day > (leapYear ? 29 : 28)) {
            return false;
        }
    }
    else if (day > daysInMonth[month]) {
        return false;
    }
    
    return true;
}

bool    BitcoinExchange::isValidValue(const std::string& valueStr, double& value, bool is_input) const {
    char    *end;
    const char  *cstr = valueStr.c_str();

    value = std::strtod(cstr, &end);
    if (end == cstr) {
        std::cerr << "Error: invalid number => " << valueStr << std::endl;
        return false;
    }

    if (*end != '\0') {
        std::cerr << "Error: trailing characters in number => " << valueStr << std::endl;
        return false;
    }

    if (std::isnan(value) || std::isinf(value)) {
        std::cerr << "Error: invalid number => " << valueStr << std::endl;
        return false;
    }

    if (value < 0) {
        std::cerr << "Error: not a positive number => " << valueStr << std::endl;
        return false;
    }

    if (is_input && value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }

    return true;
}

std::map<std::string, double>& BitcoinExchange::getDatabase() {
    return this->database_;
}