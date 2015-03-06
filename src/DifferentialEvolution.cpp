#include "../include/DifferentialEvolution.hpp"
#include "../include/BasePopulation.hpp"
#include "../include/RealCodedIndividual.hpp"
#include <iostream>
#include <math.h>



EC::DifferentialEvolution::DifferentialEvolution() 
	: m_pElite(NULL), m_diffWeight(0.7), m_crossoverProb(0.2)
{ }


EC::DifferentialEvolution::~DifferentialEvolution()
{ }

/// \brief Create and initialize a population randomly. Overridden.
///		   WARNING: MUST BE CALLED BY OVERRIDDEN FUNCTION.
/// \param[in] populationSize. Size of a population.
/// \param[in] lowerBound. Domain lower bound.
/// \param[in] upperBound. Domain upper bound.
/// \param[in] pFitnessFunc. Functor for fitness evaluation.
void EC::DifferentialEvolution::Initialize(
	unsigned int populationSize,
	std::vector<double>& lowerBound,
	std::vector<double>& upperBound,
	BaseFitnessFunctor<double, double>* pFitnessFunc)
{	
	// Call base method to check the lower and upper bound
	BaseEvolver<double, double>::Initialize(populationSize, lowerBound, upperBound, pFitnessFunc);
	
	// Create and initialize population
	unsigned int problemDim = lowerBound.size();
	m_pPopulation = new BasePopulation<double, double>(populationSize);
	for(unsigned int i=0; i<populationSize; i++)
	{		
		RealCodedIndividual* pIndiv = new RealCodedIndividual(problemDim);
		for(unsigned int k=0; k<problemDim; k++)
		{
			(*pIndiv)[k] = RandUniform(m_lowerBound[k], m_upperBound[k]);
		}		
		(*m_pPopulation)[i] = pIndiv;
	}	
}


bool EC::DifferentialEvolution::CheckStopCriteria()
{ 
	if (m_generation >= m_maxGeneration)
	{
		return true;
	}
	return false;
}


void EC::DifferentialEvolution::Select()
{
}


void EC::DifferentialEvolution::Breed()
{
	if (m_pPopulation == NULL || (*m_pPopulation)[0] == NULL)
	{
		throw std::runtime_error("Empty population. Can't do breeding");
	}

	// Mutation, Crossover and Select
	unsigned int popSize = m_pPopulation->Size();
	unsigned int indivLength = (*m_pPopulation)[0]->Size();

	for (unsigned int i = 0; i < popSize; i++)
	{
		int* pTrialIndexes = RandIntegerWithoutReplacement(0, popSize, 3);
		BaseIndividual<double, double>* x0 = (*m_pPopulation)[pTrialIndexes[0]];
		BaseIndividual<double, double>* x1 = (*m_pPopulation)[pTrialIndexes[1]];
		BaseIndividual<double, double>* x2 = (*m_pPopulation)[pTrialIndexes[2]];
		BaseIndividual<double, double>* trial = (*m_pPopulation)[i]->DeepCopy();

		int* pRandIndex = RandIntegerWithoutReplacement(0, indivLength, 1);
		for (unsigned int j = 0; j < indivLength; j++)
		{
			if(j == pRandIndex[0] || RandUniform(0.0, 1.0) < m_crossoverProb)
			{
				(*trial)[j] = (*x0)[j] + m_diffWeight * ((*x1)[j] - (*x2)[j]);
			}
		}
		// Evaluate new trial and compare it with the current one
		Evaluate(trial);
		if (trial->GetFitness() < (*m_pPopulation)[i]->GetFitness())
		{
			delete (*m_pPopulation)[i];
			(*m_pPopulation)[i] = trial;
		}
	}
}


void EC::DifferentialEvolution::SaveElite()
{
	// Smaller, better
	double minValue = 1e100;
	int minIndex = 0;
	int popSize = m_pPopulation->Size();
	for (int i = 0; i < popSize; i++)
	{
		if ((*m_pPopulation)[i]->GetFitness() < minValue)
		{
			minValue = (*m_pPopulation)[i]->GetFitness();
			minIndex = i;
		}
	}
	m_pElite = (*m_pPopulation)[minIndex];

	std::cout << m_pElite->GetFitness() << std::endl;
}



// Generate a few random integers without replacement
int* EC::DifferentialEvolution::RandIntegerWithoutReplacement(
	unsigned int min,
	unsigned int max,
	unsigned int numInteger
	)
{
	int* intArr = new int[numInteger];
	intArr[0] = std::floor(RandUniform(min, max));
	unsigned int count = 1;
	for (unsigned int i = 1; i < numInteger; i++)
	{
		bool integerIsGood = false;
		while (!integerIsGood)
		{
			int val = static_cast<int>(RandUniform(min, max));
			// Check whether val is good
			integerIsGood = true;
			for (unsigned int j = 0; j < count; j++)
			{
				if (val == intArr[j])
				{ 
					integerIsGood = false; 
					break;
				}
			}				
			intArr[i] = val;
		}
		count++;
	}
	return intArr;
}

EC::BaseIndividual<double, double>* EC::DifferentialEvolution::GetElite()
{
	return m_pElite;
}
