/*
*   This file contains methods to transfom c++ objects into matlab expressions such that 
*   the objects can be reconstrusted in matlab for debugging purpose
*   Author: Norman Hansen
*/

namespace hypro
{
         /*
         * writes a matrix_t<double> object into a file in matlab snytax
         */
          void matrixToMatlab(const char* file, matrix_t<double> m)
          {
               FILE *fp;
               fp=fopen(file, "w");
               
               
               fprintf(fp, "[");
               
               
               for( int i=0; i<m.rows(); i++)
               {
                    for( int j=0; j<m.cols(); j++)
                    {
                        fprintf(fp, "%f ", m(i,j).toDouble()); 
                    }
                    if( i<m.rows()-1)
                    {
                        fprintf(fp, "; ");
                    }
               }
               
               fprintf(fp, "]");
   
               fclose(fp);
          }          
}
