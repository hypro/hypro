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

<<<<<<< HEAD
#include <map>

#include <sys/time.h> 
=======
#include <sys/time.h>
>>>>>>> 4f0e6cccca664d2a209de7238d58921fdbd8b6bc

#include "../src/lib/config.h"
#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/Zonotope/Zonotope.h"


typedef int Number;

/*
int main(int argc, char** argv)
{
	typedef carl::FLOAT_T<double> Number;

    // Just creates an empty Center
<<<<<<< HEAD
    vector_t<Number> vCenter = vector_t<Number>(3);
    vCenter << 0, 0, 0;
    
    // Just creates the Generators (3 for now)
    matrix_t<Number> vGenerators = matrix_t<Number>(3,4);
    vGenerators << 1, 0, 0, 1,
                   0, 1, 0, 1,
                   0, 0, 1, 1;
    
=======
    hypro::vector_t<Number> vCenter = hypro::vector_t<Number>(3);
    vCenter(0) = 0;
    vCenter(1) = 0;
    vCenter(2) = 0;

    // Just creates the Generators (3 for now)
    hypro::matrix_t<Number> vGenerators = hypro::matrix_t<Number>(3,4);

    vGenerators(0, 0) = 1;
    vGenerators(1, 0) = 0;
    vGenerators(2, 0) = 0;

    vGenerators(0, 1) = 0;
    vGenerators(1, 1) = 1;
    vGenerators(2, 1) = 0;

    vGenerators(0, 2) = 0;
    vGenerators(1, 2) = 0;
    vGenerators(2, 2) = 1;

    vGenerators(0, 3) = 1;
    vGenerators(1, 3) = 1;
    vGenerators(2, 3) = 1;

>>>>>>> 4f0e6cccca664d2a209de7238d58921fdbd8b6bc
    //To test the uniteEqualVectors function!
    //
    //for (int i = 3; i < vGenerators.cols(); i++)
    //{
    //    vGenerators(0, i) = 1;
    //   vGenerators(1, i) = 0;
    //    vGenerators(2, i) = 0;
    //}

    hypro::Zonotope<Number> zonoExample(vCenter, vGenerators); // Creates an Zonotope

    // All we want now is write to see the results
    std::ofstream results("example_zonotope.txt");

    results << "Dimension: " << zonoExample.dimension() << "\n\n\n" << "Center: " << vCenter << "\n\n\n" << "Generators: \n" << zonoExample.generators() << "\n\n\n";

    zonoExample.uniteEqualVectors();

    results << "Number of Generators: " << zonoExample.numGenerators() << "\n\n\n" << "new Generators: \n" << zonoExample.generators() << "\n\n\n";

    struct timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    results << "Corners:\n" << zonoExample.vertices() << "\n\n\n"; // Here we unite equal vectors (for optimization), and calculate (recursive) the corners!!

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