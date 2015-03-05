#include "../include/BenchmarkFunctions.hpp"
#include <stdexcept>


EC::SphereFunctor::SphereFunctor() : m_problemDim(10)
{ 
	for (unsigned int i = 0; i < m_problemDim; i++)
	{
		m_lowerBound.push_back(-5.12);
		m_upperBound.push_back(5.12);
	}
}


EC::SphereFunctor::~SphereFunctor()
{ }


/// \brief     Calculate fitness of an individual. For single-objective optimization only.
/// \param[in] BaseIndividual<ChromoType, FitnessType>&. A reference to an individual
double EC::SphereFunctor::operator() (BaseIndividual<double, double>* pIndividual)
{
	double sum = 0;
	if (pIndividual->Size() != m_problemDim)
	{
		throw std::invalid_argument(
			"The length of the individual should be equal to the problem dimension."
			);
	}

	for (unsigned int i = 0; i < m_problemDim; i++)
	{
		double val = (*pIndividual)[i];
		sum += val * val;
	}

	return sum;
}
