// SortOfTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "RandomSampler.h"
#include "SortOfTesting.h"



int32_t main()
{
	printf("Hello. This is the sorting algorithm testing software\n\n");
	
	testSorting_algorithms({ 2, 16, 32, 128, 1024, 8192, 65535 }, false);

	printf("Done testing. Goodbye!\n\n");
	
	system("pause");
}



void testSorting_algorithms(const std::vector<uint32_t> & test_data_lengths, bool normalize_result)
{
	printf("We are going to test and compare two algorithms : Selection and Insertion sorting\n");

	RandomSampler sampler;

	printf("Generating random data for Selection sorting algorithm\n");
	auto test_array_set_1 = sampler.generateRandomArrays<int32_t>(test_data_lengths);

	
	printf("Generating random data for Optimized Selection sorting algorithm\n");
	auto test_array_set_2 = sampler.generateRandomArrays<int32_t>(test_data_lengths);

	
	printf("Generating random data for Insertion sorting algorithm\n\n");
	auto test_array_set_3 = sampler.generateRandomArrays<int32_t>(test_data_lengths);


	
	printf("Sorting by Selection sorting algorithm\n");
	const auto time_selection = testSorting_algorithm(sort_by_selection_counters, test_array_set_1, "Selection sorting", normalize_result);
	printf("Selection sorting time: %.2f ms\n\n", time_selection);

	
	printf("Sorting by Selection optimized (cocktail-like) sorting algorithm\n");
	const auto time_selection_opt = testSorting_algorithm(sort_by_selection_opt_counters, test_array_set_2, "Optimized selection sorting", normalize_result);
	printf("Selection optimized (cocktail-like) sorting time: %.2f ms\n\n", time_selection_opt);


	printf("Sorting by Insertion sorting algorithm\n");
	const auto time_insertion = testSorting_algorithm(sort_by_insertion_counters, test_array_set_3, "Insertion sorting", normalize_result);
	printf("Insertion sorting time: %.2f ms\n\n", time_insertion);
}