#ifndef EC_RealCodedIndividual_Hpp
#define EC_RealCodedIndividual_Hpp

#include <vector>
#include <random>
#include <stdexcept>
#include "BaseIndividual.hpp"

namespace EC
{
	/// \brief Real coded individual
	class RealCodedIndividual : public BaseIndividual<double, double>
	{
	public:
		RealCodedIndividual();

		/// \brief Constructor with length
		/// \param[in] length. Length of an individual
		RealCodedIndividual(unsigned int length);
		virtual ~RealCodedIndividual();
		
		/// \brief Overloaded subscript. Note that the return value can be a left-value.
		/// \param[in] index.
		/// \return The corresponding gene.
		virtual double& operator[](const int index);
				
		/// \brief Get the length of this individual
		/// \return Length of the individual(chromosome).
		inline virtual int Size() const
		{
			return m_chromosome.size();
		}
	
		/// \brief Get the fitness of this individual
		/// \return Fitness
		inline virtual double GetFitness() const
		{
			return m_fitness;		
		}
	
		/// \brief Set the fitness of this individual
		/// \param[in] fitness. Fitness
		inline virtual void SetFitness(double fitness)
		{
			m_fitness = fitness;
		}

		/// \brief Create a deepcopy of this individual
		/// \return A deepcopy
		virtual BaseIndividual<double, double>* DeepCopy();
			
		/// \brief Print the individual to console
		void Print();

	protected:
		
		std::vector<double> m_chromosome;
		double m_fitness;
	
	};
}
#endif
