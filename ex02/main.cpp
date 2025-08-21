/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:27:20 by aldalmas          #+#    #+#             */
/*   Updated: 2025/07/21 15:32:46 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        ft_error("waiting at least one positive number.");
    
    PmergeMe list(av + 1);
    
    list.doFordJohson();
    return (0);
}