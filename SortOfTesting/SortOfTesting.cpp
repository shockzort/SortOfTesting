// SortOfTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "RandomSampler.h"
#include "SortOfTesting.h"



int32_t main()
{
	printf("Hello. This is the sorting algorithm testing software\n\n");
	
	testSorting_algorithms({ 49, 114, 264, 609, 1402, 3227, 7424 }, true);

	printf("\nDone testing. Goodbye!\n\n");
	
	system("pause");
}


void testSorting_algorithms(const std::vector<uint32_t> & test_data_lengths, bool normalize_result)
{
	printf("We are going to test and compare two algorithms : Selection and Insertion sorting\n\n");

	const auto values_text = print_container(test_data_lengths);
	printf("Input data array sizes are : %s\n", values_text.c_str());

	const std::string log_name = values_text + ".txt";
	printf("Writing results to %s\n\n", log_name.c_str());
	std::ofstream out_file(log_name);
	
	RandomSampler sampler;

	printf("Generating random data for Selection sorting algorithm\n");
	auto test_array_set_1 = sampler.generateRandomArrays<int32_t>(test_data_lengths);
		
	printf("Generating random data for Optimized Selection sorting algorithm\n");
	auto test_array_set_2 = sampler.generateRandomArrays<int32_t>(test_data_lengths);
		
	printf("Generating random data for Insertion sorting algorithm\n\n");
	auto test_array_set_3 = sampler.generateRandomArrays<int32_t>(test_data_lengths);


	
	printf("\n// ----------------------------------------- Sorting by Selection Tests ------------------------------------------- //\n");
	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\nTesting Sorting by Selection sorting algorithm implementation for correctness\n");
	testSorting_algorithm_correctness(sort_by_selection, test_array_set_1, "Selection sorting");
	// -------------------------------------------------------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\nTesting Sorting by Selection sorting algorithm implementation for speed\n");
	sampler.shuffle_array_set(test_array_set_1);
	const auto time_selection = testSorting_algorithm_speed(sort_by_selection, test_array_set_1);
	printf("Selection sorting time: %.2f ms\n\n", time_selection);
	// -------------------------------------------------------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("Testing Sorting by Selection sorting algorithm for operations\n");
	sampler.shuffle_array_set(test_array_set_1);
	auto [swaps_sel, comparisons_sel] = testSorting_algorithm_operations(sort_by_selection_counters, test_array_set_1, 
		"Selection sorting", normalize_result);
	
	write_to_ofstream(out_file, std::string("Selection swaps: \t" + swaps_sel));
	write_to_ofstream(out_file, std::string("Selection comparisons: \t" + comparisons_sel));
	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\n// ---------------------------------------------------------------------------------------------------------------- //\n\n");


	
	printf("\n// ------------------------------------ Optimized Sorting by Selection Tests -------------------------------------- //\n");
	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\nTesting Optimized (cocktail-like) Sorting by Selection sorting algorithm implementation for correctness\n");
	testSorting_algorithm_correctness(sort_by_selection_opt, test_array_set_2, "Optimized Selection sorting");
	// -------------------------------------------------------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\nTesting Optimized (cocktail-like) Sorting by Selection sorting algorithm implementation for speed\n");
	sampler.shuffle_array_set(test_array_set_2);
	const auto time_selection_opt = testSorting_algorithm_speed(sort_by_selection_opt, test_array_set_2);
	printf("Optimized Selection sorting time: %.2f ms\n\n", time_selection_opt);
	// -------------------------------------------------------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("Testing Optimized (cocktail-like) Sorting by Selection sorting algorithm for operations\n");
	sampler.shuffle_array_set(test_array_set_2);
	auto [swaps_sel_opt, comparisons_sel_opt] = testSorting_algorithm_operations(sort_by_selection_opt_counters, 
		test_array_set_2, "Optimized Selection sorting", normalize_result);
	
	write_to_ofstream(out_file, std::string("Selection Optimized swaps: \t" + swaps_sel_opt));
	write_to_ofstream(out_file, std::string("Selection Optimized comparisons: \t" + comparisons_sel_opt));
	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\n// ---------------------------------------------------------------------------------------------------------------- //\n\n");



	printf("\n// ----------------------------------------- Sorting by Insertion Tests ------------------------------------------- //\n");
	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\nTesting Sorting by Insertion sorting algorithm implementation for correctness\n");
	testSorting_algorithm_correctness(sort_by_insertion, test_array_set_3, "Insertion sorting");
	// -------------------------------------------------------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("Testing Sorting by Insertion sorting algorithm implementation for speed\n");
	sampler.shuffle_array_set(test_array_set_3);
	const auto time_insertion = testSorting_algorithm_speed(sort_by_insertion, test_array_set_3);
	printf("Insertion sorting time: %.2f ms\n\n", time_insertion);
	// -------------------------------------------------------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("Testing Sorting by Insertion sorting algorithm for operations\n");
	sampler.shuffle_array_set(test_array_set_3);
	auto [swaps_ins, comparisons__ins] = testSorting_algorithm_operations(sort_by_insertion_counters, test_array_set_3, "Insertion sorting", normalize_result);

	write_to_ofstream(out_file, std::string("Insertion swaps: \t" + swaps_ins));
	write_to_ofstream(out_file, std::string("Insertion comparisons: \t" + comparisons__ins));
	// -------------------------------------------------------------------------------------------------------------------------- //
	printf("\n// ---------------------------------------------------------------------------------------------------------------- //\n");
}