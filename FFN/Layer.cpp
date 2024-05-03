#include <iostream>
#include "Layer.h"

class Layer
{
public:
	int size;

	Layer(int size)
	{
		this->size = size;
	}

	void print()
	{
		printf("the size is %d\n", size);
	}
};

//Layer::Layer(int size)
//{
//	this->size = size;
//}
//
//void Layer::print()
//{
//	printf("the size is %d\n", size);
//}