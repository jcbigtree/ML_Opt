#ifndef EC_BenchmarkFunctions_Hpp
#define EC_BenchmarkFunctions_Hpp

#include "BaseFitnessFunctor.hpp"
#include <vector>



namespace EC
{
	class SphereFunctor : public BaseFitnessFunctor <double, double>
	{
	public:
		SphereFunctor();
		virtual ~SphereFunctor();

		/// \brief     Calculate fitness of an individual. For single-objective optimization only.
		/// \param[in] BaseIndividual<ChromoType, FitnessType>&. A reference to an individual
		virtual double operator() (BaseIndividual<double, double>* pIndividual);

		inline std::vector<double>& GetDomainLowerBound()
		{
			return m_lowerBound;
		}
		inline std::vector<double>& GetDomainUpperBound()
		{
			return m_upperBound;
		}

	protected:		
		std::vector<double> m_lowerBound;
		std::vector<double> m_upperBound;
		int m_problemDim;
	};

}


#endif

