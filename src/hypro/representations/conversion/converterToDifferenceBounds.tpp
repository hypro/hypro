/**
 * Specialization for a conversion to a Difference Bounds representation.
 * @file converterToDifferenceBounds.tpp
 * @author Justin Winkens
 *
 * @since	2017-11-08
 * @version	2017-11-08
 */

#include "Converter.h"
#include "../../util/templateDirections.h"

//conversion from DifferenceBounds to DifferenceBounds (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const DifferenceBounds& source, const CONV_MODE ){
    return source;
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Box& source, const CONV_MODE ){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const ConstraintSet& source, const CONV_MODE ){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Ellipsoid& source, const CONV_MODE ){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const HPolytope& source, const CONV_MODE ){
    size_t numclocks = source.dimension();
    // 1. introduce a zero clock (numclocks+1)
    numclocks++;
    hypro::matrix_t<typename Converter<Number>::DifferenceBounds::DBMEntry> dbm = hypro::matrix_t<typename Converter<Number>::DifferenceBounds::DBMEntry>(numclocks, numclocks);

    //  for each pair of variables i,j
    for(size_t i = 0; i < numclocks; i++) {
        for(size_t j=0; j < numclocks; j++) {
            //      if i!=j (do not consider diagonal entries)
            if(i!=j) {
                vector_t<Number> direction = vector_t<Number>::Zero(numclocks-1);
                //          if (i=0) (query direction vector (0,...,0,-1,0,...,0) -1 at jth position)
                if(i == 0){
                    direction(j-1)=-1.0;
                }
                //          elif (j=0) (query direction vector (0,...,0,+1,0,...,0) +1 at ith position)
                else if(j==0){
                    direction(i-1)=1.0;
                }
                //          else (query direction vector (0,0,...,0,+1,0,..,0,-1,0,...0) +1 at ith position, -1 at jth position)
                else {
                    direction(i-1)=1.0;
                    direction(j-1)=-1.0;
                }
                EvaluationResult<Number> res = source.evaluate(direction);
                if(res.errorCode == hypro::SOLUTION::INFTY){
                    dbm(i, j) = typename Converter<Number>::DifferenceBounds::DBMEntry(0.0, DifferenceBounds::BOUND_TYPE::INFTY);
                }
                else {
                    dbm(i, j) = typename Converter<Number>::DifferenceBounds::DBMEntry(res.supportValue, DifferenceBounds::BOUND_TYPE::SMALLER_EQ);
                }
            }
            else{
                dbm(i,j)=typename Converter<Number>::DifferenceBounds::DBMEntry(0.0, DifferenceBounds::BOUND_TYPE::SMALLER_EQ);
            }
        }
    }
    DifferenceBounds result = DifferenceBounds();
    result.setDBM(dbm);
    return result;
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const VPolytope& source, const CONV_MODE ){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

#ifdef HYPRO_USE_PPL
template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Polytope& source, const CONV_MODE ){
    // TODO IMPLEMENT.
}
#endif

template<typename Number>
template<typename sfSetting>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const SupportFunctionT<Number,Converter,sfSetting>& _source, const std::vector<vector_t<Number>>& , const CONV_MODE, std::size_t ){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(_source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Zonotope& source, const CONV_MODE ){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}
