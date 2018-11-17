#include "gtest/gtest.h"
#include "../defines.h"
#include <algorithms/quantifierElimination/qe.h>

using namespace hypro;

TEST( FourierMotzkinEliminationTest, SingleVariable )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    ConstraintT<mpq_class> c1 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) - PolyT<mpq_class>(y) + PolyT<mpq_class>(z), carl::Relation::GEQ);
    ConstraintT<mpq_class> c2 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) + PolyT<mpq_class>(y) + PolyT<mpq_class>(-5), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);

    FormulaT<mpq_class> inFormula = FormulaT<mpq_class>(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

}

TEST( FourierMotzkinEliminationTest, NoReminder )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");

    ConstraintT<mpq_class> c1 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) - PolyT<mpq_class>(y), carl::Relation::GEQ);
    ConstraintT<mpq_class> c2 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) - PolyT<mpq_class>(y) + PolyT<mpq_class>(-5), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);

    FormulaT<mpq_class> inFormula = FormulaT<mpq_class>(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(FormulaT<mpq_class>(carl::FormulaType::TRUE), newFormula);
}

TEST( FourierMotzkinEliminationTest, Reminder )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    ConstraintT<mpq_class> c1 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) - PolyT<mpq_class>(y), carl::Relation::GEQ);
    ConstraintT<mpq_class> c2 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) - PolyT<mpq_class>(y) + PolyT<mpq_class>(-5), carl::Relation::LEQ);
    ConstraintT<mpq_class> c3 = ConstraintT<mpq_class>(PolyT<mpq_class>(y) - PolyT<mpq_class>(z), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);

    FormulaT<mpq_class> inFormula = FormulaT<mpq_class>(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(FormulaT<mpq_class>(c3), newFormula);

}

TEST( FourierMotzkinEliminationTest, MultipleVariables )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    ConstraintT<mpq_class> c1 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) - PolyT<mpq_class>(y) + PolyT<mpq_class>(z), carl::Relation::GEQ);
    ConstraintT<mpq_class> c2 = ConstraintT<mpq_class>(PolyT<mpq_class>(y), carl::Relation::GEQ);
    ConstraintT<mpq_class> c3 = ConstraintT<mpq_class>(PolyT<mpq_class>(x) + PolyT<mpq_class>(y) + PolyT<mpq_class>(-5), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);

    FormulaT<mpq_class> inFormula = FormulaT<mpq_class>(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x,y}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;
}