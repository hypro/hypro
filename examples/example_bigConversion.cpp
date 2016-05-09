#include "../src/lib/representations/Box/Box.h"
#include <cstdlib>
#include "../src/lib/config.h"
#include <chrono>
#include <mpfr.h>
#include <set>
#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../src/lib/util/helperFunctions.h"
#include "../src/lib/representations/conversion/Converter.h"
#include "../src/lib/util/Plotter.h"

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
        Plotter<Number>& plotter = Plotter<Number>::getInstance();
        
        //third zonotope (chapter 3 example)
        vector_t<Number> center3 = vector_t<Number>(2);
        center3 << 3, 3;
        matrix_t<Number> generators3 = matrix_t<Number>(2,3);
        generators3.col(0) << 0, 1;
        generators3.col(1) << 1, 1;
        generators3.col(2) << 2, -1;
        zonotope = hypro::Zonotope<Number>(center3, generators3);
        //plotter.addPoints(zonotope.vertices());
        
        
        
        std::vector<vector_t<Number>> directions = computeTemplate<Number>(2, 12);
        matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(directions.size(), 2);

        //fills the matrix with the template directions
        for (unsigned i=0; i<directions.size();++i){
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
        //plotter.addPoints(hpolytope.vertices());
        
        vpolytope = Converter<Number>::toVPolytope(hpolytope);
        vpolytope2 = Converter<Number>::toVPolytope(hpolytope2);
        vpolytope3 = Converter<Number>::toVPolytope(hpolytope3);
        plotter.addPoints(vpolytope.vertices());
        
        //zonotope = Converter<Number>::toZonotope(hpolytope);
        zonotope2 = Converter<Number>::toZonotope(hpolytope2);
        zonotope3 = Converter<Number>::toZonotope(hpolytope3);
        
        box = Converter<Number>::toBox(hpolytope);
        box2 = Converter<Number>::toBox(hpolytope2);
        box3 = Converter<Number>::toBox(hpolytope3);
        
        support = Converter<Number>::toSupportFunction(hpolytope);
        support2 = Converter<Number>::toSupportFunction(hpolytope2);
        support3 = Converter<Number>::toSupportFunction(hpolytope3);
        
        
        
        
        
        
        std::set<long int> results;
        std::set<long int> results2;
        std::set<long int> results3;
        std::set<long int> results4;
        std::set<long int> results5;
        std::set<long int> results6;
        std::set<long int> results7;
        std::set<long int> results8;       
        std::set<long int> results9;
        std::set<long int> results10;
        std::set<long int> results11;       
        std::set<long int> results12;
        std::set<long int> results13;
        std::set<long int> results14;        
        std::set<long int> results15;
        std::set<long int> results16;
        std::set<long int> results17;
        std::set<long int> results18;
        std::set<long int> results19;
        std::set<long int> results20;  
        std::set<long int> results21;
        std::set<long int> results22;
        std::set<long int> results23;
        std::set<long int> results24;  
        
        //v
        Box<Number> result3;
        HPolytope<Number> result6;
        HPolytope<Number> result7;
        Zonotope<Number> result17;
        
        //h
        Box<Number> result;
        Box<Number> result2;
        VPolytope<Number> result11;
        Zonotope<Number> result16;
        
        //sf
        Box<Number> result5;
        HPolytope<Number> result9;
        VPolytope<Number> result13;
        VPolytope<Number> result14;
        Zonotope<Number> result18;
        Zonotope<Number> result19;
        
        //zonotope
        Box<Number> result4;
        HPolytope<Number> result8;
        VPolytope<Number> result12;
        
        
        
        
        for( int index = 0 ; index < runs ; ++index){
                long int testresult;

                //tobox
                clock::time_point start = clock::now();
                
                result =Converter<Number>::toBox(hpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results.insert(testresult);
                
                start = clock::now();
                
                result2 = Converter<Number>::toBox(hpolytope, ALTERNATIVE);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results2.insert(testresult);
                
                start = clock::now();
                
                result3 = Converter<Number>::toBox(vpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results3.insert(testresult);
                
                start = clock::now();
                
                result4 = Converter<Number>::toBox(zonotope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results4.insert(testresult);   
                
                start = clock::now();
                
                result5 = Converter<Number>::toBox(support);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results5.insert(testresult);
                
                //tohpoly
                
                start = clock::now();
                
                result6 = Converter<Number>::toHPolytope(vpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results6.insert(testresult);
                
                start = clock::now();
                
                result7 = Converter<Number>::toHPolytope(vpolytope, OVER);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results7.insert(testresult);
                
                start = clock::now();
                
                result8 = Converter<Number>::toHPolytope(zonotope, OVER);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results8.insert(testresult);
                
                start = clock::now();
                
                result9 = Converter<Number>::toHPolytope(support, OVER, 8);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results9.insert(testresult);
                
                start = clock::now();
                
                Converter<Number>::toHPolytope(box);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results10.insert(testresult);
                
                //tovpolytope
                
                start = clock::now();
                
                result11 = Converter<Number>::toVPolytope(hpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results11.insert(testresult);
                
                start = clock::now();
                
                result12 = Converter<Number>::toVPolytope(zonotope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results12.insert(testresult);
                
                start = clock::now();
                
                result13 = Converter<Number>::toVPolytope(support, OVER, 8);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results13.insert(testresult);
                
                start = clock::now();
                
                result14 = Converter<Number>::toVPolytope(support, UNDER, 8);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results14.insert(testresult);
                
                start = clock::now();
                
                Converter<Number>::toVPolytope(box);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results15.insert(testresult);
                
                //tozonotope
                start = clock::now();
                
                result16 = Converter<Number>::toZonotope(hpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results16.insert(testresult);
                
                start = clock::now();
                
                result17 = Converter<Number>::toZonotope(vpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results17.insert(testresult);
                
                start = clock::now();
                
                result18 = Converter<Number>::toZonotope(support, OVER, 8);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results18.insert(testresult);
                
                start = clock::now();
                
                result19 = Converter<Number>::toZonotope(support, ALTERNATIVE, 8);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results19.insert(testresult);
                
                start = clock::now();
                
                Converter<Number>::toZonotope(box);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results20.insert(testresult);
                
                //tosupport
                start = clock::now();
                
                Converter<Number>::toSupportFunction(hpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results21.insert(testresult);
                
                start = clock::now();
                
                Converter<Number>::toSupportFunction(vpolytope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results22.insert(testresult);
                
                start = clock::now();
                
                Converter<Number>::toSupportFunction(zonotope);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results23.insert(testresult);
                
                start = clock::now();
                
                Converter<Number>::toSupportFunction(box);
                testresult= std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
                results24.insert(testresult);
                
                
                
                
                

          
        }
        //v-plots
        //plotter.addObject(result3.vertices());
        //plotter.addObject(result6.vertices());
        //plotter.addObject(result7.vertices());
        //plotter.addObject(result17.vertices());
        
        //h.plots
        //plotter.addObject(result.vertices());
        //plotter.addObject(result2.vertices());
        //plotter.addObject(result11.vertices());
        //lotter.addObject(result16.vertices()); 
        
        //sf plots
        //plotter.addObject(result5.vertices());
        plotter.addObject(result9.vertices());
        plotter.addObject(result13.vertices());
        //plotter.addObject(result14.vertices()); 
        //plotter.addObject(result18.vertices());
        //plotter.addObject(result19.vertices());
        
        //z plots
        //plotter.addObject(result4.vertices());
        //plotter.addObject(result8.vertices());
        //lotter.addObject(result12.vertices());        
       
        
        
        
        
        
        
        
        plotter.plot2d();
        plotter.plotTex();
        
        

        double avg1 = 0;
        double avg2 = 0;
        double avg3 = 0;
        double avg4 = 0;
        double avg5 = 0;
        double avg6 = 0;
        double avg7 = 0;
        double avg8 = 0;
        double avg9 = 0;
        double avg10 = 0;
        double avg11 = 0;
        double avg12 = 0;
        double avg13 = 0;
        double avg14 = 0;
        double avg15 = 0;
        double avg16 = 0;
        double avg17 = 0;
        double avg18 = 0;
        double avg19 = 0;
        double avg20 = 0;
        double avg21 = 0;
        double avg22 = 0;
        double avg23 = 0;
        double avg24 = 0;
        
        for(auto resultIt = results.begin(); resultIt != results.end(); ++resultIt )
        {
                avg1 += double((*resultIt)/double(runs));
        }
        
        for(auto resultIt = results2.begin(); resultIt != results2.end(); ++resultIt )
        {
                avg2 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results3.begin(); resultIt != results3.end(); ++resultIt )
        {
                avg3 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results4.begin(); resultIt != results4.end(); ++resultIt )
        {
                avg4 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results5.begin(); resultIt != results5.end(); ++resultIt )
        {
                avg5 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results6.begin(); resultIt != results6.end(); ++resultIt )
        {
                avg6 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results7.begin(); resultIt != results7.end(); ++resultIt )
        {
                avg7 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results8.begin(); resultIt != results8.end(); ++resultIt )
        {
                avg8 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results9.begin(); resultIt != results9.end(); ++resultIt )
        {
                avg9 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results10.begin(); resultIt != results10.end(); ++resultIt )
        {
                avg10 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results11.begin(); resultIt != results11.end(); ++resultIt )
        {
                avg11 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results12.begin(); resultIt != results12.end(); ++resultIt )
        {
                avg12 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results13.begin(); resultIt != results13.end(); ++resultIt )
        {
                avg13 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results14.begin(); resultIt != results14.end(); ++resultIt )
        {
                avg14 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results15.begin(); resultIt != results15.end(); ++resultIt )
        {
                avg15 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results16.begin(); resultIt != results16.end(); ++resultIt )
        {
                avg16 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results17.begin(); resultIt != results17.end(); ++resultIt )
        {
                avg17 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results18.begin(); resultIt != results18.end(); ++resultIt )
        {
                avg18 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results19.begin(); resultIt != results19.end(); ++resultIt )
        {
                avg19 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results20.begin(); resultIt != results20.end(); ++resultIt )
        {
                avg20 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results21.begin(); resultIt != results21.end(); ++resultIt )
        {
                avg21 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results22.begin(); resultIt != results22.end(); ++resultIt )
        {
                avg22 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results23.begin(); resultIt != results23.end(); ++resultIt )
        {
                avg23 += double((*resultIt)/double(runs));
        }
        for(auto resultIt = results24.begin(); resultIt != results24.end(); ++resultIt )
        {
                avg24 += double((*resultIt)/double(runs));
        }

        std::cout << "AVG1: " << avg1 << std::endl;
        std::cout << "AVG2: " << avg2 << std::endl;
        std::cout << "AVG3: " << avg3 << std::endl;
        std::cout << "AVG4: " << avg4 << std::endl;
        std::cout << "AVG5: " << avg5 << std::endl;
        std::cout << "AVG6: " << avg6 << std::endl;
        std::cout << "AVG7: " << avg7 << std::endl;
        std::cout << "AVG8: " << avg8 << std::endl;
        std::cout << "AVG9: " << avg9 << std::endl;
        std::cout << "AVG10: " << avg10 << std::endl;
        std::cout << "AVG11: " << avg11 << std::endl;
        std::cout << "AVG12: " << avg12 << std::endl;
        std::cout << "AVG13: " << avg13 << std::endl;
        std::cout << "AVG14: " << avg14 << std::endl;
        std::cout << "AVG15: " << avg15 << std::endl;
        std::cout << "AVG16: " << avg16 << std::endl;
        std::cout << "AVG17: " << avg17 << std::endl;
        std::cout << "AVG18: " << avg18 << std::endl;
        std::cout << "AVG19: " << avg19 << std::endl;
        std::cout << "AVG20: " << avg20 << std::endl;
        std::cout << "AVG21: " << avg21 << std::endl;
        std::cout << "AVG22: " << avg22 << std::endl;
        std::cout << "AVG23: " << avg23 << std::endl;
        std::cout << "AVG24: " << avg24 << std::endl;
        


        return 0;

}
