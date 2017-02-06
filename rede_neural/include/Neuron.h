#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cassert>
#include <cmath>

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron;
typedef std::vector<Neuron> Layer;

#ifndef NEURON_H
#define NEURON_H

class Neuron
{
    public:
        Neuron(unsigned numOutPuts, unsigned myIndex);
        void SetOutputVal(double);
        double GetOutputVal() const;
        void feedForward(const Layer &prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const Layer &nextLayer);
        void updateInputWeights(Layer &prevLayer);
        virtual ~Neuron();

    private:
        static double eta;
        static double alpha;
        static double transferFunction(double x);
        static double transferFunctionDerivative(double x);
        static double randomWeight();
        double sumDOW(const Layer &nextLayer) const;
        double m_outputVal;
        std::vector<Connection> m_outputWeights;
        unsigned m_myIndex;
        double m_gradient;
};

#endif // NEURON_H
