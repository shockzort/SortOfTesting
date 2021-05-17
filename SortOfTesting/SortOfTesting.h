#pragma once

//#define DEBUG_
#include <memory>
#include <cassert>
#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>

void testSorting_algorithms(const std::vector<uint32_t>& test_data_lengths, bool normalize_result);

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

template<typename container_type, typename T = typename container_type::value_type>
bool check_array_diff(container_type& array1, container_type& array2)
{
	assert(array1.size() == array2.size());

	int32_t diff = 0;
	for (size_t index = 0; index < array1.size(); ++index)
	{
		diff += array1[index] - array2[index];
	}

	return diff == 0 ? true : false;
}

template<typename container_type, typename T = typename container_type::value_type>
using sorting_function_type = std::tuple<uint64_t, uint64_t> (*)(container_type&);

template<typename container_type, typename T = typename container_type::value_type>
float testSorting_algorithm(sorting_function_type<container_type> sort_method,
	std::vector<container_type> & array_to_sort, const std::string & alg_name, bool normalize_result = false)
{
	const auto time_start = std::chrono::high_resolution_clock::now();
	
	for (auto& array : array_to_sort)
	{
#ifdef DEBUG_
		auto copy = array;
#endif		
		auto [swaps, comparisons] = sort_method(array);

		if (normalize_result)
		{
			auto result_swaps = static_cast<double>(swaps) / array.size();
			auto result_comparisons = static_cast<double>(comparisons) / array.size();

			printf("%s algorithm has %.2f swaps and %.2f comparisons for array of size %llu\n", 
				alg_name.c_str(), result_swaps, result_comparisons, array.size());
		}
		else
		{
			printf("%s algorithm has %llu swaps and %llu comparisons for array of size %llu\n", 
				alg_name.c_str(), swaps, comparisons, array.size());
		}
				
#ifdef DEBUG_
		std::sort(copy.begin(), copy.end());
		const auto result = check_array_diff(copy, array);

		result ? printf("%s algorithm is correct\n", alg_name.c_str()) :
			printf("%s algorithm is incorrect!\n", alg_name.c_str());
#endif
	}

	const auto time_end = std::chrono::high_resolution_clock::now();
	const auto time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);

	return static_cast<float>(time_elapsed.count() * 0.001f);
}