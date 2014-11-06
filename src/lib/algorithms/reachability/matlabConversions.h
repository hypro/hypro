/*
*   This file contains methods to transfom c++ objects into matlab expressions such that 
*   the objects can be reconstrusted in matlab for debugging purpose
*   Author: Norman Hansen
*/

#include <iostream>
#include <fstream>

namespace hypro
{
         /*
         * writes a matrix_t<double> object into a file in matlab snytax
         * (only used for debug purpose)
         */
          void matrixToMatlab(const char* file, matrix_t<double> m)
          {               
               std::ofstream outfile;
               outfile.open(file, std::ios::out);
               
               outfile << "[";
               for( int i=0; i<m.rows(); i++)
               {
                    for( int j=0; j<m.cols(); j++)
                    {
                        outfile << m(i,j).toDouble() << " ";
                    }
                    
                    if( i<m.rows()-1)
                    {
                        outfile << ";" << "\r\n";
                    }
               }
               outfile << "]";
               
               outfile.close();
          }          
}
