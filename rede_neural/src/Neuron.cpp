#include "Neuron.h"

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned numOutPuts, unsigned myIndex) {
    for(unsigned c=0; c<numOutPuts; c++) {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
        //std::cout << m_outputWeights.back().weight << std::endl;
    }
    m_myIndex = myIndex;
}

Neuron::~Neuron() {
    //dtor
}

double Neuron::randomWeight() {
    return rand() / double(RAND_MAX);
}

void Neuron::SetOutputVal(double val) {
    m_outputVal = val;
}

double Neuron::GetOutputVal() const {
    return m_outputVal;
}

void Neuron::feedForward(const Layer &prevLayer) {
    double sum = 0.0;

    for(unsigned i=0; i<prevLayer.size(); i++) {
        sum += prevLayer[i].GetOutputVal() * prevLayer[i].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x) {
    return (tanh(x) + 1.0) / 2.0;
}

double Neuron::transferFunctionDerivative(double x) {
    return (2.0 * cosh(x) * cosh(x))/((cosh(2.0 * x) + 1) * (cosh(2.0 * x) + 1));
}

void Neuron::calcOutputGradients(double targetVal) {
    double delta = targetVal - m_outputVal;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer) {
    double dow = sumDOW(nextLayer);
    m_gradient = dow * Neuron::transferFunction(m_outputVal);
}

double Neuron::sumDOW(const Layer &nextLayer) const {
    double sum = 0.0;
    for(unsigned i=0; i<nextLayer.size() - 1; i++) {
        sum += m_outputWeights[i].weight * nextLayer[i].m_gradient;
    }
    return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer) {
    for(unsigned i=0; i<prevLayer.size(); i++) {
        Neuron &neuron = prevLayer[i];

        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        double newDeltaWeight = eta * neuron.GetOutputVal() * m_gradient + alpha * oldDeltaWeight;

        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
    }
}
