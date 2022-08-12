#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/datastructures/Halfspace.h>

//#include <hypro/util/linearOptimization/smtrat/adaptions_smtrat.h>


int main(){

  typedef mpq_class number_t;

  //------------first testpolys------------
  hypro::matrix_t<number_t> matrix1 = hypro::matrix_t<number_t>(4, 2);
  matrix1 << -1, 0, 1, 0, 0, -1, 0, 1;
  hypro::vector_t<number_t> constants1 = hypro::vector_t<number_t>(4);
  constants1 << 0, 3, 0, 3;
  hypro::HPolytope<number_t> hpoly1(matrix1, constants1);
  //std::vector<hypro::Point<number_t>> hvertices=hpoly.vertices();
  //std::cout << hvertices << std::endl;

  hypro::matrix_t<number_t> matrix3 = hypro::matrix_t<number_t>(4, 2);
  matrix3 << -1, 0, 1, 0, 0, -1, 0, 1;
  hypro::vector_t<number_t> constants3 = hypro::vector_t<number_t>(4);
  constants3 <<  -1, 2, -1, 3;
  hypro::HPolytope<number_t> minuspoly1(matrix3, constants3);
  //std::vector<hypro::Point<number_t>> minusvertices=minuspoly.vertices();
  //std::cout << minusvertices << std::endl;

  //------------second testpolys (minuspoly not completely contained in hpoly)------------
  hypro::matrix_t<number_t> matrix = hypro::matrix_t<number_t>(3, 2);
  matrix << 0 , 1, 1.5, -1, -3, -1;
  hypro::vector_t<number_t> constants = hypro::vector_t<number_t>(3);
  constants << 3, 1.5, -3;
  hypro::HPolytope<number_t> hpoly(matrix, constants);
  //std::vector<hypro::Point<number_t>> hvertices=hpoly.vertices();
  //std::cout << hvertices << std::endl;

  hypro::matrix_t<number_t> matrix2 = hypro::matrix_t<number_t>(4, 2);
  matrix2 << -1, 0, 1, 0, 0, -1, 0, 1;
  hypro::vector_t<number_t> constants2 = hypro::vector_t<number_t>(4);
  constants2 <<  -0.25, number_t(7)/number_t(3), -1, 2; //number_t(-1)/number_t(3),number_t(8)/number_t(3)
  hypro::HPolytope<number_t> minuspoly(matrix2, constants2);
  //std::vector<hypro::Point<number_t>> minusvertices=minuspoly.vertices();
  //std::cout << minusvertices << std::endl;

  //------------setminus------------
  std::vector<hypro::HPolytope<number_t>> result= hpoly.setMinus2(minuspoly);
  //------------output result------------
  for (long unsigned int j = 0; j < result.size(); j++){
        std::vector<hypro::Point<number_t>> vertices=result.at(j).vertices();
        std::cout << vertices << std::endl;
        //std::cout << result.at(j) << std::endl;
  }

  //------------algorithm, different than in HPolytope.tpp (for testing new implementations)------------
  /*minuspoly=minuspoly.removeRedundancy();
  matrix2 = minuspoly.matrix();
  constants2= minuspoly.vector();

  std::vector<hypro::HPolytope<number_t>> result;
  hypro::HPolytope<number_t> copy(hpoly.matrix(), hpoly.vector());
  //std::vector<hypro::Point<number_t>> minusvertices=minuspoly1.vertices();
  std::vector<hypro::Halfspace<number_t>> minusconstraints= minuspoly.constraints();
  std::vector<hypro::Halfspace<number_t>> hpolyconstraints= hpoly.constraints();
  
  
  for (long unsigned int i = 0; i < minusconstraints.size(); i++){
      hypro::Halfspace<number_t> h=minusconstraints.at(i);
      //h2 not necessary, but more obvious
      hypro::Halfspace<number_t> h2=h; 
      h2.invert();
      //X: number of constraints
      int x= matrix2.rows()+hpoly.matrix().rows()+1;
      hypro::matrix_t<number_t> checkmatrix=hypro::matrix_t<number_t>(x, 2);
      hypro::vector_t<number_t> checkvector = hypro::vector_t<number_t>(x);
      //create constraints als matrix and vector
      for (long int t = 0; t < matrix2.rows(); t++){
        for (long int v = 0; v<matrix2.cols(); v++){
          checkmatrix(t,v)=matrix2.row(t)(v);
        }
        checkvector(t)=constants2(t);
      }
      for (long int t = 0; t < hpoly.matrix().rows(); t++){
        for (long int v = 0; v<matrix2.cols(); v++){
          checkmatrix(t+ matrix2.rows(),v)=hpoly.matrix().row(t)(v);
        }
        checkvector(t+ matrix2.rows())=hpoly.vector()(t);
      }
      for (long int v = 0; v<matrix2.cols(); v++){
          checkmatrix(x-1,v)=h2.normal()(v);
        }
      checkvector(x-1)=h2.offset();
      //use optimizer to solve LP
      hypro::Optimizer<number_t> opt;
		  opt.setMatrix(checkmatrix);
		  opt.setVector(checkvector);
      //default relation is LEQ, set LESS for original polytop
      for (long int t = 0; t < hpoly.matrix().rows(); t++){
        opt.setRelation(carl::Relation::LESS,t+ matrix2.rows());
      }
      bool check= opt.checkConsistency();
      //create polytope and add to result vector
      if (check){
        hypro::HPolytope<number_t> workpoly=copy;
        workpoly.insert(h2);
        result.push_back(workpoly);
        copy.insert(h);
      }else{
        std::cout << "not helpful" << std::endl;
      }
      
      bool c=false;
      for (long unsigned int k = 0; k < hpolyconstraints.size(); k++){
        if (h==hpolyconstraints.at(k)){
           c=true;
        }
        
      }
      if(!c){
        hypro::HPolytope<number_t> workpoly=copy;
        workpoly.insert(h.invert());        
        if (!workpoly.empty()){
          hypro::HPolytope<number_t> checkpoly=workpoly;
          for (long unsigned int check = 0; check <  minusconstraints.size(); check++){
            hypro::Halfspace<number_t> checkh=minusconstraints.at(check);
            checkpoly.insert(checkh);
          }
          if (!checkpoly.empty()){
            result.push_back(workpoly);
            copy.insert(h.invert());
          }else{
            std::cout << "not helpful" << std::endl;
          }
        }else{
            //result.push_back(workpoly);
            std::cout << "empty" << std::endl;
        }
      }else{
        std::cout << "gleich" << std::endl;
      }
    }
    for (long unsigned int j = 0; j < result.size(); j++){
        std::vector<hypro::Point<number_t>> vertices=result.at(j).vertices();
        std::cout << vertices << std::endl;
        //std::cout << result.at(j) << std::endl;
    }*/

}