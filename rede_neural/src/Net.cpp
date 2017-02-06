#include "Net.h"

Net::Net(const std::vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for(unsigned i=0; i<numLayers; i++) {
        m_layers.push_back(Layer());
        unsigned numOutputs = (i == topology.size() - 1) ? 0 : topology[i + 1];

        for(unsigned j=0; j<=topology[i]; j++) {
            std::cout << "Fez Novo Neuronio YEEEAH " << i + 1 << std::endl;
            m_layers.back().push_back(Neuron(numOutputs, j));
        }

        m_layers.back().back().SetOutputVal(1.0);
    }
}

void Net::feedForward(const std::vector<double> &inputVals)
{
    assert(inputVals.size() == m_layers[0].size() - 1);

    for(unsigned i=0; i<inputVals.size(); i++) {
        m_layers[0][i].SetOutputVal(inputVals[i]);
    }

    for(unsigned i=1; i<m_layers.size(); i++) {
        Layer &prevLayer = m_layers[i - 1];
        for(unsigned j=0; j<m_layers[i].size() - 1; j++) {
            m_layers[i][j].feedForward(prevLayer);
        }
    }
}

void Net::backProp(const std::vector<double> &targetVals)
{
    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for(unsigned i=0; i<outputLayer.size() - 1; i++) {
        double delta = targetVals[i] - outputLayer[i].GetOutputVal();
        m_error += delta * delta;
    }

    m_error /= outputLayer.size() - 1;
    m_error = sqrt(m_error);

    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

    for(unsigned i=0; i<outputLayer.size() - 1; i++) {
        outputLayer[i].calcOutputGradients(targetVals[i]);
    }

    for(unsigned i=m_layers.size() - 2; i>0; i--) {
        Layer &hiddenLayer = m_layers[i];
        Layer &nextLayer = m_layers[i + 1];

        for(unsigned j=0; j<hiddenLayer.size(); j++) {
            hiddenLayer[j].calcHiddenGradients(nextLayer);
        }
    }

    for(unsigned i=m_layers.size() - 1; i>0; i--) {
        Layer &layer = m_layers[i];
        Layer &prevLayer = m_layers[i - 1];

        for(unsigned j=0; j<layer.size() - 1; j++)  {
            layer[j].updateInputWeights(prevLayer);
        }
    }
}

void Net::getResults(std::vector<double> &resultVals) const
{
    resultVals.clear();

    for(unsigned i=0; i<m_layers.size() - 1; i++) {
        resultVals.push_back(m_layers.back()[i].GetOutputVal());
    }
}

Net::~Net()
{
    //dtor
}
