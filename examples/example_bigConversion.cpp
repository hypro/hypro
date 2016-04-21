#include "../src/lib/representations/Box/Box.h"
#include <cstdlib>
#include "../src/lib/config.h"
#include <chrono>
#include <mpfr.h>
#include <set>
#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../src/lib/util/helperFunctions.h"
#include "../src/lib/representations/conversion/Converter.h"

using namespace hypro;
using namespace carl;

int main(int argc, char const *argv[])
{
	typedef cln::cl_RA Number;
        typedef std::chrono::high_resolution_clock clock;
        typedef std::chrono::microseconds timeunit;
        const int runs = 50;
        
        hypro::HPolytope<Number> hpolytope;
        hypro::HPolytope<Number> hpolytope2;
        hypro::HPolytope<Number> hpolytope3;
        hypro::VPolytope<Number> vpolytope;
        hypro::VPolytope<Number> vpolytope2;
        hypro::VPolytope<Number> vpolytope3;
        hypro::SupportFunction<Number> support;
        hypro::SupportFunction<Number> support2;
        hypro::SupportFunction<Number> support3;
        hypro::Zonotope<Number> zonotope;
        hypro::Zonotope<Number> zonotope2;
        hypro::Zonotope<Number> zonotope3;
        hypro::Box<Number> box;
        hypro::Box<Number> box2;
        hypro::Box<Number> box3;
        
        
        
        std::vector<vector_t<Number>> directions = computeTemplate<Number>(3, 8);
        matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(directions.size(), 3);

        //fills the matrix with the template directions
        for (unsigned i=0; i<directions2.size();++i){
                templateDirectionMatrix.row(i) = directions[i];
        }
        
        vector_t<Number> distances = vector_t<Number>(directions.size());
        
        //fills the vector with a constant offset
        for (unsigned i=0; i<directions.size();++i){
                distances(i) = 5;
        }
        hpolytope = hypro::HPolytope<Number>(templateDirectionMatrix, distances);
        
        //second Hpolytope (3d object)
        std::vector<vector_t<Number>> directions2 = computeTemplate<Number>(3, 12);
        matrix_t<Number> templateDirectionMatrix2 = matrix_t<Number>(directions2.size(), 3);

        //fills the matrix with the template directions
        for (unsigned i=0; i<directions2.size();++i){
                templateDirectionMatrix2.row(i) = directions2[i];
        }
        
        vector_t<Number> distances2 = vector_t<Number>(directions2.size());
        
        //fills the vector with a constant offset
        for (unsigned i=0; i<directions2.size();++i){
                distances2(i) = 5;
        }
        
        hpolytope2 = hypro::HPolytope<Number>(templateDirectionMatrix2, distances2);
        
        //third Hpolytope (3d object (nearly a ball))
        std::vector<vector_t<Number>> directions3 = computeTemplate<Number>(3, 16);
        matrix_t<Number> templateDirectionMatrix3 = matrix_t<Number>(directions3.size(), 3);

        //fills the matrix with the template directions
        for (unsigned i=0; i<directions3.size();++i){
                templateDirectionMatrix3.row(i) = directions3[i];
        }
        
        vector_t<Number> distances3 = vector_t<Number>(directions3.size());
        
        //fills the vector with a constant offset
        for (unsigned i=0; i<distances3.size();++i){
                distances3(i) = 5;
        }
        
        hpolytope3 = hypro::HPolytope<Number>(templateDirectionMatrix3, distances3);
        
        vpolytope = Converter<Number>::toVPolytope(hpolytope);
        vpolytope2 = Converter<Number>::toVPolytope(hpolytope2);
        vpolytope3 = Converter<Number>::toVPolytope(hpolytope3);
        
        zonotope = Converter<Number>::toZonotope(hpolytope);
        zonotope2 = Converter<Number>::toZonotope(hpolytope2);
        zonotope3 = Converter<Number>::toZonotope(hpolytope3);
        
        box = Converter<Number>::toBox(hpolytope);
        box2 = Converter<Number>::toBox(hpolytope2);
        box3 = Converter<Number>::toBox(hpolytope3);
        
        support = Converter<Number>::toSupportFunction(hpolytope);
        support2 = Converter<Number>::toSupportFunction(hpolytope2);
        support3 = Converter<Number>::toSupportFunction(hpolytope3);
        
        
        
        
        std::set<std::pair<long int,long int> > results;
        std::set<std::pair<long int,long int> > results2;
        std::set<std::pair<long int,long int> > results3;
        
        for( int index = 0 ; index < runs ; ++index){
                std::pair<long int,long int> testresult;

                //2nd polytope
                clock::time_point start = clock::now();
                
                Converter<Number>::toBox(hpolytope2);
                
                std::cout << "Total time2(ConvexHull): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;

                start = clock::now();
                Converter<Number>::toBox(hpolytope2, ALTERNATIVE);
                std::cout << "Total time2(Evaluation): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results2.insert(testresult);
                
                //3rd polytope
                start = clock::now();
                
                Converter<Number>::toBox(hpolytope3);
                
                std::cout << "Total time3(ConvexHull): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;

                start = clock::now();
                Converter<Number>::toBox(hpolytope3, ALTERNATIVE);
                std::cout << "Total time3(Evaluation): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results3.insert(testresult);                
        }

        double avgHull2 = 0;
        double avgEval2 = 0;        
        double avgHull3 = 0;
        double avgEval3 = 0;
        
        for(auto resultIt = results2.begin(); resultIt != results2.end(); ++resultIt )
        {
                avgHull2 += double((*resultIt).first/double(runs));
                avgEval2 += double((*resultIt).second/double(runs));
        }
        
        for(auto resultIt = results3.begin(); resultIt != results3.end(); ++resultIt )
        {
                avgHull3 += double((*resultIt).first/double(runs));
                avgEval3 += double((*resultIt).second/double(runs));
        }

        std::cout << "AVGHull2: " << avgHull2 << ", AVGEval2: " << avgEval2 << std::endl;
        std::cout << "AVGHull3: " << avgHull3 << ", AVGEval3: " << avgEval3 << std::endl;

        return 0;

}
