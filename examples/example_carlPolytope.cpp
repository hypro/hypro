#include <representations/GeometricObject.h>
#include <util/plotting/Plotter.h>
#include <carl/interval/Interval.h>

int main(int argc, char const *argv[])
{
    using Number = mpq_class;
    using Intv = carl::Interval<Number>;
    using cPoly = hypro::CarlPolytope<Number>;

    auto& plotter = hypro::Plotter<Number>::getInstance();
    plotter.setFilename("carlPolyExample");

    Intv i1 = Intv{1,2};
    Intv i2 = Intv{1,2};
    std::vector<Intv> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);

    cPoly c1{intervals};

    auto verts = c1.vertices();

    plotter.addObject(verts);

    plotter.plot2d();

    return 0;
}


