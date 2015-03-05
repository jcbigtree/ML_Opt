#ifndef EC_DifferentialEvolution_Hpp
#define EC_DifferentialEvolution_Hpp

#include <vector>
#include "BaseEvolver.hpp"
#include "BaseFitnessFunctor.hpp"


namespace EC
{
	/// \brief Differential evolution which is a kind of evolution algorithms.
	class DifferentialEvolution : public BaseEvolver<double, double>
	{
	public:
		DifferentialEvolution();
		virtual ~DifferentialEvolution();

		/// \brief Get the best individual
		/// \return the best individual
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

		/// \brief Select the better ones from the current population.
		virtual void Select();

		/// \brief Generate a new population using the selected individuals.
		virtual void Breed();

		/// \brief Check whether the stop criteria is met.
		virtual bool CheckStopCriteria();

		/// \brief Save elite
		virtual void SaveElite();

	public:
		/// \brief Generate a few random integers without replacement
		/// \param[in] min. Lower bound
		/// \param[in] max. Upper bound
		/// \param[in] numInteger. How many random integers will be generated
		virtual int* RandIntegerWithoutReplacement(
			unsigned int min, 
			unsigned int max, 
			unsigned int numInteger
			);


	private:
		BaseIndividual<double, double>* m_pElite;

		double m_diffWeight;    // Differential weights [0, 2]
		double m_crossoverProb; // Crossover probability
	};
}


#endif 
