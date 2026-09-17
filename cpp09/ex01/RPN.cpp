#include "RPN.hpp"

#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() { }
RPN::RPN(const RPN &) { }
RPN &RPN::operator=(const RPN &) { return (*this); }
RPN::~RPN() { }

int RPN::calculate(const std::string &expression)
{
    std::stack<int> stack;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token)
    {
        if (token.length() == 1 && std::isdigit(token[0]))
            stack.push(token[0] - '0');
        else
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error");

            int b = stack.top();
            stack.pop();

            int a = stack.top();
            stack.pop();

            if (token == "+")
                stack.push(a + b);
            else if (token == "-")
                stack.push(a - b);
            else if (token == "*")
                stack.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error("Error");
                stack.push(a / b);
            }
            else
                throw std::runtime_error("Error");
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top();
}
