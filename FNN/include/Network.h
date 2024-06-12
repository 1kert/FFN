#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"
#include "Dataset.h"
#include <vector>

class Network
{
public:
	std::vector<Layer> layers;
	
	Network(const std::vector<int>& layers)
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

	std::vector<double> calculateOutputs(std::vector<double>& inputs)
	{
		for(size_t i = 0; i < layers.size(); i++)
		{
			inputs = layers[i].calculateOutputs(inputs, false);
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

	double calculateError(const std::vector<Dataset>& data)
	{
		double error = 0;
		for(size_t i = 0; i < data.size(); i++) error += calculateError(data[i]);
		return error / data.size();
	}

	void resetAllGradients()
	{
		for(size_t i = 0; i < layers.size(); i++) layers[i].resetGradients();
	}

	void updateGradients(Dataset dataset)
	{
		calculateOutputs(dataset.data);

		Layer& outputLayer = layers[layers.size() - 1];
		for(size_t i = 0; i < outputLayer.sums.size(); i++)
		{
			outputLayer.nodeValues[i] = Layer::sigmoidDerivative(outputLayer.sums[i]) * 2 * (outputLayer.activations[i] - dataset.expected[i]);
		}
		
		
		resetAllGradients();
		for(size_t i = 0; i < outputLayer.activations.size(); i++)
		{
			for(size_t j = 0; j < outputLayer.weights[i].size(); j++)
			{
				outputLayer.weightGradients[i][j] += outputLayer.nodeValues[i] * layers[layers.size() - 2].activations[j];
			}
			outputLayer.biasGradients[i] += outputLayer.nodeValues[i];
		}
		for(size_t i = layers.size() - 2; i >= 0; i--)
		{
			Layer& current = layers[i];
			Layer& prev = layers[i + 1];
			
			for(size_t node = 0; node < current.activations.size(); node++)
			{
				double nodeValue = 0;
				for(size_t prevNode = 0; prevNode < prev.biases.size(); prevNode++) nodeValue += prev.weights[prevNode][node] * prev.nodeValues[prevNode];
				current.nodeValues[node] = nodeValue * Layer::sigmoidDerivative(current.sums[node]);
				current.biasGradients[node] += current.nodeValues[node];
				if(i == 0)
				{
					for(size_t j = 0; j < current.weightGradients[node].size(); j++)
					{
						current.weightGradients[node][j] += current.nodeValues[node] * dataset.data[j];
					}
					return;
				}

				for(size_t j = 0; j < current.weightGradients[node].size(); j++)
				{
					current.weightGradients[node][j] += current.nodeValues[node] * layers[i - 1].activations[j];
				}
			}
		}
	}

	void applyGradients(double learnRate)
	{
		for(size_t i = 0; i < layers.size(); i++)
		{
			layers[i].applyGradients(learnRate);
		}
		
	}

	void Learn(Dataset data, double learnRate)
	{
		updateGradients(data);
		applyGradients(learnRate);
	}
};

#endif