#pragma once

#include <random>


class RandomSampler
{
public:
	RandomSampler() : randomGenerator(randomDevice()) {};
	~RandomSampler() = default;

	int32_t generateUniformInt(int32_t from, int32_t to);
	int32_t generateNormalInt(float mean, float sigma);
	float generateUniformFloat(float from, float to);
	float generateNormalFloat(float mean, float sigma);

	std::vector<int32_t> generateUniformIntVector(int32_t sample_length, int32_t from, int32_t to);
	std::vector<int32_t> generateNormalIntVector(int32_t sample_length, int32_t from, int32_t to, int32_t mean, int32_t sigma);

	int32_t sampleNormalValueInRange(std::normal_distribution<> & sampler, int32_t from, int32_t to);
	float sampleNormalValueInRange(std::normal_distribution<float> & sampler, float from, float to);
	std::vector<float> generateNormalFloatVector(int32_t sample_length, float from, float to, float mean, float sigma);
	std::vector<float> generateUniformFloatVector(int32_t sample_length, float from, float to);

	template <class T, typename std::enable_if<std::is_same<T, float>::value, std::size_t>::type = 0>
	std::vector<std::vector<T>> generateRandomArrays(std::vector<uint32_t> const& array_sizes)
	{
		std::vector<std::vector<T>> result;
		RandomSampler sampler;

		for (auto len : array_sizes)
		{
			if (checkDataLenForSanity(len))
			{
				result.emplace_back(sampler.generateUniformFloatVector(len, min_allowed_float_data_val, max_allowed_float_data_val));
			}
		}

		return result;
	}

	template <class T, typename std::enable_if<std::is_same<T, int32_t>::value, std::size_t>::type = 0>
	std::vector<std::vector<T>> generateRandomArrays(std::vector<uint32_t> const& array_sizes)
	{
		std::vector<std::vector<T>> result;
		RandomSampler sampler;

		for (auto len : array_sizes)
		{
			if (checkDataLenForSanity(len))
			{
				result.emplace_back(sampler.generateUniformIntVector(len, min_allowed_int_data_val, max_allowed_int_data_val));
			}
		}

		return result;
	}

private:

	static constexpr int32_t min_allowed_data_len = 1;
	static constexpr int32_t max_allowed_data_len = 1000000;

	static constexpr float min_allowed_float_data_val = 0.0f;
	static constexpr float max_allowed_float_data_val = 1.0f;

	static constexpr int32_t min_allowed_int_data_val = 1;
	static constexpr int32_t max_allowed_int_data_val = 10000;

	std::random_device randomDevice {};
	std::default_random_engine randomGenerator;

	static bool checkDataLenForSanity(int32_t length) { return length >= min_allowed_data_len && length <= max_allowed_data_len; }
};

