//#include "datastructures/Halfspace.h"
#include <hypro/representations/GeometricObjectBase.h>
//#include <hypro/representations/Box.h>
//#include <hypro/util/plotting/Plotter.h>
//#include <hypro/representations/GeometricObjectBase.h>


int main() {
  // use rational arithmetic.
  typedef mpq_class Number;

  // create a box out of two given limit points.
  hypro::Box<Number> testbox(std::make_pair(hypro::Point<Number>({1, 1}),
                                            hypro::Point<Number>({4, 4})));
  
  hypro::Box<Number> minusbox(std::make_pair(hypro::Point<Number>({2, 2}),
                                            hypro::Point<Number>({3, 3})));

  std::vector<hypro::Box<Number>> test1= testbox.setMinus(minusbox); 
  for (long unsigned int i = 0; i < test1.size(); i++){
      std::cout << test1.at(i) << std::endl;
  }

  std::vector<hypro::Box<Number>> test2= testbox.setMinus2(minusbox); 
  for (long unsigned int i = 0; i < test2.size(); i++){
      std::cout << test2.at(i) << std::endl;
  }


  /*std::vector<carl::Interval<Number>> box=testbox.intervals();
  std::vector<carl::Interval<Number>> minus=minusbox.intervals();

  std::vector<hypro::Box<Number>> test3;
  for (long unsigned int i = 0; i < minus.size(); i++){
    std::vector<carl::Interval<Number>> box2=box;//lower
    std::vector<carl::Interval<Number>> box3=box;//upper
    bool b=set_difference(box.at(i), minus.at(i), box2.at(i), box3.at(i));
    hypro::Box<Number> workbox(box2);
    if (!workbox.empty()){
      test3.push_back(workbox);
      carl::Interval<Number> tmp(box2.at(i).upperBound(),box.at(i).upperBound());
      box.at(i)=tmp;
    }
    hypro::Box<Number> workbox2(box3);
    if (!workbox2.empty()){
      test3.push_back(workbox2);
      carl::Interval<Number> tmp2(box.at(i).lowerBound(),box3.at(i).lowerBound());
      box.at(i)=tmp2;
    }   
  }
  for (long unsigned int i = 0; i < test3.size(); i++){
      std::cout << test3.at(i) << std::endl;
  }*/
    

  /*if ( testbox.dimension() != minusbox.dimension() ) {
	    //hypro::BoxT e= hypro::BoxT();
		//std::vector<hypro::BoxT<Number, Converter, Setting>> result;
		//result.push_back(e);
		std::cout << i << std::endl;
  }else{
    std::vector<hypro::Box<Number>> result;
    std::pair<hypro::Point<Number>, hypro::Point<Number>> originalpoints= testbox.limits();
    std::pair<hypro::Point<Number>, hypro::Point<Number>> minuspoints= minusbox.limits();
    for ( unsigned i = 0; i < testbox.dimension(); ++i ) {
      //lower
      std::pair<hypro::Point<Number>, hypro::Point<Number>> points= originalpoints;
      
      //points.first[i]=points.first[i] remains the same
      points.second[i]=minuspoints.first[i];
      hypro::Box<Number> tmp(points);
      if(tmp.limits().first[i]<tmp.limits().second[i]){
        result.push_back(tmp);
        originalpoints.first[i]=minuspoints.first[i];
      }
      //upper
      points= originalpoints;   
      //std::pair<Point<Number>, Point<Number>> minuspoints= minus.limits(); already known
      points.first[i]=minuspoints.second[i];
      //points.second[i]=points.second[i]; remains the same
      hypro::Box<Number> tmp2(points);
      if(tmp2.limits().first[i]<tmp2.limits().second[i]){//!(tmp2.empty())
        result.push_back(tmp2);
        originalpoints.second[i]=minuspoints.second[i];
      }
      //points= testbox.limits();
      //points.first[i]=minuspoints.first[i];
      //points.second[i]=minuspoints.second[i];
      //hypro::Box<Number> testbox(points);
    }
    std::vector<hypro::Point<Number>> tvertices = result.at(0).vertices();
    for (const auto &vertex : tvertices)
    std::cout << vertex << std::endl;
    for (long unsigned int i = 0; i < result.size(); i++){
      std::cout << result.at(i) << std::endl;
    }
  }*/
  return 0;
}