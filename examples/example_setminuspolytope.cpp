#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/datastructures/Halfspace.h>

int main(){
    typedef mpq_class number_t;
    
  hypro::matrix_t<number_t> matrix = hypro::matrix_t<number_t>(4, 2);
  matrix << -0.5 , 1, 1, 1, 2, -1, -0.5, -1;
  hypro::vector_t<number_t> constants = hypro::vector_t<number_t>(4);
  constants << 2.5, 7, 5, -2.5;
  hypro::HPolytope<number_t> hpoly(matrix, constants);

  hypro::matrix_t<number_t> matrix2 = hypro::matrix_t<number_t>(4, 2);
  matrix2 << -0.5, 1, 3, 1, number_t(-1)/number_t(6), -1,-1,1;
  hypro::vector_t<number_t> constants2 = hypro::vector_t<number_t>(4);
  hypro::HPolytope<number_t> minuspoly(matrix2, constants2);

  std::vector<hypro::HPolytope<number_t>> result= hpoly.setMinus(minuspoly);

  for (long unsigned int i = 0; i < result.size(); i++){
       std::vector<hypro::Point<number_t>> vertices=result.at(i).vertices();
       if (vertices.size()==0)
       {
           std::cout << "keine vertices" << std::endl;
       }else{
           std::cout << vertices << std::endl;
       }
   }
  //std::vector<hypro::Point<number_t>> vertices2=minuspoly.vertices();
  //std::cout << vertices2 << std::endl;
  //std::cout << matrix2.size() << std::endl;
  /*minuspoly=minuspoly.removeRedundancy();
  matrix2 = minuspoly.matrix();
  constants2= minuspoly.vector();
  //std::cout << matrix2.size() << std::endl;

  //polytopes are in minimal reprsentation
  std::vector<hypro::HPolytope<number_t>> result;
  //hypro::matrix_t<number_t> copymatrix = matrix;
  //hypro::vector_t<number_t> copyconstants = constants;
  //hypro::HPolytope<number_t> workpoly(matrix, constants);
  hypro::HPolytope<number_t> copy(matrix, constants);
  //std::vector<hypro::Point<number_t>> vertices=copy.vertices();
  //std::cout << vertices << std::endl;
  for (int i = 0; i < constants2.size(); i++){
      //copymatrix.conservativeResize(matrix.rows()+i,2);
      //copymatrix(matrix.rows()+i,0)=1;//matrix2(i,0);
      //copymatrix(matrix.rows()+i,1)=1;//matrix2(i,1);
      //copyconstants.conservativeResize(constants.size()+i);
      //copyconstants(constants.size()+i)=1;//constants2(i);
      //hypro::Halfspace h( const std::vector<Point<Number>>& points );
      //hypro::vector_t<number_t> m=hypro::vector_t<number_t>(2);
      //m << 2.5, 7;
      hypro::Point<number_t> p =hypro::Point<number_t>(matrix2.row(i));
      //std::cout << p << std::endl;
      hypro::Point<number_t> q =hypro::Point<number_t>(constants2(i));
      //std::cout << q << std::endl;
      //hypro::Halfspace<number_t> h=hypro::Halfspace<number_t>{hypro::Point<number_t>({-1,1}), i};
      hypro::Halfspace<number_t> h=hypro::Halfspace<number_t>{p, q.at(0)};
      //hypro::Halfspace<number_t> h2=h;
      std::vector<hypro::Point<number_t>> vertices=copy.vertices();
      //std::cout << vertices << std::endl;
      hypro::HPolytope<number_t> workpoly=copy;
      //std::vector<hypro::Point<number_t>> vertices2=workpoly.vertices();
      //std::cout << vertices2 << std::endl;
      workpoly.insert(h.invert());
      //std::vector<hypro::Point<number_t>> vertices3=workpoly.vertices();
      //std::cout << vertices3 << std::endl;
      if (!workpoly.empty()){
          result.push_back(workpoly);
          copy.insert(h.invert());
      }else{
          //result.push_back(workpoly);
          std::cout << "empty" << std::endl;
      }
      
   }*/
  

}
