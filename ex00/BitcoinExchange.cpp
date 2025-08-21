/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:13:41 by aldalmas          #+#    #+#             */
/*   Updated: 2025/07/21 14:59:14 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BtcExchange::BtcExchange(const char* filename)
{
    std::size_t pipe_idx;
    std::string line, date, btc_amount;
    std::map<std::string, float>::iterator nearest_it;
    std::ifstream file(filename);
    float converted_btc = 0.0f;

    if (!file.is_open())
        throw std::runtime_error("could not open file.");

    this->setDatabase();
    while (std::getline(file, line))
    {
        pipe_idx = line.find("|");
        if (pipe_idx > line.size())
        {
            std::cerr << RED "Error: bad input => " << line <<  RESET << std::endl;
            continue;
        }
        if (checkDateFormat(line) == false)
            continue;
        date = trim(line.substr(0, pipe_idx));
        btc_amount = trim(line.substr(pipe_idx + 1));
        converted_btc = convertBtcFormat(btc_amount);
        if (checkValue(converted_btc) == false)
            continue;
        this->exchange(date, converted_btc);
    }
}

void BtcExchange::exchange(std::string date, float converted_btc)
{
    std::map<std::string, float>::iterator nearest_it = _btcData.lower_bound(date);

    // if date not found, then nearest_it will return data.end() and we must grab the latest date on database
    if (nearest_it == _btcData.end())
        --nearest_it;
    std::cout << date << " => " << converted_btc << " = " << converted_btc * nearest_it->second << std::endl;
}

BtcExchange::BtcExchange(const BtcExchange& o) {
    *this = o;
}

BtcExchange::~BtcExchange() {}

BtcExchange& BtcExchange::operator=(const BtcExchange& o)
{
    if (this != &o)
        _btcData = o._btcData;
    return *this;
}

float BtcExchange::convertBtcFormat(std::string btc)
{
    float converted_btc;
    const char* btc_c = btc.c_str();
    char* pEnd;

    converted_btc = strtof(btc_c, &pEnd);
    return converted_btc;
}


bool BtcExchange::checkOnlyDigit(std::string line)
{
    const char* c_line = line.c_str();
    for (size_t i = 0; i < std::strlen(c_line); i++)
    {
        if (c_line[i] != '-'
            && c_line[i] != ' '
            && c_line[i] != '|'
            && c_line[i] != '.'
            && std::isdigit(line[i]) == 0)
            return false;
    }
    return true;
}


bool BtcExchange::checkDateFormat(std::string date)
{
    size_t limit = std::numeric_limits<int>::max() - 1;
    if (date.find("|") > limit || !checkOnlyDigit(date))
    {
        ft_error("invalid date format.");
        std::cout << "DEBUG: " << date << std::endl;
        return false;
    }
    int year = std::atoi(date.substr(0,4).c_str());
    int month = std::atoi(date.substr(5,6).c_str());
    int day = std::atoi(date.substr(8,9).c_str());

    if (year < 2009)
    {
        ft_error("cannot be bellow 2009.");
        return false;
    }
    if (year > 2025)
    {
        ft_error("year do not exist yet.");
        return false;
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day > 31)
        {
            ft_error("invalid day format, 31 days max.");
            return false;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
        {
            ft_error("invalid day format, 30 days max.");
            return false;
        }
    }
    if (month == 2)
    {
        if (year % 4 == 0)
        {
            if (day > 29)
            {
                ft_error("invalid day format, 29 days max (leap year).");
                return false;
            }
        }
        else
        {
            if (day > 28)
            {
                ft_error("invalid day format, 28 days max.");
                return false;
            }
        }
    }
    return true;
}

bool BtcExchange::checkValue(float value)
{
    if (value > 1000.0f)
    {
        ft_error("too large number.");
        return false;
    }
    if (value < 0.0f)
    {
        ft_error("not a positive number.");
        return false;
    }
    return true;
}

void BtcExchange::setDatabase()
{
    float value = 0.0f;
    std::string line;
    std::string date;
    std::ifstream file("data.csv");

    std::getline(file, line);
    while (std::getline(file, line))
    {
        date = line.substr(0, 10);
        value = convertBtcFormat(line.substr(11));
        _btcData.insert(std::pair<std::string, float>(date, value));
    }
}

// FREE FUNCTION
void ft_error(std::string msg)
{
    std::cout << RED "Error: " << msg <<  RESET << std::endl;
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    if (first == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}
