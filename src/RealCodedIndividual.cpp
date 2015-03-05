#include "RealCodedIndividual.hpp"
#include <iostream>

using namespace EC;


RealCodedIndividual::RealCodedIndividual()
{ }


/// \brief     Constructor with length
/// \param[in] Length of an individual
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
			

void RealCodedIndividual::Print()
{
	for (unsigned int i = 0; i < m_chromosome.size(); i++)
	{
		std::cout << m_chromosome[i] << " ";
	}
	std::cout << std::endl;
}
