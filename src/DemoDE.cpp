
#include <iostream>
#include <vector>
#include "RealCodedIndividual.hpp"
#include "BasePopulation.hpp"
#include "DifferentialEvolution.hpp"
#include "BenchmarkFunctions.hpp"

using namespace EC;

int main(void)
{
	SphereFunctor* pSphereFunc = new SphereFunctor();
	DifferentialEvolution myDE;
	myDE.Evolve(
		100,
		pSphereFunc->GetDomainLowerBound(),
		pSphereFunc->GetDomainUpperBound(),
		pSphereFunc,
		500,
		true
		);

	BaseIndividual<double, double>* pIndivElite = myDE.GetElite();

	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Best individual: " << std::endl;
	dynamic_cast<RealCodedIndividual*>(pIndivElite)->Print();
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Best fitness: " << pIndivElite->GetFitness() << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	std::cin.get();
	return 0;
}

