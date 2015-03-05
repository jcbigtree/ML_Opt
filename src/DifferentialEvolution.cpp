#include "DifferentialEvolution.hpp"
#include "BasePopulation.hpp"
#include "RealCodedIndividual.hpp"

#include <iostream>



EC::DifferentialEvolution::DifferentialEvolution() 
	: m_pElite(NULL)
{ }


EC::DifferentialEvolution::~DifferentialEvolution()
{ }


/// \brief       A pure virtual method for initializing the population randomly.
///				 WARNING: MUST BE CALLED BY OVERRIDDEN FUNCTION.
/// \param[in]   populationSize. Size of a population.
/// \param[in]   lowerBound. Domain lower bound.
/// \param[in]   upperBound. Domain upper bound.
void EC::DifferentialEvolution::Initialize(unsigned int populationSize, std::vector<double>& lowerBound,
	std::vector<double>& upperBound, BaseFitnessFunctor<double, double>* pFitnessFunc)
{	
	// Call base method to check the lower and upper bound
	BaseEvolver<double, double>::Initialize(populationSize, lowerBound, upperBound, pFitnessFunc);
	
	// Create and initialize population
	int problemDim = lowerBound.size();
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
}


EC::BaseIndividual<double, double>* EC::DifferentialEvolution::GetElite()
{
	return m_pElite;
}