// SortOfTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>
#include "RandomSampler.h"
#include <exception>

template<typename container_type, typename T = typename container_type::value_type>
void sort_by_selection(container_type& container)
{
	if (container.size() <= 1)
		return;

	for (auto it = container.begin(); it != container.end() - 1; ++it)
	{
		auto cur_min = it;
		auto cur_min_val = *it;

		for (auto it_inner = it + 1; it_inner != container.end(); ++it_inner)
		{
			if (*it_inner < cur_min_val)
			{
				cur_min = it_inner;
				cur_min_val = *it_inner;
			}
		}

		if (cur_min != it) 
		{
			std::swap(*cur_min, *it);
		}
	}
}


template<typename container_type, typename T = typename container_type::value_type>
void sort_by_insertion(container_type& container)
{
	if (container.size() <= 1)
		return;

	for (auto idx_out = 1; idx_out < container.size(); ++idx_out)
	{
		auto cur_min_val = container[idx_out];
		
		auto idx_inner = idx_out - 1;
		for (; idx_inner >= 0 && container[idx_inner] > cur_min_val; --idx_inner)
		{
			container[idx_inner + 1] = container[idx_inner];
		}

		container[idx_inner + 1] = cur_min_val;
	}
}

void testSorting_algorithms()
{
	std::cout << "We are going to test and compare two algorithms : Selection and Insertion sorting" << std::endl;
	
	RandomSampler sampler;

	static const std::vector<int> test_data_lengths = { 2, 16, 32, 128, 1024, 8192 };

	std::cout << "Generating random data for Selection sorting algorithm" << std::endl;
	auto test_array_set_1 = sampler.generateRandomArrays<float>(test_data_lengths);

	std::cout << "Generating random data for Insertion sorting algorithm" << std::endl;
	auto test_array_set_2 = sampler.generateRandomArrays<int>(test_data_lengths);


	std::cout << "Sorting by Selection sorting algorithm" << std::endl;
	for (auto& array : test_array_set_1)
	{
		sort_by_selection(array);
	}

	std::cout << "Sorting by Insertion sorting algorithm" << std::endl;
	for (auto& array : test_array_set_2)
	{
		sort_by_insertion(array);
	}
}

int main()
{
	std::cout << "Hello. This is the sorting algorithm testing software" << std::endl;
	
	testSorting_algorithms();
	
	std::cout << "Done testing. Goodbue!" << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
