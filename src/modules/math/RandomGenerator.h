/**
 * Copyright (c) 2006-2013 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_MATH_RANDOM_GENERATOR_H
#define LOVE_MATH_RANDOM_GENERATOR_H

// LOVE
#include "common/math.h"
#include "common/int.h"
#include "common/Object.h"

// STL
#include <limits>

namespace love
{
namespace math
{

class RandomGenerator : public Object
{
public:

	RandomGenerator();

	virtual ~RandomGenerator() {};

	/**
	 * Set pseudo random seed.
	 * It's up to the implementation how to use this.
	 *
	 * @param seed The random seed.
	 **/
	inline void randomseed(uint64 seed)
	{
		rng_state = seed;
	}

	/**
	 * Return uniformly distributed pseudo random integer.
	 *
	 * @return Pseudo random integer in [0,2^64).
	 **/
	uint64 rand();

	/**
	 * Get uniformly distributed pseudo random number in [0,1).
	 *
	 * @return Pseudo random number in [0,1).
	 **/
	inline double random()
	{
		return double(rand()) / (double(std::numeric_limits<uint64>::max()) + 1.0);
	}

	/**
	 * Get uniformly distributed pseudo random number in [0,max).
	 *
	 * @return Pseudo random number in [0,max).
	 **/
	inline double random(double max)
	{
		return random() * max;
	}

	/**
	 * Get uniformly distributed pseudo random number in [min, max).
	 *
	 * @return Pseudo random number in [min, max).
	 **/
	inline double random(double min, double max)
	{
		return random() * (max - min) + min;
	}

	/**
	 * Get normally distributed pseudo random number.
	 *
	 * @param stddev Standard deviation of the distribution.
	 * @return Normally distributed random number with mean 0 and variance (stddev)².
	 **/
	double randomnormal(double stddev);

private:

	uint64 rng_state;
	double last_randomnormal;

}; // RandomGenerator

} // math
} // love

#endif // LOVE_MATH_RANDOM_GENERATOR_H
