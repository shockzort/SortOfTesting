#include "RandomSampler.h"

int RandomSampler::generateUniformInt(int from, int to)
{
	static std::uniform_int_distribution<int> uint_from_to(from, to);

	return uint_from_to(randomGenerator);
}

int RandomSampler::generateNormalInt(float mean, float sigma)
{
	static std::normal_distribution<> nint_from_to(mean, sigma);

	return static_cast<int>(round(nint_from_to(randomGenerator)));
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

std::vector<int> RandomSampler::generateUniformIntVector(int sample_length, int from, int to)
{
	std::vector<int> result;
	result.resize(sample_length);

	for (auto it = 0; it < sample_length; ++it)
	{
		result[it] = generateUniformInt(from, to);
	}

	return result;
}


int RandomSampler::sampleNormalValueInRange(std::normal_distribution<> & sampler, int from, int to)
{
	while (true)
	{
		const auto number = static_cast<int>(round(sampler(randomGenerator)));

		if (number >= from && number <= to)
			return number;
	}
}

std::vector<int> RandomSampler::generateNormalIntVector(int sample_length, int from, int to, int mean, int sigma)
{
	std::vector<int> result;
	result.resize(sample_length);

	static std::normal_distribution<> nint_from_to(mean, sigma);

	for (auto it = 0; it < sample_length; ++it)
	{
		result[it] = sampleNormalValueInRange(nint_from_to, from, to);
	}

	return result;
}



std::vector<float> RandomSampler::generateUniformFloatVector(int sample_length, float from, float to)
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

std::vector<float> RandomSampler::generateNormalFloatVector(int sample_length, float from, float to, 
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
