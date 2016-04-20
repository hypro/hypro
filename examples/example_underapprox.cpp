/* 
 * File:   example_underapprox.cpp
 * Author: simon.froitzheim
 * 
 * Created on April 20, 2016, 6:15 PM
 */

#include "../src/lib/representations/Box/Box.h"
#include <cstdlib>
#include "../src/lib/config.h"
#include <chrono>
#include <mpfr.h>
#include <set>
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
        Plotter<Number>& plotter = Plotter<Number>::getInstance();
        
        hypro::VPolytope<Number> vpolytope;
        hypro::VPolytope<Number> vpolytope2;
        hypro::VPolytope<Number> vpolytope3;
        hypro::VPolytope<Number> vpolytope4;
        
        hypro::SupportFunction<Number> support;
        hypro::SupportFunction<Number> support2;
        hypro::SupportFunction<Number> support3;
        hypro::SupportFunction<Number> support4;
        
        
        //first vpolytope (simple triangle 2D)
        vector_t<Number> p1 = vector_t<Number>(2);
        p1(0) = 1;
        p1(1) = 2;
        vector_t<Number> p2 = vector_t<Number>(2);
        p2(0) = 3;
        p2(1) = 2;
        vector_t<Number> p3 = vector_t<Number>(2);
        p3(0) = 1;
        p3(1) = 4;
        typename hypro::VPolytope<Number>::pointVector points;
	points.push_back(Point<Number>(p1));
	points.push_back(Point<Number>(p2));
        points.push_back(Point<Number>(p3));
        vpolytope = VPolytope<Number>(points);
        plotter.setObjectColor(plotter.addObject(vpolytope.vertices()), colors[red])
        support = Converter<Number>::toSupportFunction(vpolytope);
        
        //second vpolytope (ambiguous box)
        vector_t<Number> p4 = vector_t<Number>(2);
        p4(0) = 2.5;
        p4(1) = 1;
        vector_t<Number> p5 = vector_t<Number>(2);
        p5(0) = 1;
        p5(1) = 2.5;
        vector_t<Number> p6 = vector_t<Number>(2);
        p6(0) = 4;
        p6(1) = 2.5;
        vector_t<Number> p7 = vector_t<Number>(2);
        p7(0) = 2.5;
        p7(1) = 4;
        typename hypro::VPolytope<Number>::pointVector points2;
	points2.push_back(Point<Number>(p4));
	points2.push_back(Point<Number>(p5));
        points2.push_back(Point<Number>(p6));
        points2.push_back(Point<Number>(p7));
        vpolytope2 = VPolytope<Number>(points2); 
        //plotter.setObjectColor(plotter.addObject(vpolytope2.vertices()), colors[red];
        support2 = Converter<Number>::toSupportFunction(vpolytope2);
        
        //third  vpolytope (point cloud)
        vector_t<Number> p8 = vector_t<Number>(2);
        p8(0) = 2;
        p8(1) = 1;
        vector_t<Number> p9 = vector_t<Number>(2);
        p9(0) = 3;
        p9(1) = 1;
        vector_t<Number> p10 = vector_t<Number>(2);
        p10(0) = 2;
        p10(1) = 2;
        vector_t<Number> p11 = vector_t<Number>(2);
        p11(0) = 1;
        p11(1) = 2;
        vector_t<Number> p12 = vector_t<Number>(2);
        p12(0) = 1;
        p12(1) = 3;
        vector_t<Number> p13 = vector_t<Number>(2);
        p13(0) = 3;
        p13(1) = 3;
        vector_t<Number> p14 = vector_t<Number>(2);
        p14(0) = 2;
        p14(1) = 4;
        vector_t<Number> p15 = vector_t<Number>(2);
        p15(0) = 4;
        p15(1) = 4;
        vector_t<Number> p16 = vector_t<Number>(2);
        p16(0) = 5;
        p16(1) = 4;
        vector_t<Number> p17 = vector_t<Number>(2);
        p17(0) = 4;
        p17(1) = 5;
        typename hypro::VPolytope<Number>::pointVector points3;
	points3.push_back(Point<Number>(p8));
	points3.push_back(Point<Number>(p9));
        points3.push_back(Point<Number>(p10));
        points3.push_back(Point<Number>(p11));
	points3.push_back(Point<Number>(p12));
	points3.push_back(Point<Number>(p13));
        points3.push_back(Point<Number>(p14));
        points3.push_back(Point<Number>(p15));
	points3.push_back(Point<Number>(p16));
	points3.push_back(Point<Number>(p17));
        vpolytope3 = VPolytope<Number>(points3);
        //plotter.setObjectColor(plotter.addObject(vpolytope3.vertices()), colors[red])
        support3 = Converter<Number>::toSupportFunction(vpolytope3);
        
        //fourth vpolytope (stretched box)
        vector_t<Number> p18 = vector_t<Number>(2);
        p18(0) = 1;
        p18(1) = 4;
        vector_t<Number> p19 = vector_t<Number>(2);
        p19(0) = 2;
        p19(1) = 5;
        vector_t<Number> p20 = vector_t<Number>(2);
        p20(0) = 4;
        p20(1) = 1;
        vector_t<Number> p21 = vector_t<Number>(2);
        p21(0) = 5;
        p21(1) = 2;
        typename hypro::VPolytope<Number>::pointVector points4;
	points4.push_back(Point<Number>(p18));
	points4.push_back(Point<Number>(p19));
        points4.push_back(Point<Number>(p20));
        points4.push_back(Point<Number>(p21));
        vpolytope4 = VPolytope<Number>(points4);  
        //plotter.setObjectColor(plotter.addObject(vpolytope4.vertices()), colors[red])
        support4 = Converter<Number>::toSupportFunction(vpolytope4);
        
        
        
        std::set<long int> results;
        std::set<long int> results2;
        std::set<long int> results3;
        std::set<long int> results4;
        for( int index = 0 ; index < runs ; ++index){
                long int testresult;

                //1st polytope (triangle)
                clock::time_point start = clock::now();
                
                auto result = Converter<Number>::toVPolytope(support, UNDER);
                
                std::cout << "Total time(triangle): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                results.insert(testresult);
                
                //2nd polytope (ambiguous box)
                start = clock::now();
                
                auto result2 = Converter<Number>::toHPolytope(support2, UNDER);
                
                std::cout << "Total time(ambiBox): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                results2.insert(testresult);
                
                //3rd polytope (point cloud)
                start = clock::now();
                
                auto result3 = Converter<Number>::toHPolytope(support3, UNDER);
                
                std::cout << "Total time(pointCloud): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                results3.insert(testresult);
                
                //4th polytope (stretched box)
                start = clock::now();
                
                auto result4 = Converter<Number>::toHPolytope(support4, UNDER);
                
                std::cout << "Total time(stretchBox): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                results4.insert(testresult);
                
                
                
        }

        double avgTri = 0;
        double avgAmbiBox = 0;
        double avgCloud = 0;
        double avgStretch = 0;


        
        for(auto resultIt = results.begin(); resultIt != results.end(); ++resultIt )
        {
                avgTri += double((*resultIt)/double(runs));
        }
        
        for(auto resultIt = results2.begin(); resultIt != results2.end(); ++resultIt )
        {
                avgAmbiBox += double((*resultIt)/double(runs));
        }
        
        for(auto resultIt = results3.begin(); resultIt != results3.end(); ++resultIt )
        {
                avgCloud += double((*resultIt)/double(runs));
        }
        
        for(auto resultIt = results4.begin(); resultIt != results4.end(); ++resultIt )
        {
                avgStretch += double((*resultIt)/double(runs));
        }
        

        std::cout << "AVGTri: " << avgTri << std::endl;
        std::cout << "AVGAmbiBox: " << avgAmbiBox << std::endl;
        std::cout << "AVGCloud: " << avgCloud << std::endl;
        std::cout << "AVGStretch: " << avgStretch << std::endl;
        
        plotter.addObject(result.vertices());
        //plotter.addObject(result2.vertices());
        //plotter.addObject(result3.vertices());
        //plotter.addObject(result4.vertices());

        return 0;

}



