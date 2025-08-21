/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:05:33 by aldalmas          #+#    #+#             */
/*   Updated: 2025/08/21 17:09:01 by aldalmas         ###   ########.fr       */
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

class PmergeMe {
    private:
        std::vector<size_t> _initial_list;
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
        void handlePairs();
        bool swapPairs(size_t pair_idx); // will replace preSort()
        void doFordJohson();
        void charChecker(char* av);
        void print_list(std::vector<size_t>& list);
        void setupMainList();
        std::vector<size_t> doJacobsthal(size_t max);
        void jacobLowerInMain(std::vector<size_t> idx_list);
        void binaryInsert(std::vector<size_t>& dest_list, int element);
        void insertLastLowers();
};

void ft_error(std::string msg);