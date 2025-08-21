/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:22 by aldalmas          #+#    #+#             */
/*   Updated: 2025/05/19 17:13:08 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define RED     "\x1b[31m"
# define RESET   "\x1b[0m"

#include <iostream>
#include <stdlib.h>
#include <stack>
#include <exception>
#include <fstream>
#include <limits>


class RPN {
    private:
        std::stack<int> _stack;

    public:
        RPN();
        ~RPN();
        RPN(const RPN& other);
        
        RPN& operator=(const RPN& other);
        int calculate(const std::string& arg);
        bool isOperator(char o);
        int getResult(int nb1, int nb2, const char op);
};

void ft_error(std::string msg);

