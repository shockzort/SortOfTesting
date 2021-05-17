#include "RandomSampler.h"

int32_t RandomSampler::generateUniformInt(int32_t from, int32_t to)
{
	static std::uniform_int_distribution<int32_t> uint_from_to(from, to);

	return uint_from_to(randomGenerator);
}

int32_t RandomSampler::generateNormalInt(float mean, float sigma)
{
	static std::normal_distribution<> nint_from_to(mean, sigma);

	return static_cast<int32_t>(round(nint_from_to(randomGenerator)));
}

float RandomSampler::generateUniformFloat(float from, float to)
{
	static std::uniform_real_distribution<float> ufloat_from_to(from, to);

	return ufloat_from_to(randomGenerator);
}

float RandomSampler::generateNormalFloat(float mean, float sigma)
{
	static std::normal_distribution<float> nfloat_from_to(mean, sigma);

	return nfloat_from_to(randomGenerator);
}

std::vector<int32_t> RandomSampler::generateUniformIntVector(int32_t sample_length, int32_t from, int32_t to)
{
	std::vector<int32_t> result;
	result.resize(sample_length);

	for (auto it = 0; it < sample_length; ++it)
	{
		result[it] = generateUniformInt(from, to);
	}

	return result;
}


int32_t RandomSampler::sampleNormalValueInRange(std::normal_distribution<> & sampler, int32_t from, int32_t to)
{
	while (true)
	{
		const auto number = static_cast<int32_t>(round(sampler(randomGenerator)));

		if (number >= from && number <= to)
			return number;
	}
}

std::vector<int32_t> RandomSampler::generateNormalIntVector(int32_t sample_length, int32_t from, int32_t to, int32_t mean, int32_t sigma)
{
	std::vector<int32_t> result;
	result.resize(sample_length);

	static std::normal_distribution<> nint_from_to(mean, sigma);

	for (auto it = 0; it < sample_length; ++it)
	{
		result[it] = sampleNormalValueInRange(nint_from_to, from, to);
	}

	return result;
}



std::vector<float> RandomSampler::generateUniformFloatVector(int32_t sample_length, float from, float to)
{
	std::vector<float> result;
	result.resize(sample_length);

	for (auto it = 0; it < sample_length; ++it)
	{
		result[it] = generateUniformFloat(from, to);
	}

	return result;
}


float RandomSampler::sampleNormalValueInRange(std::normal_distribution<float> & sampler, float from, float to)
{
	while (true) 
	{
		const float number = sampler(randomGenerator);

		if (number >= from && number <= to)
			return number;
	}
}

std::vector<float> RandomSampler::generateNormalFloatVector(int32_t sample_length, float from, float to, 
	const float mean, const float sigma)
{
	std::vector<float> result;
	result.resize(sample_length);

	static std::normal_distribution<float> nfloat_from_to(mean, sigma);

	for (auto it = 0; it < sample_length; ++it)
	{
		result[it] = sampleNormalValueInRange(nfloat_from_to, from, to);
	}

	return result;
}
