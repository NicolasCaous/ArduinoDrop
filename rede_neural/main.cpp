#include "Net.h"

int main()
{
    srand (time(NULL));

    std::vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(4);
    topology.push_back(1);
    Net myNet(topology);

    std::vector<double> inputVals;
    std::vector<double> targetVals;
    std::vector<double> resultVals;

    for(int i=0; i<1750; i++) {

        inputVals.clear();
        targetVals.clear();

        int r1 = rand();
        int r2 = rand();

        if(r1%2 && r2%2) {
            targetVals.push_back(1.0);
        } else {
            targetVals.push_back(0.0);
        }

        std::cout << "Teste: " << i + 1 << " R1: " << r1%2 * 1.0 << " R2: " << r2%2 * 1.0 << std::endl;
        std::cout << "Target: " << targetVals.back() << std::endl;

        inputVals.push_back(r1%2 * 1.0);
        inputVals.push_back(r2%2 * 1.0);

        myNet.feedForward(inputVals);
        myNet.backProp(targetVals);
        myNet.getResults(resultVals);

        if(resultVals[0] > 0.5) {
            resultVals[0] = 1;
        } else {
            resultVals[0] = 0;
        }

        std::cout << "Resposta: " << resultVals[0] << std::endl;
        std::cout << "Margem de erro: " << myNet.m_recentAverageError << std::endl;
        std::cout << std::endl;

    }
    return 0;
}
