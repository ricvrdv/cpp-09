#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <cmath>
# include <map>

class   BitcoinExchange {
    private:
        std::map<std::string, double> database_;

        bool    isValidDate(const std::string& date) const;
        bool    isValidValue(const std::string& valueStr, double& value) const;

    public:
        BitcoinExchange();
        BitcoinExchange( const BitcoinExchange &other );
        BitcoinExchange& operator=( const BitcoinExchange &other );
        ~BitcoinExchange();

        bool    loadDatabase(const std::string& filename);
        void    processInputLine(const std::string& line) const;

        std::map<std::string, double>&   getDatabase();
};

#endif
