/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:44:54 by aldalmas          #+#    #+#             */
/*   Updated: 2025/07/14 18:02:15 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& o)
{
    *this = o;  
}

RPN& RPN::operator=(const RPN& o)
{
    if (this != &o)
        _stack = o._stack;
    return *this;
}


int RPN::calculate(const std::string& arg)
{
    int result;
    int nb1;
    int nb2;
    
    for (size_t i = 0; i < arg.size(); i++)
    {
        if (std::isspace(arg[i]))
            continue;

        if(std::isdigit(arg[i]))
            _stack.push(arg[i] - '0');
    
        else if(isOperator(arg[i]))
        {
            if (_stack.size() < 2)
                ft_error("too many operators.");
            nb1 = _stack.top();
            _stack.pop();
            nb2 = _stack.top();
            _stack.pop();
            result = getResult(nb1, nb2, arg[i]);
            _stack.push(result);
        }
        else
            ft_error("only digit and '+', '-', '/' and '*' operators are allowed.");
    }
    if (_stack.size() != 1)
        ft_error("bad format, try again.");
    return _stack.top();
}


int RPN::getResult(int nb1, int nb2, const char op)
{
    int result;
    int max_limit = std::numeric_limits<int>::max();
    int min_limit = std::numeric_limits<int>::min();

    if (op == '+')
    {
        if (nb1 > 0 && (nb2 > max_limit - nb1))
            ft_error("addition overflow.");
        if (nb1 < 0 && (nb2 < min_limit - nb1))
            ft_error("addition underflow.");
        result = nb2 + nb1;
    }
    if (op == '-')
    {
        if (nb1 < 0 && (nb2 > max_limit + nb1))
            ft_error("substraction overflow.");
        if (nb1 > 0 && (nb2 < min_limit + nb1))
            ft_error("substraction underflow.");
        result = nb2 - nb1;
    }
    if (op == '/')
    {
        if (nb1 == 0)
            ft_error("can't divide by zero. NICE TRY.");
        result = nb2 / nb1;
    }
    if (op == '*')
    {
        if (nb1 > 0 && (nb2 > max_limit / nb1))
            ft_error("multiplication overflow.");
        if (nb1 < 0 && (nb2 < min_limit / nb1))
            ft_error("multiplication underflow.");
        result = nb2 * nb1;
    }
    return result;
}

bool RPN::isOperator(char o)
{
    if (o != '+' && o != '-' && o != '/' && o != '*')
        return false;
    return true;
}


void ft_error(std::string msg)
{
    std::cerr << RED "Error: " << msg <<  RESET << std::endl;
    exit (1);
}