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

	double calculateError(Dataset data)
    {
		std::vector<double> outputs = calculateOutputs(data.data);
		double error = 0;
		for(size_t i = 0; i < outputs.size(); i++) error += std::pow(data.expected[i] - outputs[i], 2);
		return error;
    }

	double calculateError(std::vector<Dataset> data)
	{
		double error = 0;
		for(size_t i = 0; i < data.size(); i++) error += calculateError(data[i]);
		return error / data.size();
	}

	void resetAllGradients()
	{
		for(size_t i = 0; i < layers.size(); i++) layers[i].resetGradients();
	}

	void updateGradients(std::vector<Dataset> dataset, double learnRate)
	{
		for(size_t i = 0; i < dataset.size(); i++)
		{
			calculateOutputs(dataset[i].data);
		}
	}
	
	void learn(std::vector<Dataset> dataset, double learnRate)
	{
		double error = calculateError(dataset);

		for(size_t i = 0; dataset.size(); i++)
		{

		}
	}
};

#endif