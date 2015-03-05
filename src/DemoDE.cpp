
#include <iostream>
#include <vector>
#include "../include/RealCodedIndividual.hpp"
#include "../include/BasePopulation.hpp"
#include "../include/DifferentialEvolution.hpp"
#include "../include/BenchmarkFunctions.hpp"

using namespace EC;

int main(void)
{
	SphereFunctor* pSphereFunc = new SphereFunctor();
	DifferentialEvolution myDE;
	unsigned int populationSize = 100;
	unsigned int maxGeneration = 500;
	bool verbose = true;
	myDE.Evolve(
		populationSize,
		pSphereFunc->GetDomainLowerBound(),
		pSphereFunc->GetDomainUpperBound(),
		pSphereFunc,
		maxGeneration,
		verbose
		);

	RealCodedIndividual* pIndivElite = dynamic_cast<RealCodedIndividual*>(myDE.GetElite());

	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Best individual: " << std::endl;
	pIndivElite->Print();
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Best fitness: " << pIndivElite->GetFitness() << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	std::cin.get();
	return 0;
}

