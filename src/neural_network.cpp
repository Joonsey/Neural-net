#include <iostream>

#include "neuron.h"

int main()
{
	neuralnet::Neuron n(2);
	neuralnet::Neuron n2(2);

	float activation = n.activate(n2.get_weights());
	std::cout << activation << std::endl;
	return 0;
}
