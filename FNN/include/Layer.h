#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <random>
#include <numeric>

class Layer
{
public:
    std::vector<std::vector<double>> weights;
    std::vector<std::vector<double>> weightGradients;
	std::vector<double> biases;
    std::vector<double> biasGradients;
    std::vector<double> nodeValues;

	Layer(int size, int inputs)
	{
        nodeValues = std::vector<double>(size);
		weights = std::vector<std::vector<double>>(size);
        weightGradients = std::vector<std::vector<double>>(size);
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_real_distribution distr(0.0, 1.0);
		for (int i = 0; i < size; i++) 
        {
            weights[i] = std::vector<double>(inputs);
            weightGradients[i] = std::vector<double>(inputs);
            for(int j = 0; j < inputs; j++) weights[i][j] = distr(engine);
        }
		biases = std::vector<double>(size);
        biasGradients = std::vector<double>(size);
        for(int i = 0; i < size; i++) biases[i] = distr(engine);
	}

    std::vector<double> calculateOutputs(std::vector<double> inputs)
    {
        int inputSize = weights[0].size();
        if(inputs.size() > inputSize) throw std::length_error("too many inputs");
        std::vector<double> output(weights.size(), 0);
        for(int node = 0; node < output.size(); node++)
        {
            for(int input = 0; input < inputSize; input++) output[node] += inputs[input] * weights[node][input];
            output[node] += biases[node];
        }
        return output;
    }

    void resetGradients()
    {
        for(size_t node = 0; biases.size(); node++)
        {
            biasGradients[node] = 0;
            for(size_t i = 0; i < weightGradients[node].size(); i++)
            {
                weightGradients[node][i] = 0;
            }
        }
    }
};

#endif
