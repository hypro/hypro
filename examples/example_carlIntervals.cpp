#include "hypro/representations/GeometricObject.h"
#include "hypro/datastructures/Halfspace.h"

int main(){

	typedef mpq_class Number;


	carl::Interval<Number> intv1 = new carl::Interval<Number>(0,1);
	carl::Interval<Number> intv2 = new carl::Interval<Number>(1,1);

	carl::Interval<Number> res1 = intv1 + intv2;
	

return 0;
}
