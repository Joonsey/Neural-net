#pragma once
#include "math.h"
#include <vector>
#include <iostream>

namespace neuralnet
{
	class Neuron {
	public:
		Neuron(const unsigned int size) : size(size), m_weights(size), m_bias(0.0f) {}
		float activate(const std::vector<float>& inputs) const {
			if (inputs.size() != m_weights.size()) {
				throw std::invalid_argument("Input size does not match weight size");
			}

			float activation = 0.0f;
			for (long unsigned int i = 0; i < m_weights.size(); i++) {
				activation += inputs[i] * m_weights[i];
			}

			return math::sigmoid(activation + m_bias);
		}
		std::vector<float> get_weights() {return m_weights;}
		void set_weights(std::vector<float>& new_weights) {
			if (new_weights.size() != m_weights.size())
			{
				throw std::invalid_argument("Number of new weights doesn't match number of neurons");
			}
			m_weights = new_weights;
		}
		int size;

	private:
		std::vector<float> m_weights;
		float m_bias;

	};
}
