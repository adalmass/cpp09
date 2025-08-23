/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:27:20 by aldalmas          #+#    #+#             */
/*   Updated: 2025/08/23 10:23:42 by marvin           ###   ########.fr       */
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