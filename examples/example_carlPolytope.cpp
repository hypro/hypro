/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/VariablePool.h>
#include <hypro/util/plotting/Plotter.h>

int main(int argc, char const *argv[]) {
    using Number = mpq_class;
    using Pol = hypro::PolyT<Number>;
    using Constr = hypro::ConstraintT<Number>;
    using Intv = carl::Interval<Number>;
    using Var = carl::Variable;

    auto &vpool = hypro::VariablePool::getInstance();
    auto &plotter = hypro::Plotter<Number>::getInstance();

    // original variables
    Var x = vpool.newCarlVariable("x");
    Var y = vpool.newCarlVariable("y");

    // initial constraints
    Intv i1 = Intv{1, 2};
    Intv i2 = Intv{1, 2};
    std::vector<Intv> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);
    // create initial set represented as a carlPolytope
    hypro::CarlPolytope<Number> c1{intervals};

    // plot initial set
    auto verts = c1.vertices();
    plotter.addObject(verts);

    // let time pass: substitute original variables by ^pre-versions, add
    // constraints for time being positive, the flow and the invariants.
    Var t = vpool.newCarlVariable("t");
    Var xp = vpool.newCarlVariable("xpre");
    Var yp = vpool.newCarlVariable("ypre");

    // substitute
    c1.substituteVariable(vpool.carlVarByIndex(0), xp);
    c1.substituteVariable(vpool.carlVarByIndex(1), yp);

    // add new constraints
    // t >= 0
    c1.addConstraint(Constr(Pol(t), carl::Relation::GEQ));
    // flow: x' = [2,3], y' = [1,2]
    // -x + xp + 2t <= 0, -x + xp +3t >= 0
    c1.addConstraint(Constr(-Pol(x) + Pol(xp) + Pol(2) * t, carl::Relation::LEQ));
    c1.addConstraint(Constr(-Pol(x) + Pol(xp) + Pol(3) * t, carl::Relation::GEQ));
    // -y + yp + t <= 0, -y + yp +2t >= 0
    c1.addConstraint(Constr(-Pol(y) + Pol(yp) + Pol(t), carl::Relation::LEQ));
    c1.addConstraint(Constr(-Pol(y) + Pol(yp) + Pol(2) * t, carl::Relation::GEQ));
    // invariants: x <= 10, y <= 10
    c1.addConstraint(Constr(Pol(x) - Pol(10), carl::Relation::LEQ));
    c1.addConstraint(Constr(Pol(y) - Pol(10), carl::Relation::LEQ));

    // eliminate ^pre-variables to obtain polytope after having let time pass
    std::cout << "Before elimination: " << c1 << std::endl;
    c1.eliminateVariable(xp);
    std::cout << "After elimination of xpre: " << c1 << std::endl;
    c1.eliminateVariable(yp);
    std::cout << "After elimination of ypre: " << c1 << std::endl;
    c1.eliminateVariable(t);
    std::cout << "After elimination of t: " << c1 << std::endl;

    // plot after time elapse
    verts = c1.vertices();
    plotter.addObject(verts);

    // write plot file
    plotter.plot2d();

    return 0;
}
