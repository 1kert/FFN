#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>

class Layer
{
	int size;
	int inputs;
	double** weights;
public:
	Layer(int size, int inputs)
	{
		this->size = size;
		this->inputs = inputs;

		weights = new double* [size];
		for (int i = 0; i < size; i++) weights[i] = new double[inputs];
	}

	~Layer()
	{
		for (int i = 0; i < size; i++) delete[] weights[i];
		delete[] weights;
	}
};

#endif
