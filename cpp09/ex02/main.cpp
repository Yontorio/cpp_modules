#include "PmergeMe.hpp"

#include <list>
#include <ctime>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <stdexcept>

static std::list<int> validateInput(int argc, char **argv)
{
	std::list<int> values;

	for (int i = 1; i < argc; ++i)
	{
		std::string str(argv[i]);
		if (str.empty())
			throw std::runtime_error("Error");

		size_t pos = 0;
		if (str[0] == '+')
			pos = 1;
		if (pos == str.length()
			|| str.find_first_not_of("0123456789", pos) != std::string::npos)
			throw std::runtime_error("Error");

        long value;
		std::stringstream ss(str);
		if (!(ss >> value) || value <= 0 || value > INT_MAX)
			throw std::runtime_error("Error");

		values.push_back(static_cast<int>(value));
	}
	return values;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::list<int> values;
	try
	{
		values = validateInput(argc, argv);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::cout << "Before: ";
	std::list<int>::const_iterator it = values.begin();
	while (it != values.end())
	{
		std::cout << *it;
		++it;
		if (it != values.end())
			std::cout << " ";
	}
	std::cout << std::endl;

	
	std::vector<int> vec;
	for (std::list<int>::const_iterator it = values.begin(); it != values.end(); ++it)
		vec.push_back(*it);
	clock_t start_vec = clock();
	PmergeMe::sort(vec);
	clock_t end_vec = clock();

	
	std::deque<int> deq;
	for (std::list<int>::const_iterator it = values.begin(); it != values.end(); ++it)
		deq.push_back(*it);
	clock_t start_deq = clock();
	PmergeMe::sort(deq);
	clock_t end_deq = clock();

    std::cout << "After:  ";
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << (i + 1 == vec.size() ? "" : " ");
	std::cout << std::endl;

	double time_vec = static_cast<double>(end_vec - start_vec) * 1000000.0 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << vec.size()
			  << " elements with std::vector : "
			  << std::fixed << std::setprecision(2)
			  << time_vec << " us" << std::endl;

	double time_deq = static_cast<double>(end_deq - start_deq) * 1000000.0 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << deq.size()
			  << " elements with std::deque  : "
			  << std::fixed << std::setprecision(2)
			  << time_deq << " us" << std::endl;

	return 0;
}

