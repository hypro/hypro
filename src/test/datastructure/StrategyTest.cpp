#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/representations/GeometricObject.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"
#include "../../hypro/datastructures/reachability/Strategy.h"


using namespace hypro;


TEST(StrategyTest, Constructor)
{
    Strategy<State_t<double>> strat;

	strat.mStrategy.emplace_back(StrategyNode<Box<double>>{mpq_class(1)});
}

TEST(StrategyTest, Conversion)
{
    Strategy<State_t<double>> strat;

	strat.mStrategy.emplace_back(StrategyNode<Box<double>>{mpq_class(1)});
	strat.mStrategy.emplace_back(StrategyNode<SupportFunction<double>>{mpq_class(1)});

	Box<double> b;
	b.insert(carl::Interval<double>(1,2));

	State_t<double> s;
	s.setSet(b);

	auto tmp = strat.mStrategy[1];

	s.setSetDirect(boost::get<SupportFunction<double>(boost::apply_visitor(genericConversionVisitor<typename State_t<double>::repVariant, double, tmp::representationType>(representation_name::support_function), s.getSet())));
}
