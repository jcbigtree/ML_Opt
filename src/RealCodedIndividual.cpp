#include "../include/RealCodedIndividual.hpp"
#include <iostream>

using namespace EC;


RealCodedIndividual::RealCodedIndividual()
{ }


RealCodedIndividual::RealCodedIndividual(unsigned int length)
{
	m_chromosome.resize(length);
}


RealCodedIndividual::~RealCodedIndividual()
{
	// Just to be sure
	m_chromosome.clear();
}
	

double& RealCodedIndividual::operator[](const int index)
{
	if(index < 0 || index > m_chromosome.size()-1)
	{
		throw std::invalid_argument( "Index out of bound" );
	}
	return m_chromosome[index];
}



// Note that when speed is crutial, we may use other ways to 
// implement this function.
BaseIndividual<double, double>* RealCodedIndividual::DeepCopy()
{
	unsigned int length = m_chromosome.size();
	RealCodedIndividual* deepCopy = new RealCodedIndividual(length);
	for (size_t i = 0; i < length; i++)
	{
		(*deepCopy)[i] = m_chromosome[i];
	}
	deepCopy->SetFitness(m_fitness);	
	return deepCopy;
}
			

void RealCodedIndividual::Print()
{
	for (unsigned int i = 0; i < m_chromosome.size(); i++)
	{
		std::cout << m_chromosome[i] << " ";
	}
	std::cout << std::endl;
}
