#ifndef EC_BaseEvolver_Hpp
#define EC_BaseEvolver_Hpp

#include <stdexcept>
#include <vector>
#include <random>
#include <iostream>
#include "BasePopulation.hpp"
#include "BaseFitnessFunctor.hpp"

namespace EC
{
	/// 
	/// \brief    A general evolver class used in evolutionary algorithms.
	/// 
	/// \details  Pseudocode for General Evolutionary Algorithms.
	///				(1) Initialize the population randomly.
	///				(2) Evaluate the current generation.
	///				(3) Repeat: 
	///				(4)     Select one or a few 'good' individuals.
	///				(5)     Generate next generation using 'good' individuals.
	///				(6)     Check whether the stop criteria is met.
	template<typename ChromoType, typename FitnessType>
	class BaseEvolver
	{
	public:
		BaseEvolver();
		virtual ~BaseEvolver();
	

		/// \brief Create and initialize a population randomly.
		///            WARNING: MUST BE CALLED BY OVERRIDDEN FUNCTION.
		/// \param[in] populationSize. Size of a population
		/// \param[in] lowerBound. Domain lower bound
		/// \param[in] upperBound. Domain upper bound
		/// \param[in] pFitnessFunc. Functor for fitness evaluation
		virtual void Initialize(
			unsigned int populationSize,
			std::vector<double>& lowerBound,
			std::vector<double>& upperBound,
			BaseFitnessFunctor<ChromoType, FitnessType>* pFitnessFunc
			);

		/// \brief Evolve. The main loop
		/// \param[in] maxGeneration. Max generation allowed
		/// \param[in] verbose. If true, show details during evolving
		virtual void Evolve(unsigned int maxGeneration=100, bool verbose=false);

		/// \brief Evolve. The main loop
		/// \param[in] populationSize. Desired population size
		/// \param[in] lowerBound. Domain lower bound
		/// \param[in] upperBound. Domain upper bound
		/// \param[in] pFitnessFunc. Functor for fitness evaluation
		/// \param[in] maxGeneration. Max generation allowed. default 100
		/// \param[in] verbose. If true, show details during evolving. default false
		virtual void Evolve(
			unsigned int populationSize,
			std::vector<double>& lowerBound,
			std::vector<double>& upperBound,
			BaseFitnessFunctor<ChromoType, FitnessType>* pFitnessFunc,
			unsigned int maxGeneration=100,
			bool verbose=false);
		
		/// \brief Set the population that will be evolved.
		/// \param[in] pop. A pointer to an existing population
		void SetPopulation(BasePopulation<ChromoType, FitnessType>* pop);

		/// \brief Get a pointer to the population that will be evolved.
		/// \return The pointer to the population stored in the BaseEvolver
		BasePopulation<ChromoType, FitnessType>* GetPopulation();

	protected:
		/// \brief Evaluate an individual
		/// \param[in,out] An individual. Fitness will be stored in the input individual
		virtual void Evaluate(BaseIndividual<ChromoType, FitnessType>* pIndiv);

		/// \brief Evaluate a population
		/// \param[in,out] A population. Fitness will be stored in each individual
		virtual void Evaluate(BasePopulation<ChromoType, FitnessType>* pPopulation);

		/// \brief Select the better ones from the current population.
		virtual void Select() = 0;

		/// \brief Generate a new population using the selected individuals.
		virtual void Breed() = 0;

		/// \brief Check whether the stop criteria is met.
		virtual bool CheckStopCriteria() = 0;

		/// \brief Save the elite
		virtual void SaveElite() = 0;
		
		/// \brief       Generate a number from a given uniform distribution [min, max]
		/// \param[in]   min. Lower bound of a uniform distribution
		/// \param[in]   max. Upper bound of a uniform distribution
		/// \return      Random number
		double RandUniform(const double min, const double max);

		/// \brief       Generate a number from a given normal distribution (mean, std)
		/// \param[in]   mean. Mean of a normal distribution
		/// \param[in]   std. Std of a normal distribution
		/// \return      Random number
		double RandNorm(const double mean, const double std);

	protected:		
		BasePopulation<ChromoType, FitnessType>* m_pPopulation;	
		BasePopulation<ChromoType, FitnessType>* m_pOffsprings;	

		unsigned int  m_generation;		    // Generation 
		unsigned int  m_maxGeneration;	    // Max generation allowed

		std::vector<double> m_lowerBound;   // Lower bound of the variables
		std::vector<double> m_upperBound;   // Upper bound of the variables

