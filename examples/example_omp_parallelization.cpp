#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "omp.h"

typedef int Number;

void print_vector(const std::vector<Number>& vect) {
    int n = vect.size();
    std::cout << "vect = ( ";
    for(int i =0; i < n; i++) {
        std::cout << vect[i] << " ";
    }
    std::cout << ")" << std::endl;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // #pragma omp parallel
    // {
    //     int ID = omp_get_thread_num();
    //     printf("Hello(%d) ", ID);
    //     printf(" world(%d) \n", ID);
    // }

    int m = 5 + rand() % 5;
    std::cout << "m = " << m << std::endl;

    std::vector<Number> result = std::vector<Number>();
    result.push_back(1 + rand() % 3);
    print_vector(result);

    // simulation of iterating over m layers
    for(int i = 0; i < m; i++) {
        int N = result.size();

        #pragma omp parallel for
        for(int j = 0; j < N; j++) {
            Number current = result[j];

            std::vector<Number> inner_results = std::vector<Number>();
            for(int k = 0; k < current; k++) {
                inner_results.push_back(1 + rand() % 3);
            }

            result.insert( result.end(), inner_results.begin(), inner_results.end() );
        }

    }
    
    return 0;
}
