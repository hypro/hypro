/*
 * File:   example_adddition.cpp
 * Author: stefan
 *
 * Created on November 20, 2013, 12:08 PM
 */

#include <cstdlib>
#include "../src/lib/config.h"
#include <chrono>
#include <mpfr.h>
#include <set>

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::microseconds timeunit;
    const int runs = 10;

    double f1 = 3.141592654;
    double f2 = 1.414786;

    carl::FLOAT_T<mpfr_t> hf1 = carl::FLOAT_T<mpfr_t>(f1);
    carl::FLOAT_T<mpfr_t> hf2 = carl::FLOAT_T<mpfr_t>(f2);
    carl::FLOAT_T<mpfr_t> result;

    mpfr_t mf1;
    mpfr_t mf2;
    mpfr_t mResult;

    mpfr_init(mf1);
    mpfr_init(mf2);
    mpfr_init(mResult);

    mpfr_set_d(mf1,f1,MPFR_RNDN);
    mpfr_set_d(mf2,f2,MPFR_RNDN);

    std::set<std::pair<long int,long int> > results;
    for( int index = 0 ; index < runs ; ++index)
    {
        std::pair<long int,long int> testresult;
        clock::time_point start = clock::now();
        int count = 0;
        while (count < 100000000)
        {
            hf1.add(result,hf2);
            ++count;
        }
        std::cout << "Total time(HYPRO): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
        testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;

        start = clock::now();
        count = 0;
        while (count < 100000000)
        {
            mpfr_add(mResult, mf1, mf2, MPFR_RNDN);
            ++count;
        }
        std::cout << "Total time(MPFR): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
        testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
        results.insert(testresult);
    }

    double avgHypro = 0;
    double avgMpfr = 0;

    for(auto resultIt = results.begin(); resultIt != results.end(); ++resultIt )
    {
        avgHypro += double((*resultIt).first/double(runs));
        avgMpfr += double((*resultIt).second/double(runs));
    }

    std::cout << "AVGHypro: " << avgHypro << ", AVGMpfr: " << avgMpfr << std::endl;

    return 0;
}

