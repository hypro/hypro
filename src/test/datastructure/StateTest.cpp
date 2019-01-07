#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"
#include "../../hypro/representations/GeometricObject.h"
#include <thread>

using namespace hypro;

void run(State_t<double> st) {
	matrix_t<double> dir = matrix_t<double>::Zero(1,2);
	vector_t<double> consts = vector_t<double>::Zero(1);
	dir << 1,0;
	consts << 1;

	st.satisfiesHalfspaces(dir,consts);

	SupportFunction<double> tmp = boost::get<SupportFunction<double>>(st.getSet());
	tmp.cleanUp();
	st.setSet(tmp);
}

TEST(StateTest, Constructor)
{
    // Todo
}

TEST(StateTest, CleanUp)
{
	matrix_t<double> constraints;
	matrix_t<double> constants;
	constraints = matrix_t<double>::Zero(3,2);

	constraints(0,0) = double(2);
	constraints(0,1) = double(4);
	constraints(1,0) = double(1);
	constraints(1,1) = double(-2);
	constraints(2,0) = double(-4);
	constraints(2,1) = double(1);

	constants = matrix_t<double>(3,1);
	constants(0,0) = double(20);
	constants(1,0) = double(5);
	constants(2,0) = double(17);

	State_t<double> st;
	SupportFunction<double> psf1 = SupportFunction<double>(constraints, constants);

	st.setSet(psf1);

	std::thread* t = new std::thread(run, st);

	t->join();
}

TEST(StateTest, Conversion)
{
	Box<double> b;
	b.insert(carl::Interval<double>(1,2));

	State_t<double> s;
	s.setSet(b);

	s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<double>::repVariant, SupportFunction<double>>(), s.getSet()));
	s.setSetType(representation_name::support_function);

	EXPECT_NO_THROW(boost::get<SupportFunction<double>>(s.getSet()));
	EXPECT_ANY_THROW(boost::get<Box<double>>(s.getSet()));

	s.setSet(boost::apply_visitor(genericConversionVisitor<typename State_t<double>::repVariant, HPolytope<double>>(), s.getSet()));

	EXPECT_NO_THROW(boost::get<HPolytope<double>>(s.getSet()));
	EXPECT_ANY_THROW(boost::get<Box<double>>(s.getSet()));
	EXPECT_ANY_THROW(boost::get<SupportFunction<double>>(s.getSet()));
	EXPECT_EQ(representation_name::polytope_h, s.getSetType());
}
