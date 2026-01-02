#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <cmath>
# include <map>

bool    loadDatabase(const std::string& filename, std::map<std::string, double> &database);
bool    isValidDate(const std::string& date);
bool    isValidValue(const std::string& valueStr, double& value);
void    processInputLine();

#endif
