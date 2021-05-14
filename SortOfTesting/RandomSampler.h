#pragma once

#include <random>


class RandomSampler
{
public:
	RandomSampler() : randomGenerator(randomDevice()) {};
	~RandomSampler() = default;

	int generateUniformInt(int from, int to);
	int generateNormalInt(float mean, float sigma);
	float generateUniformFloat(float from, float to);
	float generateNormalFloat(float mean, float sigma);

	std::vector<int> generateUniformIntVector(int sample_length, int from, int to);
	std::vector<int> generateNormalIntVector(int sample_length, int from, int to, int mean, int sigma);

	int sampleNormalValueInRange(std::normal_distribution<> & sampler, int from, int to);
	float sampleNormalValueInRange(std::normal_distribution<float> & sampler, float from, float to);
	std::vector<float> generateNormalFloatVector(int sample_length, float from, float to, float mean, float sigma);
	std::vector<float> generateUniformFloatVector(int sample_length, float from, float to);

	template <class T, typename std::enable_if<std::is_same<T, float>::value, std::size_t>::type = 0>
	std::vector<std::vector<T>> generateRandomArrays(std::vector<int> const& array_sizes)
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

	template <class T, typename std::enable_if<std::is_same<T, int>::value, std::size_t>::type = 0>
	std::vector<std::vector<T>> generateRandomArrays(std::vector<int> const& array_sizes)
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

	static constexpr int min_allowed_data_len = 1;
	static constexpr int max_allowed_data_len = 1000000;

	static constexpr float min_allowed_float_data_val = 0.0f;
	static constexpr float max_allowed_float_data_val = 1.0f;

	static constexpr float min_allowed_int_data_val = 1;
	static constexpr float max_allowed_int_data_val = 10000;

	std::random_device randomDevice {};
	std::default_random_engine randomGenerator;

	inline bool checkDataLenForSanity(int length) { return length >= min_allowed_data_len && length <= max_allowed_data_len; }
};

