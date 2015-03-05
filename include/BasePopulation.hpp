#ifndef EC_BasePopulation_Hpp
#define EC_BasePopulation_Hpp

#include <cstddef>
#include <vector>
#include <stdexcept>
#include "BaseIndividual.hpp"


namespace EC
{

	/// \brief Data structure used in evolutionary algorithms. 
	///        A population consists of a set of individuals.
	template<typename ChromoType, typename FitnessType>
	class BasePopulation
	{
	public:         
		BasePopulation();
		/// \brief Constructor
		/// \param[in] size. Desired population size
		BasePopulation(unsigned int size);
		virtual ~BasePopulation();
		
		/// \brief Overloaded subscript operator
		/// \param[in] index. Index of a particular individual
		/// \return A reference to the pointer of the corresponding individual.
		inline BaseIndividual<ChromoType, FitnessType>*& operator[](unsigned int index)
		{
			if (index < 0 || index > m_population.size() - 1)
			{
				throw std::out_of_range("Index out of bound");
			}
			return m_population[index];
		}
			
		/// \brief Get size of the population
		/// \return Size of the population
		inline unsigned int Size() const
		{
			return m_population.size();
		}
	
		/// \brief Release memories	
		void Release();
	
	protected:
		// VERY IMPORTANT! Must use pointers here.
		std::vector<BaseIndividual<ChromoType, FitnessType>*> m_population;	
	};
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename ChromoType, typename FitnessType>
EC::BasePopulation<ChromoType, FitnessType>::BasePopulation()
{ }


template<typename ChromoType, typename FitnessType>
EC::BasePopulation<ChromoType, FitnessType>::BasePopulation(unsigned int size)
{ 
	if(size <= 0)
	{
		throw std::invalid_argument( "received non-positive value" );
	}
	m_population.resize(size);
	for(unsigned int i = 0; i < size; i++)
	{
		m_population[i] = NULL;	
	}
}


template<typename ChromoType, typename FitnessType>
EC::BasePopulation<ChromoType, FitnessType>::~BasePopulation()
{ 
	Release(); 
}


template<typename ChromoType, typename FitnessType>
void EC::BasePopulation<ChromoType, FitnessType>::Release()
{	
	unsigned int size = m_population.size();
	for(unsigned int i = 0; i < size; i++)
	{
		delete m_population[i];				
	}
}

#endif
