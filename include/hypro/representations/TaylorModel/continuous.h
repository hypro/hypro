/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * continuous.h
 *
 *  Created on: Dec 3, 2014
 *      Author: chen
 */

#pragma once

#include "ContinuousSetting.h"
#include "TaylorModel.h"

namespace hypro {

    template<typename Number>
    class Flowpipe {
    protected:
        TaylorModelVec<Number> tmvPre;
        TaylorModelVec<Number> tmv;
        Domain<Number> domain;

    public:
        Flowpipe();

        Flowpipe(const TaylorModelVec<Number> &tmv_input, const Domain<Number> &domain_input);

        Flowpipe(const Flowpipe<Number> &flowpipe);

        ~Flowpipe();

        void clear();

        void enclosure(Range<Number> &range);

        void enclosure(Range<Number> &range, const exponent order);

        void composition(TaylorModelVec<Number> &result, Domain<Number> &fp_domain, const exponent order);

        template<class Setting>
        int next_picard(Flowpipe<Number> &result, const PolynomialODE<Number> &ode, const carl::Variable &t,
                        const double stepsize, const exponent order, const Range<Number> &estimation);

        Flowpipe<Number> &operator=(const Flowpipe<Number> &flowpipe);

        void output(std::ostream &os, const exponent order);
    };

    template<typename Number>
    class ContinuousSystem {
    protected:
        PolynomialODE<Number> ode;
        Flowpipe<Number> initialSet;

    public:
        ContinuousSystem();

        ContinuousSystem(const PolynomialODE<Number> &ode_input, const Flowpipe<Number> &initialSet_input);

        ContinuousSystem(const ContinuousSystem<Number> &system);

        ~ContinuousSystem();

        int reach_picard(std::list <Flowpipe<Number>> &result, const carl::Variable &t, const double time,
                         const double stepsize,
                         const exponent order, const Range<Number> &estimation) const;

        ContinuousSystem<Number> &operator=(const ContinuousSystem<Number> &system);

        void output(std::ostream &os, const exponent order);
    };

    template<typename Number>
    void
    output_2D_interval_gnuplot(std::list <Flowpipe<Number>> &flowpipes, std::ofstream &os, const std::string &fileName,
                               const carl::Variable &axis_x, const carl::Variable &axis_y);

}  // namespace hypro

#include "continuous.tpp"
