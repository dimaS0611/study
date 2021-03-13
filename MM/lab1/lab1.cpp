#include <iostream>
#include <fstream>
#include <math.h>

const int K = 64;
const int A0 = 8195;
const int B = A0;
const int N = 1000;
unsigned const int M = pow(2, 31);

double tableElements[K];
unsigned int startValue = A0;


double multiplicativeMethod() {
    //Ai' = (Ai-1' * B)modM; Ai = Ai'/M
    startValue *= B;
    startValue %= M;
    
    return startValue * 1. / M;
}

void fillTable() {
    for (int i = 0; i < K; i++) {
        tableElements[i] = multiplicativeMethod();
    }
}

double updateRandomElement() {
    int s = rand() % K;
    double res = tableElements[s];
    
    tableElements[s] = multiplicativeMethod();
    
    return res;
}

bool kolmogorovCriteriaTest(int sampleSize, int observationsCount, double(*method)(), double critical) {
    double sup = 0;
    
    for (int i = 0; i < observationsCount; i++) {
        int hitsInInterval = 0;

        for (int j = 0; j < sampleSize; j++) {
            if (method() < (double)i / observationsCount) {
                hitsInInterval++;
            }
        }

        double F = (double)hitsInInterval / sampleSize;
        double delta = F - (double)i / observationsCount;
    
        if (sup < abs(delta)) {
            sup = delta;
        }
    }

    return sqrt(sampleSize) * sup < critical;
}

bool pirsonCriteriaTest(int sampleSize, int intervalsCount, double(*method)(), double critical) {
    int* frequences = new int[intervalsCount] {0};
  
    for (int i = 0; i < sampleSize; i++) {
        int generatedIndex = lround(method() * intervalsCount);
        frequences[generatedIndex]++;
    }

    double xi = 0;
    for (int i = 0; i < intervalsCount; i++) {
        double pEmpiric = frequences[i];
        double pTheoretical = (double)sampleSize / intervalsCount;
        xi += pow((pTheoretical - pEmpiric), 2) / pTheoretical;
    }
    
    return xi < critical;
}


int main() 
{
    std::ofstream out1("first_sensor_results.txt");
    std::ofstream out2("second_sensor_results.txt");

    fillTable();

    for (int i = 0; i < N; i++) {
        out1 << multiplicativeMethod() << std::endl;
    }

    for (int i = 0; i < N; i++) {
        out2 << updateRandomElement() << std::endl;
    }

    //critical for e = 0.05 is 37. (Kolmogorov table)
    std::cout << "Pirson criteria satisfied: " << pirsonCriteriaTest(N, 28, multiplicativeMethod, 41.3) << std::endl;

    //critical for e = 0.05 is 1.36 (Kolmogorov table)
    int criticalValue = 1.36;
    std::cout << "Kolmogorov criteria satisfied: " << kolmogorovCriteriaTest(100, N, multiplicativeMethod, criticalValue) << std::endl;

}

