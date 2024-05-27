#ifndef DATASET_H
#define DATASET_H

#include <vector>

class Dataset
{
public:
    std::vector<double> output;
    std::vector<double> expected;

    Dataset(std::vector<double> output, std::vector<double> expected)
    {
        this->output = output;
        this->expected = expected;
    }
};

#endif