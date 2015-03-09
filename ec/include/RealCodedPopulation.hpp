#ifndef EC_RealCodedPopulation_Hpp
#define EC_RealCodedPopulation_Hpp

#include <cstddef>
#include <vector>
#include "BaseIndividual.hpp"
#include "BasePopulation.hpp"


namespace EC
{
	/// \brief Data structure used in evolutionary algorithms. 
	///        A population consists of a set of individuals.
	class RealCodedPopulation : public BasePopulation<double, double>
	{
	public: 
		RealCodedPopulation(unsigned int size) : BasePopulation(size)
		{ }
	
		virtual ~RealCodedPopulation()
		{ }
	};
}
#endif