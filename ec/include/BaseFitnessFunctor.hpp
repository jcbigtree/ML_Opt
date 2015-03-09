#ifndef EC_BaseFitnessFunctor_Hpp
#define EC_BaseFitnessFunctor_Hpp

#include "BaseIndividual.hpp"
#include <vector>


namespace EC
{
	/// \brief Base class for Fitness functor. Used for encapsulating objective functions.
	template<typename ChromoType, typename FitnessType>
	class BaseFitnessFunctor
	{
	public:
		BaseFitnessFunctor()
		{ }
		virtual ~BaseFitnessFunctor()
		{ }

		/// \brief Calculate fitness of an individual. For single-objective optimization only.
		/// \param[in] pIndiv. An individual that will be evaluated
		virtual double operator() (BaseIndividual<ChromoType, FitnessType>* pIndiv) = 0;
	};
}
#endif






