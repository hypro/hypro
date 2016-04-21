
/* 
 * File:   example_supportpca.cpp
 * Author: Simon Froitzheim
 * 
 * Created on April 20, 2016, 5:26 PM
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
        //plotter.setObjectColor(plotter.addObject(vpolytope.vertices()), colors[red]);
        support = Converter<Number>::toSupportFunction(vpolytope);
        
        //second vpolytope (ambiguous box)
        vector_t<Number> p4 = vector_t<Number>(2);
        p4(0) = 1;
        p4(1) = 3;
        vector_t<Number> p5 = vector_t<Number>(2);
        p5(0) = 3;
        p5(1) = 1;
        vector_t<Number> p6 = vector_t<Number>(2);
        p6(0) = 5;
        p6(1) = 3;
        vector_t<Number> p7 = vector_t<Number>(2);
        p7(0) = 3;
        p7(1) = 5;
        typename hypro::VPolytope<Number>::pointVector points2;
	points2.push_back(Point<Number>(p4));
	points2.push_back(Point<Number>(p5));
        points2.push_back(Point<Number>(p6));
        points2.push_back(Point<Number>(p7));
        vpolytope2 = VPolytope<Number>(points2);  
        //plotter.setObjectColor(plotter.addObject(vpolytope2.vertices()), colors[red]);
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
        //plotter.setObjectColor(plotter.addObject(vpolytope3.vertices()), colors[red]);
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
        plotter.setObjectColor(plotter.addObject(vpolytope4.vertices()), colors[red]);
        support4 = Converter<Number>::toSupportFunction(vpolytope4);
        
        
        std::set<std::pair<long int,long int> > results;
        std::set<std::pair<long int,long int> > results2;
        std::set<std::pair<long int,long int> > results3;
        std::set<std::pair<long int,long int> > results4;
        Zonotope<Number> result;
        Zonotope<Number> result2;
        Zonotope<Number> result3;
        Zonotope<Number> result4;
        Zonotope<Number> result5;
        Zonotope<Number> result6;
        Zonotope<Number> result7;
        Zonotope<Number> result8;
        for( int index = 0 ; index < runs ; ++index){
                std::pair<long int,long int> testresult;

                //1st support function (triangle)
                clock::time_point start = clock::now();
                
                result = Converter<Number>::toZonotope(support, OVER, 7);
                
                std::cout << "Total time(H1): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                
                result2 = Converter<Number>::toZonotope(support, ALTERNATIVE, 7);
                
                std::cout << "Total time(B1): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;      
                results.insert(testresult);
                
                
                //2nd support function (ambiguous box)
                start = clock::now();
                
                result3 = Converter<Number>::toZonotope(support2, OVER, 7);
                
                std::cout << "Total time(H2): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                
                result4 = Converter<Number>::toZonotope(support2, ALTERNATIVE, 7);
                
                std::cout << "Total time(B2): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;      
                results2.insert(testresult);
                
                //3rd support function (point cloud)
                start = clock::now();
                
                result5 = Converter<Number>::toZonotope(support3, OVER, 7);
                
                std::cout << "Total time(H3): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                
                result6 = Converter<Number>::toZonotope(support3, ALTERNATIVE, 7);
                
                std::cout << "Total time(B3): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;      
                results3.insert(testresult);
                
                //4th polytope (stretched box)
                start = clock::now();
                
                result7 = Converter<Number>::toZonotope(support4, OVER, 8);
                
                std::cout << "Total time(H4): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.first = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;            
                
                result8 = Converter<Number>::toZonotope(support4, ALTERNATIVE, 7);
                
                std::cout << "Total time(B4): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;
                testresult.second = std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;      
                results4.insert(testresult);
                
                
                
        }

        double avgTri1 = 0;
        double avgAmbiBox1 = 0;
        double avgCloud1 = 0;
        double avgStretch1 = 0;
        double avgTri2 = 0;
        double avgAmbiBox2 = 0;
        double avgCloud2 = 0;
        double avgStretch2 = 0;


        
        for(auto resultIt = results.begin(); resultIt != results.end(); ++resultIt )
        {
                avgTri1 += double((*resultIt).first/double(runs));
                avgTri2 += double((*resultIt).second/double(runs));
        }
        
        for(auto resultIt = results2.begin(); resultIt != results2.end(); ++resultIt )
        {
                avgAmbiBox1 += double((*resultIt).first/double(runs));
                avgAmbiBox2 += double((*resultIt).second/double(runs));
        }
        
        for(auto resultIt = results3.begin(); resultIt != results3.end(); ++resultIt )
        {
                avgCloud1 += double((*resultIt).first/double(runs));
                avgCloud2 += double((*resultIt).second/double(runs));
        }
        
        for(auto resultIt = results4.begin(); resultIt != results4.end(); ++resultIt )
        {
                avgStretch1 += double((*resultIt).first/double(runs));
                avgStretch2 += double((*resultIt).second/double(runs));
        }
        

        std::cout << "AVGTri1: " << avgTri1 << std::endl;
        std::cout << "AVGAmbiBox1: " << avgAmbiBox1 << std::endl;
        std::cout << "AVGCloud1: " << avgCloud1 << std::endl;
        std::cout << "AVGStretch1: " << avgStretch1 << std::endl;
        std::cout << "AVGTri2: " << avgTri2 << std::endl;
        std::cout << "AVGAmbiBox2: " << avgAmbiBox2 << std::endl;
        std::cout << "AVGCloud2: " << avgCloud2 << std::endl;
        std::cout << "AVGStretch2: " << avgStretch2 << std::endl;
        
        //plotter.addObject(result.vertices());
        //plotter.addObject(result2.vertices());
        //plotter.addObject(result3.vertices());
        //plotter.addObject(result4.vertices());
        //plotter.addObject(result5.vertices());
        //plotter.addObject(result6.vertices());
        plotter.addObject(result7.vertices());
        //plotter.addObject(result8.vertices());
        
        plotter.plot2d();
        plotter.plotTex();

        return 0;

}
