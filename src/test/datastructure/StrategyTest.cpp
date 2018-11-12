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

	EXPECT_EQ(strat.mStrategy.size(), 1);

	Strategy<State_t<double>> strat2;
	strat2.mStrategy = {StrategyNode<Box<double>>(mpq_class(1)), StrategyNode<SupportFunction<double>>(mpq_class(1)),
		StrategyNode<Zonotope<double>>(mpq_class(1))};

	EXPECT_EQ(strat2.mStrategy.size(), 3);
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

	boost::apply_visitor(detail::strategyConversionVisitor<double,State_t<double>>(s), strat.mStrategy[1]);

	EXPECT_NO_THROW(boost::get<SupportFunction<double>>(s.getSet()));
	EXPECT_ANY_THROW(boost::get<Box<double>>(s.getSet()));

	EXPECT_EQ(boost::get<SupportFunction<double>>(s.getSet()).type(), representation_name::support_function);
	EXPECT_EQ(s.getSetType(), representation_name::support_function);
}
