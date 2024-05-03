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
			this->layers.push_back(Layer(layers[i], layers[i - 1]));
		}
	}
};

#endif // !NETWORK_H
