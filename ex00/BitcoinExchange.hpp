/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BtcExchange.hpp                                :+:      :+:    :+:   */
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
#include <exception>
#include <fstream>
#include <cstring>  // strlen
#include <iomanip> // setprecision
#include <map>
#include <limits>

class BtcExchange {
    private:
        std::map<std::string, float> _btcData;

    public:
        BtcExchange(const char* filename);
        ~BtcExchange();
        BtcExchange(const BtcExchange& other);
        
        BtcExchange& operator=(const BtcExchange& other);

        void setDatabase();
        // void exchange();
        void exchange(std::string date, float converted_btc);
        bool checkValue(float value);
        bool checkOnlyDigit(std::string date);
        bool checkDateFormat(std::string date);
        float convertBtcFormat(std::string btc);
};

void ft_error(std::string msg);
std::string trim(const std::string& str);