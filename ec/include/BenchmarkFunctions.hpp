#ifndef EC_BenchmarkFunctions_Hpp
#define EC_BenchmarkFunctions_Hpp

#include "BaseFitnessFunctor.hpp"
#include <vector>



namespace EC
{
	/// \brief Sphere functor
	class SphereFunctor : public BaseFitnessFunctor <double, double>
	{
	public:
		SphereFunctor();
		virtual ~SphereFunctor();

		/// \brief Calculate fitness of an individual. For single-objective optimization only.
		/// \param[in] pIndiv. Individual that is to be evaluated
		virtual double operator() (BaseIndividual<double, double>* pIndiv);

		/// \brief Get the domain lower bound
		/// \return the domain lower bound
		inline std::vector<double>& GetDomainLowerBound()
		{
			return m_lowerBound;
		}

		/// \brief Get the domain upper bound
		/// \return the domain upper bound
		inline std::vector<double>& GetDomainUpperBound()
		{
			return m_upperBound;
		}

	protected:		
		std::vector<double> m_lowerBound;
		std::vector<double> m_upperBound;
		unsigned int m_problemDim;
	};

}


#endif

