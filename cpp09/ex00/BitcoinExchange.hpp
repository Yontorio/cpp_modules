#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <map>

class BitcoinExchange
{
    public:
        BitcoinExchange(const std::string &filename);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void processInputFile(const std::string &filename);

    private:
        BitcoinExchange();

        std::map<std::string, double> _dataBase;

        void loadDataBase(const std::string &filename);
        bool isValidDate(const std::string& date) const;
        double getRate(const std::string& date) const;
        std::string parseDate(const std::string &str) const;
        double parseValue(const std::string &str) const;
};

#endif
