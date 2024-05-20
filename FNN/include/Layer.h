#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <random>

class Layer
{
	std::vector<std::vector<double>> weights;
	std::vector<double> biases;
public:
	Layer(int size, int inputs)
	{
		weights = std::vector<std::vector<double>>(size);
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_real_distribution distr(0.0, 1.0);
		for (int i = 0; i < size; i++) 
        {
            weights[i] = std::vector<double>(inputs);
            for(int j = 0; j < inputs; j++) weights[i][j] = distr(engine);
        }
		biases = std::vector<double>(size);
        for(int i = 0; i < size; i++) biases[i] = distr(engine);
	}
};

#endif
