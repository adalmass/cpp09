/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:27:20 by aldalmas          #+#    #+#             */
/*   Updated: 2025/07/14 12:07:40 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    try
    {
        if (ac != 2)
            throw std::runtime_error("valid file needed 'file.txt'.");

        std::string date = "2009-02-28";
        std::string date2 = "2024-05-31";
        std::map<std::string, float> btcData;
        
        // std::cout << std::fixed << std::setprecision(2);
        BtcExchange btc(av[1]);
        // btc.checkDateFormat(date);
        // btc.checkDateFormat(date2);
        // btc.checkValue(9999.9);
        // btc.checkValue(-134);
        // std::cout << "ok" << std::endl;
        // btc.calculateBtc();
    }
    catch (const std::exception& e)
    {
        std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
    }

    return 0;
}