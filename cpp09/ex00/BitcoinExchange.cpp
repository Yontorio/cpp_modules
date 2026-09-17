#include "BitcoinExchange.hpp"

#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string &filename) { loadDataBase(filename); }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _dataBase(other._dataBase) { }

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other) { _dataBase = other._dataBase; }
	return *this;
}

BitcoinExchange::~BitcoinExchange() { }

void BitcoinExchange::loadDataBase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error opening file");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date;
		double value;

		if (std::getline(ss, date, ',') && (ss >> value))
		{
			_dataBase[date] = value;
		}
	}
}

double BitcoinExchange::getRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _dataBase.lower_bound(date);

	if (it == _dataBase.begin())
		throw std::runtime_error("Error: no earlier date available.");

	if (it != _dataBase.end() && it->first == date)
		return it->second;

	return (--it)->second;
}

static bool isNumber(const std::string &str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return true;
}

static bool hasNoSurroundingWhitespace(const std::string &str)
{
	if (str.empty())
		return false;

	if (std::isspace(static_cast<unsigned char>(str[0]))
		|| std::isspace(static_cast<unsigned char>(str[str.length() - 1])))
		return false;

	return true;
}

std::string BitcoinExchange::parseDate(const std::string &str) const
{
	if (!hasNoSurroundingWhitespace(str))
		throw std::runtime_error("Error: bad input => " + str);

	std::stringstream ss(str);

	std::string year;
	std::string month;
	std::string day;

	if (!std::getline(ss, year, '-')
		|| !std::getline(ss, month, '-')
		|| !std::getline(ss, day))
		throw std::runtime_error("Error: bad input => " + str);

	if (year.empty() || month.length() != 2 || day.length() != 2
		|| !isNumber(year) || !isNumber(month) || !isNumber(day))
		throw std::runtime_error("Error: bad input => " + str);

	return str;
}

double BitcoinExchange::parseValue(const std::string &str) const
{
	if (!hasNoSurroundingWhitespace(str))
		throw std::runtime_error("Error: bad input => " + str);

	char *end;
	double value = std::strtod(str.c_str(), &end);

	if (end == str.c_str() || *end != '\0')
		throw std::runtime_error("Error: bad input => " + str);

	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");

	if (value > 1000)
		throw std::runtime_error("Error: too large a number.");

	return value;
}

void BitcoinExchange::processInputFile(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	std::getline(file, line);

	if (line != "date | value")
		throw std::runtime_error("Invalid input header: " + line);

	while (std::getline(file, line))
	{
		size_t pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		try
		{
			std::string date = parseDate(line.substr(0, pos));
			double value = parseValue(line.substr(pos + 3));
			double rate = getRate(date);
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
