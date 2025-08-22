/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:24:51 by aldalmas          #+#    #+#             */
/*   Updated: 2025/08/22 16:08:00 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


PmergeMe::PmergeMe(char** av)
{
    for (int i = 0; av[i]; i++)
    {
        charChecker(av[i]);
        _arg_list.push_back(std::atoi(av[i]));
    }
}


void PmergeMe::charChecker(char* av)
{
    for (size_t i = 0; av[i]; i++)
    {
        if (!std::isdigit(av[i]))
            ft_error("only positive digit are allowed.");
    }
}


PmergeMe::~PmergeMe() {}


PmergeMe::PmergeMe(const PmergeMe& o)
{
    *this = o;  
}


PmergeMe& PmergeMe::operator=(const PmergeMe& o)
{
    if (this != &o)
        _arg_list = o._arg_list;
    return *this;
}


void PmergeMe::doFordJohson()
{
    std::vector<size_t> jacob_list;

    if (_arg_list.size() <= 1)
        return;

    // will sort little pairs, big pairs, big big, etc.
    handlePairs();

        
    // setupMainList();
    
    // jacob_list = doJacobsthal(_lower.size());
    // //create vector with good idx (jacob_stal + merde)
    
    // printList(jacob_list);
    // jacobLowerInMain(jacob_list);
    
    // insertLastLowers();
    // // std::cout << "\nlower: "; // debug
    // // printList(_lower);
    // // std::cout << "\nremaining_lower: "; // debug
    // // printList(_remaining_lower);
    // // std::cout << "\nupper: "; // debug
    // // printList(_upper);
    // std::cout << "\nmain: "; // debug
    // printList(_main);
}


// will replace preSort()
bool PmergeMe::firstSwap(size_t stride)
{
    bool swapped = false;

    for (size_t i = 0; i + 1 < _arg_list.size(); i += stride)
    {
        if (_arg_list[i + 1] > _arg_list[i])
        {
            std::swap(_arg_list[i], _arg_list[i + 1]);
            swapped = true;
        }
        _pairs.push_back(std::make_pair(_arg_list[i], _arg_list[i + 1]));
    }    
    return swapped;
}


bool PmergeMe::swapBiggerPairs(size_t stride)
{
    (void)stride;
    bool swapped = false;
    std::vector< std::pair<size_t, size_t> >::iterator it = _pairs.begin();

    for (; it != _pairs.end(); ++it)
        std::cout << it->first << ", " << it->second << std::endl;
    
    return swapped;
}
void PmergeMe::handlePairs()
{
    size_t stride = 2;
    size_t turns = 1;

    while (true)
    {
        bool swapped = false;

        if (turns == 1)
        {
            if (firstSwap(stride))
                swapped = true;
        }
        else
        {
            if (swapBiggerPairs(stride))
                swapped = true;
        }

        if (!swapped)
            break;

        stride *= 2;
        turns += 1;
    }
}


// second step: do _main = lower[0] + _upper
void PmergeMe::setupMainList()
{
    _main.push_back(_lower[0]);
    for (std::vector<size_t>::iterator it = _upper.begin(); it != _upper.end(); it++)
        _main.push_back(*it);
}


void PmergeMe::binaryInsert(std::vector<size_t>& dest_list, int element)
{
    std::vector<size_t>::iterator idx = std::lower_bound(dest_list.begin(), dest_list.end(), element);
    dest_list.insert(idx, element);
}


void PmergeMe::insertLastLowers()
{
    for (size_t i = 0; i < _remaining_lower.size(); i++)
        binaryInsert(_main, _remaining_lower[i]);
}


// third step: use the idx for insert _lower in _main.
void PmergeMe::jacobLowerInMain(std::vector<size_t> jacob_list)
{
    const size_t low_size = _lower.size();
    const size_t jac_size = jacob_list.size();
    size_t ji = 0;

    std::cout << RED "actual main:" RESET << std::endl;
    printList(_main);
    std::cout << RED "actual lower: " RESET << std::endl;
    printList(_lower);
    // i = 1 because we already moved the _lower[0] in the main list before this step.
    for (size_t i = 1; i < low_size; i++)
    {
        const size_t current = _lower[i];
    
        if (ji < jac_size && jacob_list[ji] == i)
        {
            std::cout << current << " added to _main" << std::endl;
            binaryInsert(_main, current);
            ji++;
        }
        else
        { 
            std::cout << current << " added to _remaining_lower" << std::endl;
            binaryInsert(_remaining_lower, current);
        }
    }
}


std::vector<size_t> PmergeMe::doJacobsthal(size_t max)
{
    std::vector<size_t> result;
    size_t j0 = 0;
    size_t j1 = 1;

    if (max == 0)
        return result;

    result.push_back(j1);
    while (true)
    {
        size_t jn = j1 + 2 * j0;
        result.push_back(jn);
        if (jn > max)
            break;

        j0 = j1;
        j1 = jn;
    
    }
    return result;
}


// ---
void ft_error(std::string msg)
{
    std::cerr << RED "Error: " << msg <<  RESET << std::endl;
    exit (1);
}


void PmergeMe::printList(std::vector<size_t>& list)
{
    const size_t n = list.size();

    for (size_t i = 0; i < n; i++)
    {
        if (i <= n && i != 0)
            std::cout << ", ";
        std::cout << list[i];
    }
    std::cout << std::endl;
}