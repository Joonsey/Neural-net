#pragma once
#include "neuron.h"

namespace neuralnet
{

	class NeuronLayer {
	public:
		NeuronLayer(
				const unsigned int num_neurons,
				const unsigned int num_input_per_neuron) {

			for (int i = 0; i < num_neurons; i++)
			{
				Neuron n(num_input_per_neuron);
				neurons.push_back(n);
			}
		};
		std::vector<float> activate(std::vector<float>& input) const
		{
			std::vector<float> activations;
			float activation;

			for (auto neuron : neurons)
			{
				activation = neuron.activate(input);
				activations.push_back(activation);
			}

			return activations;
		};
		std::vector<std::vector<float>> get_weights() const {
			std::vector<std::vector<float>> weights;
			std::vector<float> weight;
			for (auto neuron : neurons)
			{
				weight = neuron.get_weights();
				weights.push_back(weight);
			}

			return weights;
		};
		void set_weights(std::vector<std::vector<float>>& new_weights) {
			if (new_weights.size() != neurons.size())
			{
				throw std::invalid_argument("Number of new weights doesn't match number of neurons");
			}

			for (unsigned int i = 0; i < neurons.size();i++)
			{
				neurons[i].set_weights(new_weights[i]);
			}
		}

	private:
		std::vector<Neuron> neurons;
	};

}
