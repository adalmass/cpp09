/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <aldalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:24:51 by aldalmas          #+#    #+#             */
/*   Updated: 2025/09/09 14:12:14 by aldalmas         ###   ########.fr       */
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

    // dissociate upper and lower in each pair
    _main.push_back(_pairs[0].second);
    for (size_t i = 0; i < _pairs.size(); ++i)
    {
        _main.push_back(_pairs[i].first);
        if (i != 0)
            _pendant.push_back(_pairs[i].second);
    }
    std::cout << "main: ";
    printList(_main);
    std::cout << "pendant: ";
    printList(_pendant);
    jacob_list = doJacobsthal(_pendant.size());
    // todo
    const size_t size = _arg_list.size();
    if (_arg_list.size() % 2 == 1)
        binaryInsert(_main, _arg_list[size - 1]);
}


void PmergeMe::firstSwap()
{
    const size_t n = _arg_list.size();

    for (size_t i = 0; i + 1 < n; i += 2)
    {
        if (_arg_list[i + 1] > _arg_list[i])
            std::swap(_arg_list[i + 1], _arg_list[i]);
    
        _pairs.push_back(std::make_pair(_arg_list[i], _arg_list[i + 1]));
    }
}


void PmergeMe::handlePairs()
{   
    printList(_arg_list);
    firstSwap();
    printList(_arg_list);
    const size_t n = _pairs.size();

    for (size_t stride = 1; stride < n; stride *= 2)
        swapBiggerPairs(stride);
    
    std::cout << "DEBUG _pairs:" << std::endl;
    for (size_t i = 0; i < _pairs.size(); ++i) {
        std::cout << "(" << _pairs[i].first << "," << _pairs[i].second << ") ";
    }
std::cout << std::endl;

}


void PmergeMe::swapBiggerPairs(size_t stride)
{
    const size_t n = _pairs.size();
    if (n <2 || stride == 0)
        return;

    std::vector< std::pair<size_t, size_t> > temp;

    for (size_t i = 0; i < n; i += 2 * stride)
    {
        const size_t mid = (i + stride < n) ? i + stride : n; // searching the mid of _pairs (and the lenght of the left block)
        if (mid >= n) 
            break;
        
        const size_t end = (mid + stride < n) ? mid + stride : n; // end of the right block

        temp.clear();

        movePairs(i, mid, end, temp);
        
        for (size_t k = 0; k < temp.size(); ++k)
            _pairs[i + k] = temp[k];
    }
}

void PmergeMe::movePairs(size_t i, size_t mid, size_t end, std::vector< std::pair<size_t, size_t> >& temp)
{
    size_t l_side = i;
    size_t r_side = mid;

    while (l_side < mid && r_side < end)
    {
        if (_pairs[l_side].first <= _pairs[r_side].first)
        {
            temp.push_back(_pairs[l_side]);
            l_side++;   
        }
        else
        {
            temp.push_back(_pairs[r_side]);
            r_side++;  
        }
    }

    while (l_side < mid) // on vide ce qu' il reste du cote gauche
    {
        temp.push_back(_pairs[l_side]);
        l_side++;
    }

    while (r_side < end) // pareil ici
    {
        temp.push_back(_pairs[r_side]);
        r_side++;
    }
}


void PmergeMe::binaryInsert(std::vector<size_t>& dest_list, int element)
{
    std::vector<size_t>::iterator idx = std::lower_bound(dest_list.begin(), dest_list.end(), element);
    dest_list.insert(idx, element);
}


std::vector<size_t> PmergeMe::doJacobsthal(size_t max)
{
    std::vector<size_t> order;

    if (max <= 1)
        return order;

    size_t j0 = 0;
    size_t j1 = 1;
    std::vector<size_t> jSequence;

    while (j1 < max)
    {
        jSequence.push_back(j1);
        size_t jn = j1 + 2 * j0;
        j0 = j1;
        j1 = jn;
    }
    for (size_t t = 2; t < jSequence.size(); ++t)
    {
        size_t from = (jSequence[t] > max) ? max : jSequence[t];
        size_t limit = jSequence[t - 1] + 1;

        if (from < limit)
            continue;

        for (size_t x = from; ; --x)
        {
            if (x != 1)
                order.push_back(x - 1); // on convertit en 0-based

            if (x == limit)
                break;
        }
    }

    // --- compléter avec les indices non ajoutés par les blocs
    std::vector<bool> seen(max, false);
    for (size_t i = 0; i < order.size(); ++i)
        seen[order[i]] = true;

    // ne pas ajouter l'élément déjà inséré au tout début
    for (size_t i = max; i-- > 1; )
    {
        if (!seen[i])
            order.push_back(i);
    }
    std::cout << "jacob sequence: ";
    printList(jSequence);
    std::cout << "order: ";
    printList(order);
    exit(0);
    return order;
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