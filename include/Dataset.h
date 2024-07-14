#ifndef DATASET_H
#define DATASET_H

#include <vector>

class Dataset
{
public:
    std::vector<double> data;
    std::vector<double> expected;

    Dataset(std::vector<double> data, std::vector<double> expected)
    {
        this->data = data;
        this->expected = expected;
    }
};

#endif