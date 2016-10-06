/**
 * @file    ConverterTest.cpp
 * @covers  Converter
 *
 * @author  Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Simon Froitzheim
 *
 * @since	2015-05-13
 * @version     2015-12-16
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/GeometricObject.h"
#include "../../lib/util/Plotter.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class ConverterTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {


                //box
                std::vector<carl::Interval<Number>> boundaries;
                boundaries.push_back(carl::Interval<Number>(2,6));
                boundaries.push_back(carl::Interval<Number>(1,3));
                box = hypro::Box<Number>(boundaries);

                // first support function
                matrix = matrix_t<Number>(3,2);
		distances = vector_t<Number>(3);
		matrix << 1,1,
                        -1,1,
                        0,-1;
		distances << 1,1,0;

                support = hypro::SupportFunction<Number>(this->matrix, this->distances);

                // second support function (box)
                matrix2 = matrix_t<Number>(4,2);
                distances2 = vector_t<Number>(4);
                matrix2 << 0, 1, 0, -1, 1, 0, -1, 0;
                distances2 << 2, 2, 1, 1;

                support2 = hypro::SupportFunction<Number>(this->matrix2, this->distances2);

                //first zonotope
		vector_t<Number> center = vector_t<Number>(2);
		center << 2, 2;
		matrix_t<Number> generators = matrix_t<Number>(2,2);
		generators << 0, 1, 1, -1;
		zonotope = hypro::Zonotope<Number>(center, generators);

                //second zonotope (box)
                vector_t<Number> center2 = vector_t<Number>(2);
                center2 << 1, 1;
                matrix_t<Number> generators2 = matrix_t<Number>(2,2);
                generators2 << 0, 1, 1, 0;
                zonotope2 = hypro::Zonotope<Number>(center2, generators2);

                //third zonotope (chapter 3 example)
                //vector_t<Number> center3 = vector_t<Number>(2);
                //center3 << 3, 3;
                //matrix_t<Number> generators3 = matrix_t<Number>(2,3);
                //generators3.col(0) << 0, 1;
                //generators3.col(1) << 1, 1;
                //generators3.col(2) << 2, -1;
                //zonotope3 = hypro::Zonotope<Number>(center3, generators3);

                //fourth zonotope (chapter 3 example)
                //vector_t<Number> center4 = vector_t<Number>(2);
                //center4 << 3, 3;
                //matrix_t<Number> generators4 = matrix_t<Number>(2,2);
                //generators3 << 0, 1, 1, 1;
                //zonotope4 = hypro::Zonotope<Number>(center4, generators4);

                //first v-polytope (box)
		vector_t<Number> p1 = vector_t<Number>(2);
		p1(0) = 1;
		p1(1) = 2;
		vector_t<Number> p2 = vector_t<Number>(2);
		p2(0) = 3;
		p2(1) = 2;
		vector_t<Number> p3 = vector_t<Number>(2);
		p3(0) = 3;
		p3(1) = 4;
		vector_t<Number> p4 = vector_t<Number>(2);
		p4(0) = 1;
		p4(1) = 4;
		typename hypro::VPolytope<Number>::pointVector points;
		points.push_back(Point<Number>(p1));
		points.push_back(Point<Number>(p2));
		points.push_back(Point<Number>(p3));
		points.push_back(Point<Number>(p4));
		vpolytope = hypro::VPolytope<Number>(points);

                //second v-polytope (slightly deformed box)
                vector_t<Number> p5 = vector_t<Number>(2);
                p5(0) = 0;
                p5(1) = 2;
                typename hypro::VPolytope<Number>::pointVector points2;
                points2.push_back(Point<Number>(p5));
                points2.push_back(Point<Number>(p2));
                points2.push_back(Point<Number>(p3));
                points2.push_back(Point<Number>(p4));
                vpolytope2 = hypro::VPolytope<Number>(points2);



                //third v-polytope(tilted stretched box)
                vector_t<Number> p6 = vector_t<Number>(2);
                p6(0)= 2;
                p6(1)= 1;
                vector_t<Number> p7 = vector_t<Number>(2);
                p7(0)= 1;
                p7(1)= 2;
                vector_t<Number> p8 = vector_t<Number>(2);
                p8(0)= 5;
                p8(1)= 4;
                vector_t<Number> p9 = vector_t<Number>(2);
                p9(0)= 4;
                p9(1)= 5;
                typename hypro::VPolytope<Number>::pointVector points3;
		points3.push_back(Point<Number>(p6));
		points3.push_back(Point<Number>(p7));
		points3.push_back(Point<Number>(p8));
		points3.push_back(Point<Number>(p9));
		vpolytope3 = hypro::VPolytope<Number>(points3);

                // A box (for H-Polytope)
		Halfspace<Number> hp1({1,0},2);
		Halfspace<Number> hp2({0,1},2);
		Halfspace<Number> hp3({-1,0},2);
		Halfspace<Number> hp4({0,-1},2);

                planes.push_back(hp1);
		planes.push_back(hp2);
		planes.push_back(hp3);
		planes.push_back(hp4);

                hpolytope = hypro::HPolytope<Number>(this->planes);

                //second H-Polytope
                Halfspace<Number> hp5({1,1},carl::rationalize<Number>(1.4));
                Halfspace<Number> hp6({0,-1},1);
                Halfspace<Number> hp7({-1,0},1);

                planes2.push_back(hp5);
                planes2.push_back(hp6);
                planes2.push_back(hp7);

                hpolytope2 = hypro::HPolytope<Number>(this->planes2);

    }

    virtual void TearDown()
    {
    }

    Plotter<Number>& plotter = Plotter<Number>::getInstance();

    matrix_t<Number> matrix;
    matrix_t<Number> matrix2;
    vector_t<Number> distances;
    vector_t<Number> distances2;
    hypro::SupportFunction<Number> support;
    hypro::SupportFunction<Number> support2;

    hypro::Box<Number> box;

    hypro::VPolytope<Number> vpolytope;
    hypro::VPolytope<Number> vpolytope2;
    hypro::VPolytope<Number> vpolytope3;

    hypro::Zonotope<Number> zonotope;
    hypro::Zonotope<Number> zonotope2;
    hypro::Zonotope<Number> zonotope3;
    hypro::Zonotope<Number> zonotope4;


    typename hypro::HPolytope<Number>::HalfspaceVector planes;
    typename hypro::HPolytope<Number>::HalfspaceVector planes2;
    hypro::HPolytope<Number> hpolytope;
    hypro::HPolytope<Number> hpolytope2;
};

TYPED_TEST(ConverterTest, toBox)
{

	Converter<TypeParam>::toBox(this->box);
        //std::cout << " Box: " << std::endl;
        //result.print();
	Converter<TypeParam>::toBox(this->support);
        //std::cout << " Support:" << std::endl;
        //result.print();
        Converter<TypeParam>::toBox(this->support2);
        //result.print();
	Converter<TypeParam>::toBox(this->vpolytope);
        //std::cout << " V:" << std::endl;
        //result.print();
        Converter<TypeParam>::toBox(this->vpolytope2);
        //result.print();
	Converter<TypeParam>::toBox(this->zonotope);
        //std::cout << " Zonotope:" << std::endl;
        //result.print();
        Converter<TypeParam>::toBox(this->zonotope2);
        //result.print();
        Converter<TypeParam>::toBox(this->hpolytope);
        //std::cout << " H:" << std::endl;
        //result.print();
        Converter<TypeParam>::toBox(this->hpolytope2);
        //result.print();
        auto result = Converter<TypeParam>::toBox(this->hpolytope, ALTERNATIVE);
        //this->plotter.setObjectColor(this->plotter.addObject(result.vertices()), colors[orange]);

        auto result2 = Converter<TypeParam>::toBox(this->hpolytope2, ALTERNATIVE);
        //this->plotter.setObjectColor(this->plotter.addObject(result2.vertices()), colors[green]);

        auto result3 = Converter<TypeParam>::toBox(this->hpolytope);
        //this->plotter.setObjectColor(this->plotter.addObject(result3.vertices()), colors[orange]);

        auto result4 = Converter<TypeParam>::toBox(this->hpolytope2);
        //this->plotter.setObjectColor(this->plotter.addObject(result4.vertices()), colors[green]);

        SUCCEED();
}

TYPED_TEST(ConverterTest, toHPolytope)
{
        auto result =  Converter<TypeParam>::toHPolytope(this->hpolytope);

        auto result2 = Converter<TypeParam>::toHPolytope(this->support);
        //this->plotter.setObjectColor(this->plotter.addObject(result2.vertices()), colors[orange]);

        auto result3 = Converter<TypeParam>::toHPolytope(this->support2);
        //this->plotter.setObjectColor(this->plotter.addObject(result3.vertices()), colors[green]);

        auto result4 = Converter<TypeParam>::toHPolytope(this->zonotope);
        //this->plotter.setObjectColor(this->plotter.addObject(result4.vertices()), colors[petrol]);

        auto result5 = Converter<TypeParam>::toHPolytope(this->zonotope2);
        //this->plotter.setObjectColor(this->plotter.addObject(result5.vertices()), colors[turquoise]);

        auto result6 = Converter<TypeParam>::toHPolytope(this->vpolytope, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result6.vertices()), colors[maygreen]);

        auto result7 = Converter<TypeParam>::toHPolytope(this->vpolytope2, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result7.vertices()), colors[red]);

        auto result8 = Converter<TypeParam>::toHPolytope(this->vpolytope3, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result8.vertices()), colors[bordeaux]);

        auto result9 = Converter<TypeParam>::toHPolytope(this->box);
        //this->plotter.setObjectColor(this->plotter.addObject(result9.vertices()), colors[violett]);


	SUCCEED();
}

TYPED_TEST(ConverterTest, toSupportFunction)
{
        Converter<TypeParam>::toSupportFunction(this->support);
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->hpolytope);
        //std::cout << " HPolytope: " << std::endl;
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->hpolytope2);
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->box);
        //std::cout << " Box: " << std::endl;
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->vpolytope);
        //std::cout << " VPolytope: " << std::endl;
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->vpolytope2);
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->zonotope);
        //std::cout << " Zonotope: " << std::endl;
        //result.print();
        Converter<TypeParam>::toSupportFunction(this->zonotope2);
        //result.print();
	SUCCEED();
}

TYPED_TEST(ConverterTest, toVPolytope)
{
        auto result =  Converter<TypeParam>::toVPolytope(this->vpolytope);

        auto result2 = Converter<TypeParam>::toVPolytope(this->support, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result2.vertices()), colors[orange]);

        auto result3 = Converter<TypeParam>::toVPolytope(this->support2, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result3.vertices()), colors[green]);

        auto result4 = Converter<TypeParam>::toVPolytope(this->zonotope);
        //this->plotter.setObjectColor(this->plotter.addObject(result4.vertices()), colors[petrol]);

        auto result5 = Converter<TypeParam>::toVPolytope(this->zonotope2);
        //this->plotter.setObjectColor(this->plotter.addObject(result5.vertices()), colors[turquoise]);

        auto result6 = Converter<TypeParam>::toVPolytope(this->hpolytope, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result6.vertices()), colors[maygreen]);

        auto result7 = Converter<TypeParam>::toVPolytope(this->hpolytope2, OVER);
        //this->plotter.setObjectColor(this->plotter.addObject(result7.vertices()), colors[red]);
        //this->plotter.addPoints(Converter<TypeParam>::toVPolytope(this->hpolytope2).vertices());

        auto result8 = Converter<TypeParam>::toVPolytope(this->box);
        //this->plotter.setObjectColor(this->plotter.addObject(result8.vertices()), colors[violett]);

        //auto result9 = Converter<TypeParam>::toVPolytope(this->support, ALTERNATIVE, 4);
        //this->plotter.setObjectColor(this->plotter.addObject(result9.vertices()), colors[red]);

        //auto result10 = Converter<TypeParam>::toVPolytope(this->support2, ALTERNATIVE, 4);
        //this->plotter.setObjectColor(this->plotter.addObject(result10.vertices()), colors[lila]);
	SUCCEED();
}

TYPED_TEST(ConverterTest, toZonotope)
{

        auto result = Converter<TypeParam>::toZonotope(this->zonotope);
        //result.print();
        auto result2 = Converter<TypeParam>::toZonotope(this->box);
        //std::cout << " Box: " << std::endl;
        //result2.print();
        auto result3 = Converter<TypeParam>::toZonotope(this->vpolytope);
        //std::cout << "V: " << std::endl;
        //result3.print();
        auto result4 = Converter<TypeParam>::toZonotope(this->vpolytope2);
        //auto vpoly = VPolytope<TypeParam>(result4.vertices());
        //this->plotter.addObject(vpoly.vertices());
        //this->plotter.addPoints(this->vpolytope2.vertices());

        auto result5 = Converter<TypeParam>::toZonotope(this->vpolytope3);
        //auto vpoly2 = VPolytope<TypeParam>(result5.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly2.vertices()), colors[green]);
        //this->plotter.setObjectColor(this->plotter.addObject(this->vpolytope3.vertices()), colors[orange]);


        auto result6 = Converter<TypeParam>::toZonotope(this->hpolytope);
        //auto vpoly3 = VPolytope<TypeParam>(result6.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly3.vertices()), colors[turquoise]);
        //std::cout << "H: " << std::endl;

        auto result7 = Converter<TypeParam>::toZonotope(this->hpolytope2);
        //auto vpoly4 = VPolytope<TypeParam>(result7.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly4.vertices()), colors[maygreen]);
        //this->plotter.addPoints(Converter<TypeParam>::toVPolytope(this->hpolytope2).vertices());


        //TODO result is slightly tilted (maybe try with different number of directions)
        auto result8 = Converter<TypeParam>::toZonotope(this->support, ALTERNATIVE);
        //auto vpoly5 = VPolytope<TypeParam>(result8.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly5.vertices()), colors[petrol]);

        auto result9 = Converter<TypeParam>::toZonotope(this->support2, ALTERNATIVE);
        //auto vpoly6 = VPolytope<TypeParam>(result9.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly6.vertices()), colors[bordeaux]);
        //auto vpoly7 = VPolytope<TypeParam>(this->zonotope3.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly7.vertices()), colors[petrol]);

        //auto vpoly8 = VPolytope<TypeParam>(this->zonotope4.vertices());
        //this->plotter.setObjectColor(this->plotter.addObject(vpoly8.vertices()), colors[petrol]);

        this->plotter.plot2d();
	SUCCEED();
}
