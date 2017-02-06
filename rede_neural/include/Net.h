#include "Neuron.h"

#ifndef NET_H
#define NET_H


class Net
{
    public:
        Net(const std::vector<unsigned> &topology);
        void feedForward(const std::vector<double> &inputVals);
        void backProp(const std::vector<double> &targetVals);
        void getResults(std::vector<double> &resultVals) const;
        virtual ~Net();
        double m_recentAverageError;

    private:
        std::vector<Layer> m_layers;
        double m_error;
        double m_recentAverageSmoothingFactor;
};

#endif // NET_H