		BaseFitnessFunctor<ChromoType, FitnessType>* m_pFitnessFunc;

	private:
		// Random number generator
		std::random_device          m_randDevice;
		std::default_random_engine  m_RandNumberGenerator; 	
	
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Implementation
	///////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename ChromoType, typename FitnessType>
	BaseEvolver<ChromoType, FitnessType>::BaseEvolver()
		:m_pPopulation(NULL), m_generation(0), m_maxGeneration(100), m_pFitnessFunc(NULL)
	{
		m_RandNumberGenerator = std::default_random_engine(m_randDevice()); 
	}


	template<typename ChromoType, typename FitnessType>
	BaseEvolver<ChromoType, FitnessType>::~BaseEvolver()
	{}


	template<typename ChromoType, typename FitnessType>
	void BaseEvolver<ChromoType, FitnessType>::SetPopulation(BasePopulation<ChromoType, FitnessType>* pop)
	{ 
		m_pPopulation = pop; 
	}	


	template<typename ChromoType, typename FitnessType>
	BasePopulation<ChromoType, FitnessType>* BaseEvolver<ChromoType, FitnessType>::GetPopulation()
	{
		return m_pPopulation; 
	}	


	template<typename ChromoType, typename FitnessType>
	double BaseEvolver<ChromoType, FitnessType>::RandUniform(const double min, const double max)
	{
		std::uniform_real_distribution<double> distribution(min, max);
		return distribution(m_RandNumberGenerator);
	}


	template<typename ChromoType, typename FitnessType>
	double BaseEvolver<ChromoType, FitnessType>::RandNorm(const double mean, const double std)
	{
		std::normal_distribution<double> distribution(mean, std);
		return distribution(m_RandNumberGenerator);	
	}


	template<typename ChromoType, typename FitnessType>
	void BaseEvolver<ChromoType, FitnessType>::Initialize(
		unsigned int populationSize,
		std::vector<double>& lowerBound,
		std::vector<double>& upperBound,
		BaseFitnessFunctor<ChromoType, FitnessType>* pFitnessFunc)
	{
		// Check the given bounds
		if (lowerBound.size() != upperBound.size())
		{
			throw std::invalid_argument(
				"Lower and upper bounds should have the same size"
				);
		}
		for (unsigned int i = 0; i < lowerBound.size(); i++)
		{
			if (lowerBound[i] > upperBound[i])
			{
				throw std::invalid_argument(
					"Lower bound must be not bigger than the upper bound."
					);
			}
		}

		m_lowerBound = lowerBound;
		m_upperBound = upperBound;
		m_pFitnessFunc = pFitnessFunc;		
	}
	

	template<typename ChromoType, typename FitnessType>
	void BaseEvolver<ChromoType, FitnessType>::
	Evaluate(BaseIndividual<ChromoType, FitnessType>* pIndiv)
	{
		// Check whether we have fitness function
		if (m_pFitnessFunc == NULL)
		{
			throw std::invalid_argument("Invalid fitness function");
		}
		double fitness = (*m_pFitnessFunc)(pIndiv);
		pIndiv->SetFitness(fitness);
	}

	template<typename ChromoType, typename FitnessType>
	void BaseEvolver<ChromoType, FitnessType>::
	Evaluate(BasePopulation<ChromoType, FitnessType>* pPopulation)
	{
		unsigned int popSize = pPopulation->Size();
		for (unsigned int i = 0; i < popSize; i++)
		{
			Evaluate((*pPopulation)[i]);
		}
	}

	template<typename ChromoType, typename FitnessType>
	void BaseEvolver<ChromoType, FitnessType>::Evolve(unsigned int maxGeneration, bool verbose)
	{
		m_maxGeneration = maxGeneration;
		Evaluate(m_pPopulation);
		while(CheckStopCriteria() == false)
		{
			if (verbose)
			{
				std::cout << "Generation: " << m_generation << std::endl;
			}

			Breed();     // Generate offsprings

			Select();    // Select better ones

			SaveElite(); // Save the best one

			m_generation++;
		}
	}


	template<typename ChromoType, typename FitnessType>
	void BaseEvolver<ChromoType, FitnessType>::Evolve(
		unsigned int populationSize,
		std::vector<double>& lowerBound, 
		std::vector<double>& upperBound,
		BaseFitnessFunctor<ChromoType, FitnessType>* pFitnessFunc,
		unsigned int maxGeneration,
		bool verbose)
	{
		Initialize(populationSize, lowerBound, upperBound, pFitnessFunc);
		Evolve(maxGeneration, verbose);
	}




}

#endif
