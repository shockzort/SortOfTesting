#pragma once

//#define DEBUG_
#include <memory>
#include <cassert>
#include <vector>
#include <chrono>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>

// Main function
void testSorting_algorithms(const std::vector<uint32_t>& test_data_lengths, bool normalize_result);

// Selection sort algorithm implementation
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


// Selection sort algorithm implementation optimized to find min and max in one loop (cocktail sort like)
template<typename container_type, typename T = typename container_type::value_type>
void sort_by_selection_opt(container_type& container)
{
	if (container.size() <= 1)
		return;

	auto max_val_idx = static_cast<int64_t>(container.size());

	for (int64_t it = 0; it < max_val_idx - 1; ++it)
	{
		auto cur_min = it;
		auto cur_min_val = container[it];

		auto cur_max = it;
		auto cur_max_val = cur_min_val;

		for (int64_t it_inner = it + 1; it_inner < max_val_idx; ++it_inner)
		{
			auto val = container[it_inner];
			if (val < cur_min_val)
			{
				cur_min = it_inner;
				cur_min_val = val;
			}

			if (val > cur_max_val)
			{
				cur_max = it_inner;
				cur_max_val = val;
			}
		}
		--max_val_idx;

		if (cur_min != it)
		{
			std::swap(container[cur_min], container[it]);

			if (cur_max == it)
			{
				cur_max = cur_min;
			}
		}

		if (cur_max != max_val_idx)
		{
			std::swap(container[cur_max], container[max_val_idx]);
		}
	}
}


// Insertion sort algorithm implementation
template<typename container_type, typename T = typename container_type::value_type>
void sort_by_insertion(container_type& container)
{
	if (container.size() <= 1)
		return;

	for (int64_t idx_out = 1; idx_out < static_cast<int64_t>(container.size()); ++idx_out)
	{
		auto cur_min_val = container[idx_out];

		int64_t idx_inner = idx_out - 1;
		for (; idx_inner >= 0 && container[idx_inner] > cur_min_val; --idx_inner)
		{
			container[idx_inner + 1] = container[idx_inner];
		}

		container[idx_inner + 1] = cur_min_val;
	}
}


// Selection sort algorithm with operation counters
template<typename container_type, typename T = typename container_type::value_type>
std::tuple<uint64_t, uint64_t> sort_by_selection_counters(container_type& container)
{
	if (container.size() <= 1)
		return std::make_tuple(0, 0);

	uint64_t swaps = 0;
	uint64_t comparisons = 0;
	
	for (auto it = container.begin(); it != container.end() - 1; ++it)
	{
		auto cur_min = it;
		auto cur_min_val = *it;

		for (auto it_inner = it + 1; it_inner != container.end(); ++it_inner, ++comparisons)
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
			++swaps;
		}
	}

	return std::make_tuple(swaps, comparisons);
}


// Optimized Selection sort algorithm with operation counters
template<typename container_type, typename T = typename container_type::value_type>
std::tuple<uint64_t, uint64_t> sort_by_selection_opt_counters(container_type& container)
{
	if (container.size() <= 1)
		return std::make_tuple(0, 0);

	uint64_t swaps = 0;
	uint64_t comparisons = 0;
	auto max_val_idx = static_cast<int64_t>(container.size());

	for (int64_t it = 0; it < max_val_idx - 1; ++it)
	{
		auto cur_min = it;
		auto cur_min_val = container[it];

		auto cur_max = it;
		auto cur_max_val = cur_min_val;

		for (int64_t it_inner = it + 1; it_inner < max_val_idx; ++it_inner, comparisons += 2)
		{
			auto val = container[it_inner];
			if (val < cur_min_val)
			{
				cur_min = it_inner;
				cur_min_val = val;
			}

			if (val > cur_max_val)
			{
				cur_max = it_inner;
				cur_max_val = val;
			}
		}
		--max_val_idx;

		if (cur_min != it)
		{
			std::swap(container[cur_min], container[it]);

			if (cur_max == it)
			{
				cur_max = cur_min;
			}
			++swaps;
		}

		if (cur_max != max_val_idx)
		{
			std::swap(container[cur_max], container[max_val_idx]);
			++swaps;
		}
	}

	return std::make_tuple(swaps, comparisons);
}

