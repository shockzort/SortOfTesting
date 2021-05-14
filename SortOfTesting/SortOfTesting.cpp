// SortOfTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>
#include "RandomSampler.h"

template<typename Iterator>
void sort_by_selection(Iterator begin, Iterator end)
{
	if (end - begin <= 1)
		return;

	for (auto it = begin; it != end - 1; ++it) 
	{
		auto cur_min = it;
		auto cur_min_val = *it;

		for (auto it_inner = it + 1; it_inner != end; ++it_inner)
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

int main()
{
	std::cout << "Hello. This is the sorting algorithm testing software\n";
	std::cout << "We are going to test and compare two algorithms : Selection and Insertion sorting\n";

	std::cout << "Generating random data for Selection sorting algorithm\n";

	RandomSampler sampler;

	static const std::vector<int> test_data_lengths = { 2, 16, 32, 128, 1024, 8192 };

	auto test_array_set_1 = sampler.generateRandomArrays<float>(test_data_lengths);

	auto test_array_set_2 = sampler.generateRandomArrays<int>(test_data_lengths);
	

	for (auto & array : test_array_set_1) 
	{
		sort_by_selection(array.begin(), array.end());
	}


	for (auto& array : test_array_set_2)
	{
		sort_by_selection(array.begin(), array.end());
	}
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
