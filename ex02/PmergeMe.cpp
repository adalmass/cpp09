/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:24:51 by aldalmas          #+#    #+#             */
/*   Updated: 2025/08/21 17:11:59 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


PmergeMe::PmergeMe(char** av)
{
    for (int i = 0; av[i]; i++)
    {
        charChecker(av[i]);
        _initial_list.push_back(std::atoi(av[i]));
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
        _initial_list = o._initial_list;
    return *this;
}


void PmergeMe::doFordJohson()
{
    std::vector<size_t> jacob_list;

    // preSort();
    // std::sort(_upper.begin(), _upper.end());

    
    setupMainList();
    
    jacob_list = doJacobsthal(_lower.size());
    //create vector with good idx (jacob_stal + merde)
    
    print_list(jacob_list);
    jacobLowerInMain(jacob_list);
    
    insertLastLowers();
    // std::cout << "\nlower: "; // debug
    // print_list(_lower);
    // std::cout << "\nremaining_lower: "; // debug
    // print_list(_remaining_lower);
    // std::cout << "\nupper: "; // debug
    // print_list(_upper);
    std::cout << "\nmain: "; // debug
    print_list(_main);
}

// will replace preSort()
bool PmergeMe::swapPairs(size_t pair_idx)
{
    bool swapped = false;

    const size_t n = _initial_list.size();
    
    // move this part in doFordJohnson---------
    if (n == 0) return;

    if (n == 1)
    {
        std::cout << _initial_list[0] << std::endl;
        exit (0);
    }
    // ----------------------------------------

    for (size_t i = 0; i + 1 < n; i += 2)
    {
        if (_initial_list[i + 1] > _initial_list[i])
        {
            std::swap(_initial_list[i], _initial_list[i + 1]);   
            swapped = true;
        }
    }

    return swapped;
}

void PmergeMe::handlePairs()
{
    size_t pair_idx = 1;
    bool swapped = false;

    while (true)
    {
        if (swapPairs(pair_idx))
            swapped = true;
        
        if (!swapped)
            break;
        pair_idx *= 2;   
    }
}

// first step: compare paires in the initial _initial_list and sort each lower and upper in _lower and _upper
// void PmergeMe::preSort()
// {
//     const size_t n = _initial_list.size();
    
//     if (n == 0)
//         return;
    
//     if (n == 1)
//     {
//         std::cout << _initial_list[0] << std::endl;
//         exit (0);
//     }
    
//     size_t i = 0;

//     for (; i + 1 < n; i += 2)
//     {
//         const size_t current = _initial_list[i];
//         const size_t next = _initial_list[i + 1];

//         if (current > next)
//         {
//             _upper.push_back(current);
//             _lower.push_back(next);
//         }
//         else
//         {
//             _upper.push_back(next);
//             _lower.push_back(current);
//         }    
//     }
//     if (i < n)
//         _upper.push_back(_initial_list[i]);  // choix arbitraire si taille de liste impaire
// }


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
    print_list(_main);
    std::cout << RED "actual lower: " RESET << std::endl;
    print_list(_lower);
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


void PmergeMe::print_list(std::vector<size_t>& list)
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