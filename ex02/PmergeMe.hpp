/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:05:33 by aldalmas          #+#    #+#             */
/*   Updated: 2025/08/23 11:08:00 by marvin           ###   ########.fr       */
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
#include <vector>
#include <cctype> // isdigit
#include  <algorithm> // lower_bound
#include <utility> // std::pair, std::make_pair

class PmergeMe {
    private:
        std::vector<size_t> _arg_list;
        std::vector< std::pair<size_t, size_t> > _pairs;

        // useless ?
        std::vector<size_t> _lower;
        std::vector<size_t> _upper;
        std::vector<size_t> _main;
        std::vector<size_t> _remaining_lower;

    public:
        PmergeMe(char** av);
        ~PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        // void preSort();
        void handlePairs(); // will replace preSort()
        void firstSwap();
        void swapBiggerPairs(size_t stride);
        void doFordJohson();
        void charChecker(char* av);
        void printList(std::vector<size_t>& list);
        void setupMainList();
        std::vector<size_t> doJacobsthal(size_t max);
        void jacobLowerInMain(std::vector<size_t> idx_list);
        void binaryInsert(std::vector<size_t>& dest_list, int element);
        void insertLastLowers();
};

void ft_error(std::string msg);