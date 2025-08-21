/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:27:20 by aldalmas          #+#    #+#             */
/*   Updated: 2025/07/14 17:09:23 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        ft_error("only one argument is required.");
    
    RPN calculator;
    std::cout << calculator.calculate(av[1]) << std::endl;
}
