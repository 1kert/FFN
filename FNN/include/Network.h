#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"
#include "Dataset.h"
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

	static double calculateError(Dataset data)
    {
        if(data.data.size() != data.expected.size()) throw std::length_error("actual and expected not the same size");

        double sum = 0;
        for(size_t i = 0; i < data.data.size(); i++) sum += std::pow(data.data[i] - data.expected[i], 2);
        return sum / data.data.size();
    }

	static double calculateError(std::vector<Dataset> data)
	{
		double error = 0;
		for(size_t i = 0; i < data.size(); i++) error += calculateError(data[i]);
		return error / data.size();
	}

	void learn(Dataset* data)
	{
		std::vector<double> outputs = calculateOutputs(data->data);
		double error = calculateError(outputs, data->expected);

	}
};

#endif