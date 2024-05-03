#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>

class Layer
{
	std::vector<std::vector<double>> weights;
	std::vector<double> biases;
public:
	Layer(int size, int inputs)
	{
		weights = std::vector<std::vector<double>>(size);
		for (int i = 0; i < size; i++) weights[i] = std::vector<double>(inputs);
		biases = std::vector<double>(size);
	}
};

#endif