// Insertion sort algorithm with operation counters
template<typename container_type, typename T = typename container_type::value_type>
std::tuple<uint64_t, uint64_t> sort_by_insertion_counters(container_type& container)
{
	if (container.size() <= 1)
		return std::make_tuple(0, 0);

	uint64_t swaps = 0;
	uint64_t comparisons = 0;
	for (int64_t idx_out = 1; idx_out < static_cast<int64_t>(container.size()); ++idx_out)
	{
		auto cur_min_val = container[idx_out];

		int64_t idx_inner = idx_out - 1;
		for (; idx_inner >= 0 && container[idx_inner] > cur_min_val; --idx_inner, ++comparisons)
		{
			container[idx_inner + 1] = container[idx_inner];
			++swaps;
		}

		container[idx_inner + 1] = cur_min_val;
		++swaps;
	}

	return std::make_tuple(swaps, comparisons);
}

// Function to check if two containers contain same values
template<typename container_type, typename T = typename container_type::value_type>
bool check_array_diff(container_type& array1, container_type& array2)
{
	assert(array1.size() == array2.size());

	float diff = 0.0f;
	for (size_t index = 0; index < array1.size(); ++index)
	{
		diff += array1[index] - array2[index];
	}

	return diff == 0.0f ? true : false;
}


template<typename container_type, typename T = typename container_type::value_type>
std::string print_container(container_type const& container)
{
	std::string result;
	
	for (auto & element : container)
		result.append(std::to_string(element) + " ");

	return result;
}

template<typename container_type, typename T = typename container_type::value_type>
using sorting_function_type_counters = std::tuple<uint64_t, uint64_t> (*)(container_type&);

template<typename container_type, typename T = typename container_type::value_type>
using sorting_function_type = void(*)(container_type&);

// Template for sorting correctness checking, comparing with std::sort
template<typename container_type, typename T = typename container_type::value_type>
bool testSorting_algorithm_correctness(sorting_function_type<container_type> sort_method,
	std::vector<container_type>& array_to_sort, const std::string& alg_name)
{
	bool all_sorts_correct = true;
	for (auto& array : array_to_sort)
	{
		auto copy = array;
		sort_method(array);

		std::sort(copy.begin(), copy.end());
		const auto correct_sort = check_array_diff(copy, array);

		all_sorts_correct = all_sorts_correct && correct_sort;
	}

	all_sorts_correct ? printf("%s algorithm implementation is correct\n", alg_name.c_str()) :
		printf("%s algorithm implementation is incorrect!\n", alg_name.c_str());

	return all_sorts_correct;
}

// Template for sorting speed measurement, using high_resolution_clock
template<typename container_type, typename T = typename container_type::value_type>
float testSorting_algorithm_speed(sorting_function_type<container_type> sort_method, std::vector<container_type>& array_to_sort)
{
	const auto time_start = std::chrono::high_resolution_clock::now();

	for (auto& array : array_to_sort)
	{	
		sort_method(array);
	}

	const auto time_end = std::chrono::high_resolution_clock::now();
	const auto time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);

	return static_cast<float>(time_elapsed.count() * 0.001f);
}


inline void write_to_ofstream(std::ofstream & file, std::string && data)
{
	if (file.is_open())
		file << data << std::endl;
}

// Template for sorting operation counting
template<typename container_type, typename T = typename container_type::value_type>
std::tuple<std::string, std::string> testSorting_algorithm_operations(sorting_function_type_counters<container_type> sort_method,
	std::vector<container_type> & array_to_sort, const std::string & alg_name, bool normalize_result = false)
{
	std::ostringstream swaps_data;
	std::ostringstream comparisons_data;
	
	for (auto& array : array_to_sort)
	{
		auto [swaps, comparisons] = sort_method(array);

		if (normalize_result)
		{
			auto result_swaps = std::log10(swaps);// static_cast<double>(swaps) / array.size();
			auto result_comparisons = std::log10(comparisons); //static_cast<double>(comparisons) / array.size();

			swaps_data.precision(5);
			comparisons_data.precision(5);
			
			swaps_data << std::fixed << result_swaps << "\t";
			comparisons_data << std::fixed << result_comparisons << "\t";

			printf("%s algorithm has %.2f swaps and %.2f comparisons for array of size %llu\n", 
				alg_name.c_str(), result_swaps, result_comparisons, array.size());
		}
		else
		{
			swaps_data << swaps << "\t";
			comparisons_data << comparisons << "\t";

			printf("%s algorithm has %llu swaps and %llu comparisons for array of size %llu\n", 
				alg_name.c_str(), swaps, comparisons, array.size());
		}
		
	}

	return std::make_tuple(swaps_data.str(), comparisons_data.str());
}