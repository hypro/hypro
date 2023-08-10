/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Specialization for a conversion to a Difference Bounds representation.
 * @file converterToDifferenceBounds.tpp
 * @author Justin Winkens
 *
 * @since	2017-11-08
 * @version	2017-11-08
 */

#include "Converter.h"

#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

// conversion from DifferenceBounds to DifferenceBounds (no differentiation between conversion modes - always EXACT)
    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const DifferenceBoundsT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        return source;
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const BoxT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const CarlPolytopeT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const ConstraintSetT<Number, inSetting> &source, const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DBSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const Ellipsoid &source, const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const HPolytopeT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        size_t numclocks = source.dimension();
        // 1. introduce a zero clock (numclocks+1)
        numclocks++;
        hypro::matrix_t<typename DifferenceBoundsT<Number, Converter<Number>, DBSetting>::DBMEntry> dbm = hypro::matrix_t<typename DifferenceBoundsT<Number, Converter<Number>, DBSetting>::DBMEntry>(
                numclocks, numclocks);

        //  for each pair of variables i,j
        for (size_t i = 0; i < numclocks; i++) {
            for (size_t j = 0; j < numclocks; j++) {
                //      if i!=j (do not consider diagonal entries)
                if (i != j) {
                    vector_t<Number> direction = vector_t<Number>::Zero(numclocks - 1);
                    //          if (i=0) (query direction vector (0,...,0,-1,0,...,0) -1 at jth position)
                    if (i == 0) {
                        direction(j - 1) = -1.0;
                    }
                        //          elif (j=0) (query direction vector (0,...,0,+1,0,...,0) +1 at ith position)
                    else if (j == 0) {
                        direction(i - 1) = 1.0;
                    }
                        //          else (query direction vector (0,0,...,0,+1,0,..,0,-1,0,...0) +1 at ith position, -1 at jth position)
                    else {
                        direction(i - 1) = 1.0;
                        direction(j - 1) = -1.0;
                    }
                    EvaluationResult<Number> res = source.evaluate(direction);
                    if (res.errorCode == hypro::SOLUTION::INFTY) {
                        dbm(i, j) = typename DifferenceBoundsT<Number, Converter<Number>, DBSetting>::DBMEntry(0.0,
                                                                                                               DifferenceBounds::BOUND_TYPE::INFTY);
                    } else {
                        dbm(i, j) = typename DifferenceBoundsT<Number, Converter<Number>, DBSetting>::DBMEntry(
                                res.supportValue, DifferenceBounds::BOUND_TYPE::SMALLER_EQ);
                    }
                } else {
                    dbm(i, j) = typename DifferenceBoundsT<Number, Converter<Number>, DBSetting>::DBMEntry(0.0,
                                                                                                           DifferenceBounds::BOUND_TYPE::SMALLER_EQ);
                }
            }
        }
        DifferenceBoundsT<Number, Converter, DBSetting> result{};
        result.setDBM(dbm);
        return result;
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const VPolytopeT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

#ifdef HYPRO_USE_PPL
    template <typename Number>
    template <typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting> Converter<Number>::toDifferenceBounds( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE ) {
        // TODO IMPLEMENT.
        return toDifferenceBounds( toHPolytope( source ) );
    }
#endif

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const SupportFunctionT<Number, Converter<Number>, inSetting> &_source,
                                          const std::vector<vector_t<Number>> &, const CONV_MODE, std::size_t) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(_source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const ZonotopeT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DBSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DBSetting>
    Converter<Number>::toDifferenceBounds(const SupportFunctionNewT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        // TODO make better, this is just the cheap solution
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

    template<typename Number>
    template<typename DifferenceBoundsSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>
    Converter<Number>::toDifferenceBounds(const TemplatePolyhedronT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        HPolytope tmp = toHPolytope(source);
        return toDifferenceBounds(tmp);
    }

// template<typename Number>
// template<typename DifferenceBoundsSetting, typename inSetting>
// DifferenceBoundsT<Number,Converter<Number>,DifferenceBoundsSetting> Converter<Number>::toDifferenceBounds( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return DifferenceBoundsT<Number,Converter<Number>,DifferenceBoundsSetting>();
// }

    // namespace hypro

    template<typename Number>
    template<typename DifferenceBoundsSetting, typename inSetting>
    DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>
    Converter<Number>::toDifferenceBounds(const StarsetT<Number, Converter<Number>, inSetting> &source,
                                          const CONV_MODE) {
        return DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>();
    }

}
