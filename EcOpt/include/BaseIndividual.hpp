#ifndef EC_BaseIndividual_Hpp
#define EC_BaseIndividual_Hpp

#include <vector>
#include <random>

namespace EC
{

	/// \brief A base individual class in EAs typically corresponds to a solution.  
	template<typename ChromoType, typename FitnessType>
	class BaseIndividual
	{
	public:

		BaseIndividual();
		virtual ~BaseIndividual();
		
		/// \brief Overloaded subscript. Note that the return value can be a left-value.
		/// \param[in] index. Index of a particular gene
		/// \return The corresponding gene.
		virtual ChromoType& operator[](const int index) = 0;
			
		/// \brief Get the length of this individual
		/// \return Length of the individual(chromosome).
		virtual int Size() const = 0;

		/// \brief Get the fitness of this individual
		/// \return Fitness
		virtual FitnessType GetFitness() const = 0;

		/// \brief Set the fitness of this individual
		/// \param[in] fitness. Fitness
		virtual void SetFitness(FitnessType fitness) = 0;	

		/// \brief Create a deepcopy of this individual
		/// \return A pointer to a deepcopy of this individual
		virtual BaseIndividual<ChromoType, FitnessType>* DeepCopy() = 0;
	};
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename ChromoType, typename FitnessType>
EC::BaseIndividual<ChromoType, FitnessType>::BaseIndividual()
{ }


template<typename ChromoType, typename FitnessType>
EC::BaseIndividual<ChromoType, FitnessType>::~BaseIndividual()
{ }

#endif
