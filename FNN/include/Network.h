#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"
#include <vector>

class Network
{
	std::vector<Layer> layers;
public:
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
};

#endif