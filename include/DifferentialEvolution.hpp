#ifndef EC_DifferentialEvolution_Hpp
#define EC_DifferentialEvolution_Hpp

#include <vector>
#include "BaseEvolver.hpp"
#include "BaseFitnessFunctor.hpp"


namespace EC
{
	class DifferentialEvolution : public BaseEvolver<double, double>
	{
	public:
		DifferentialEvolution();
		virtual ~DifferentialEvolution();

		BaseIndividual<double, double>* GetElite();	
		
	protected:
		/// \brief       Create and initialize a population randomly. Overridden.
		///				 WARNING: MUST BE CALLED BY OVERRIDDEN FUNCTION.
		/// \param[in]   populationSize. Size of a population.
		/// \param[in]   lowerBound. Domain lower bound.
		/// \param[in]   upperBound. Domain upper bound.
		/// \param[in]   pFitnessFunc. Functor for fitness evaluation.
		virtual void Initialize(
			unsigned int populationSize,
			std::vector<double>& lowerBound,
			std::vector<double>& upperBound,
			BaseFitnessFunctor<double, double>* pFitnessFunc
			);

		/// \brief       Select the better ones from the current population.
		virtual void Select();

		/// \brief       Generate a new population using the selected individuals.
		virtual void Breed();

		/// \brief       Check whether the stop criteria is met.
		virtual bool CheckStopCriteria();


		virtual void SaveElite();

	private:
		BaseIndividual<double, double>* m_pElite;
		
	};
}


#endif 