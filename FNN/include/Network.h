#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"
#include <vector>

class Network
{
public:
	std::vector<Layer> layers;
	
	Network(std::vector<int> layers)
	{
		for (int i = 1; i < layers.size(); i++)
		{
			Layer layer(layers[i], layers[i - 1]);
			this->layers.push_back(layer);
		}
	}

	std::vector<Layer> getLayers()
	{
		return layers;
	}

	std::vector<double> calculateOutputs(std::vector<double> inputs)
	{
		for(Layer layer : layers)
		{
			inputs = layer.calculateOutputs(inputs);
		}
		return inputs;
	}

	static double calculateError(std::vector<double> actual, std::vector<double> expected)
    {
        if(actual.size() != expected.size()) throw std::length_error("actual and expected not the same size");

        double sum = 0;
        for(size_t i = 0; i < actual.size(); i++) sum += std::pow(actual[i] - expected[i], 2);
        return sum /= actual.size();
    }
};

#endif