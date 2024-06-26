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
    std::vector<double> sums;
    std::vector<double> activations;

	Layer(int size, int inputs)
	{
        nodeValues = std::vector<double>(size);
        weights = std::vector<std::vector<double>>(size);
        weightGradients = std::vector<std::vector<double>>(size);
        activations = std::vector<double>(size);
        sums = std::vector<double>(size);
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_real_distribution<double> distr(-sqrt(6.0 / (size + inputs)), sqrt(6.0 / (size + inputs)));
        for (int i = 0; i < size; i++) 
        {
            weights[i] = std::vector<double>(inputs);
            weightGradients[i] = std::vector<double>(inputs);
            for(int j = 0; j < inputs; j++) weights[i][j] = distr(engine);
        }
        biases = std::vector<double>(size, 0);
        biasGradients = std::vector<double>(size);
	}

    std::vector<double> calculateOutputs(const std::vector<double>& inputs, bool isOutput)
    {
        int inputSize = weights[0].size();
        if(inputs.size() > inputSize) throw std::length_error("too many inputs");
        std::vector<double> output(weights.size(), 0);
        for(size_t node = 0; node < output.size(); node++)
        {
            for(size_t input = 0; input < inputSize; input++) output[node] += inputs[input] * weights[node][input];
            output[node] += biases[node];
            this->sums[node] = output[node];
            output[node] = isOutput ? sigmoidActivation(output[node]) : reluActivation(output[node]);
            this->activations[node] = output[node];
        }
        
        return output;
    }

    static double reluActivation(double x)
    {
        return x < 0 ? 0 : x;
    }

    static double reluDerivative(double x)
    {
        return x <= 0 ? 0 : 1;
    }

    static double sigmoidActivation(double x)
    {
        return 1 / (1 + std::exp(-x));
    }

    static double sigmoidDerivative(double x)
    {
        return std::exp(-x) / std::pow(1 + std::exp(-x), 2);
    }

    void resetGradients()
    {
        for(size_t node = 0; node < biases.size(); node++)
        {
            biasGradients[node] = 0;
            for(size_t i = 0; i < weightGradients[node].size(); i++)
            {
                weightGradients[node][i] = 0;
            }
        }
    }

    void applyGradients(double learnRate)
    {
        for(size_t i = 0; i < biases.size(); i++)
        {
            for(size_t j = 0; j < weights[i].size(); j++)
            {
                weights[i][j] -= weightGradients[i][j] * learnRate;
            }
            biases[i] -= biasGradients[i] * learnRate;
        }
    }
};

#endif
