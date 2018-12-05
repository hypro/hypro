#include "gtest/gtest.h"
#include "../defines.h"
#include <algorithms/quantifierElimination/qe.h>

using namespace hypro;

using Pol = PolyT<mpq_class>;
using Constr = ConstraintT<mpq_class>;
using Form = FormulaT<mpq_class>;

TEST( FourierMotzkinEliminationTest, SingleVariable )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    Constr c1 = Constr(Pol(x) - Pol(y) + Pol(z), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(x) + Pol(y) + Pol(-5), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

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

    Constr c1 = Constr(Pol(x) - Pol(y), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(x) - Pol(y) + Pol(-5), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(Form(carl::FormulaType::TRUE), newFormula);
}

TEST( FourierMotzkinEliminationTest, Reminder )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    Constr c1 = Constr(Pol(x) - Pol(y), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(x) - Pol(y) + Pol(-5), carl::Relation::LEQ);
    Constr c3 = Constr(Pol(y) - Pol(z), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(Form(c3), newFormula);

}

TEST( FourierMotzkinEliminationTest, MultipleVariables )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    Constr c1 = Constr(Pol(x) - Pol(y) + Pol(z), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(y), carl::Relation::GEQ);
    Constr c3 = Constr(Pol(x) + Pol(y) + Pol(-5), carl::Relation::LEQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x,y}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;
}

TEST( FourierMotzkinEliminationTest, SingleVariableEquation )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    Constr c1 = Constr(Pol(x) + Pol(z), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(x) - Pol(y), carl::Relation::LEQ);
    Constr c3 = Constr(Pol(x) + Pol(y) + Pol(-5), carl::Relation::EQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(Form(carl::FormulaType::AND, FormulasT<mpq_class>{Form(Constr(Pol(5)-Pol(y)+Pol(z),carl::Relation::GEQ)), Form(Constr(Pol(5)-Pol(y)*Pol(2), carl::Relation::LEQ))}),newFormula);
}

TEST( FourierMotzkinEliminationTest, SingleVariableEquationInconsistent )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    Constr c1 = Constr(Pol(x) + Pol(z), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(x) - Pol(y), carl::Relation::LEQ);
    Constr c3 = Constr(Pol(x) + Pol(-5), carl::Relation::EQ);
    Constr c4 = Constr(Pol(x) + Pol(-3), carl::Relation::EQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);
    constraints.emplace_back(c4);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(Form(carl::FormulaType::FALSE),newFormula);
}

TEST( FourierMotzkinEliminationTest, SingleVariableEquationInconsistent2 )
{
    carl::Variable x = carl::freshRealVariable("x");
    carl::Variable y = carl::freshRealVariable("y");
    carl::Variable z = carl::freshRealVariable("z");

    Constr c1 = Constr(Pol(x) + Pol(z), carl::Relation::GEQ);
    Constr c2 = Constr(Pol(x) - Pol(y), carl::Relation::LEQ);
    Constr c3 = Constr(Pol(x) + Pol(y), carl::Relation::EQ);
    Constr c4 = Constr(Pol(x) + Pol(z), carl::Relation::EQ);

    FormulasT<mpq_class> constraints;
    constraints.emplace_back(c1);
    constraints.emplace_back(c2);
    constraints.emplace_back(c3);
    constraints.emplace_back(c4);

    Form inFormula = Form(carl::FormulaType::AND, constraints);

    std::cout << "Formula: " << inFormula << std::endl;

    QEQuery query;
    query.emplace_back(std::make_pair(QuantifierType::EXISTS,std::vector<carl::Variable>{x}));

    auto newFormula = eliminateQuantifiers(inFormula, query);

    std::cout << "New formula: " << newFormula << std::endl;

    EXPECT_EQ(Form(carl::FormulaType::AND, FormulasT<mpq_class>{Form(Constr(Pol(y)-Pol(z),carl::Relation::LEQ)), Form(Constr(-Pol(y), carl::Relation::LEQ)), Form(Constr(-Pol(z)-Pol(y), carl::Relation::LEQ))}),newFormula);
}