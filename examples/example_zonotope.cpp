/*
 * @file    example_zonotope.cpp
 * @author  Leonardo Winter Pereira
 * @since   2015-09-09
 * @version 2015-09-09
 */

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

#include <map>

#include <sys/time.h> 

#include "../src/lib/config.h"
#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/Zonotope/Zonotope.h"

using namespace hypro;
using namespace carl;

typedef int Number;

/*
int main(int argc, char** argv)
{
    // Just creates an empty Center
    vector_t<Number> vCenter = vector_t<Number>(3);
    vCenter << 0, 0, 0;
    
    // Just creates the Generators (3 for now)
    matrix_t<Number> vGenerators = matrix_t<Number>(3,4);
    vGenerators << 1, 0, 0, 1,
                   0, 1, 0, 1,
                   0, 0, 1, 1;
    
    //To test the uniteEqualVectors function!
    //
    //for (int i = 3; i < vGenerators.cols(); i++)
    //{
    //    vGenerators(0, i) = 1;
    //   vGenerators(1, i) = 0;
    //    vGenerators(2, i) = 0;
    //}
    
    Zonotope<Number> zonoExample(vCenter, vGenerators); // Creates an Zonotope
    
    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");
 
    results << "Dimension: " << zonoExample.dimension() << "\n\n\n" << "Center: " << vCenter << "\n\n\n" << "Generators: \n" << zonoExample.generators() << "\n\n\n";
    
    zonoExample.uniteEqualVectors();
    
    results << "Number of Generators: " << zonoExample.numGenerators() << "\n\n\n" << "new Generators: \n" << zonoExample.generators() << "\n\n\n";
    
    struct timeval t1, t2;
    double elapsedTime;
    
    // start timer
    gettimeofday(&t1, NULL);
    
    results << "Corners:\n" << zonoExample.corners() << "\n\n\n"; // Here we unite equal vectors (for optimization), and calculate (recursive) the corners!!
    
    // stop timer
    gettimeofday(&t2, NULL);
    
    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    
    results << "Time spent: " << elapsedTime << "ms\n";
    
    results.close(); // Just closes the file 
    
    return 0;
}
*/

int main ()
{
    vector_t<Number> vCenter = vector_t<Number>(3);
    vCenter << 0, 0, 0;
    
    matrix_t<Number> vGenerators = matrix_t<Number>(3,4);
    vGenerators << 1, 0, 0, 1,
                   0, 1, 0, 1,
                   0, 0, 1, 1;
    
    std::unordered_map<vector_t<Number>, matrix_t<Number>, std::hash<vector_t<Number> > > myHash;
    myHash = {{vCenter, vGenerators}};
   
    std::ofstream results("example_zonotope.txt");
    
    results << "\n\n\n\n";
    
    results << "myHash contains: ";
  
    for ( auto it = myHash.begin(); it != myHash.end(); ++it )
        results << "\n" << it->first << ":\n" << it->second;
  
    results << "\n\n\n\n";

    results << "myHash's buckets contain:\n";
  
    for ( unsigned i = 0; i < myHash.bucket_count(); ++i) {
        results << "bucket #" << i << " contains:";
   
        for ( auto local_it = myHash.begin(i); local_it!= myHash.end(i); ++local_it )
            results << " " << local_it->first << ":" << local_it->second;
   
        results << "\n\n\n\n";
    }

    return 0;
}