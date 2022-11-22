#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>


template <typename Number>
class StarsetTest : public ::testing::Test {
  protected:
    
	virtual void SetUp() {
        // star set
    
		hypro::Halfspace<Number> hp1( { Number( 1 ), Number( 0 ) }, Number( 2 ) );
		hypro::Halfspace<Number> hp2( { Number( 0 ), Number( 1 ) }, Number( 2 ) );
		hypro::Halfspace<Number> hp3( { Number( -1 ), Number( 0 ) }, Number( 2 ) );
		hypro::Halfspace<Number> hp4( { Number( 0 ), -Number( 1 ) }, Number( 2 ) );

        planes1.push_back( hp1 );
		planes1.push_back( hp2 );
		planes1.push_back( hp3 );
		planes1.push_back( hp4 );

        hypro::vector_t<Number> center=hypro::vector_t<Number>(2);
        hypro::vector_t<Number> Limits=hypro::vector_t<Number>(4);
        hypro::matrix_t<Number> Generator=hypro::matrix_t<Number>(2,2);
        hypro::matrix_t<Number> ShapeMatrix=hypro::matrix_t<Number>(4,2);
        center<<10,1;
        Limits<<1,1,1,1;
        Generator<<1,2,0,1;
        ShapeMatrix<<1,0,-1,0,0,1,0,-1;
        myStar1= hypro::Starset<Number>(center,ShapeMatrix,Limits,Generator);

        hypro::vector_t<Number> center1=hypro::vector_t<Number>(2);
        hypro::vector_t<Number> Limits1=hypro::vector_t<Number>(4);
        hypro::matrix_t<Number> Generator1=hypro::matrix_t<Number>(2,2);
        hypro::matrix_t<Number> ShapeMatrix1=hypro::matrix_t<Number>(4,2);
        center1<<3,7;
        Limits1<<1,1,1,1;
        Generator1<<1,0,0,1;
        ShapeMatrix1<<1,0,-1,0,0,1,0,-1;
        myStar2= hypro::Starset<Number>(center1,ShapeMatrix1,Limits1,Generator1);
        myStar=hypro::Starset<Number>();

        // hypro::vector_t<Number> center2=hypro::vector_t<Number>(2);
        // hypro::vector_t<Number> Limits2=hypro::vector_t<Number>(5);
        // hypro::matrix_t<Number> Generator2=hypro::matrix_t<Number>(2,2);
        // hypro::matrix_t<Number> ShapeMatrix2=hypro::matrix_t<Number>(5,2);
        // center2<<-12.8727,-15.8922;
        // Limits2<<0.000246886,7.94631,7.94656,0,-12.8727;
        // ShapeMatrix2<<1,0,0,1,1,1,-1,0,-1,1.62;
        // Generator2<<1,0,1.62,1;

        // myStar1000=hypro::Starset<Number>(center2,ShapeMatrix2,Limits2,Generator2);
	}

	virtual void TearDown() {}
    std::vector<hypro::Halfspace<Number>> planes1;

    hypro::Starset<Number> myStar;
    hypro::Starset<Number> myStar2;
    hypro::Starset<Number> myStar1;
    // hypro::Starset<Number> myStar1000;


};


TYPED_TEST(StarsetTest, Constructor){
    EXPECT_NE(this->myStar.limits(),this->myStar2.limits() );
    hypro::matrix_t<TypeParam> transmat=hypro::matrix_t<TypeParam>(2,2);
    transmat<<cos(45),-sin(45),sin(45),cos(45);
    hypro::vector_t<TypeParam> offset=hypro::vector_t<TypeParam>(2);
    offset<<1,1;
    hypro::HPolytope<TypeParam> anotherHPolytope = hypro::HPolytope<TypeParam>(this->myStar1.constraintss().affineTransformation(this->myStar1.generator(),this->myStar1.center()) );
    hypro::HPolytope<TypeParam> anotherHPolytope2 = hypro::HPolytope<TypeParam>(anotherHPolytope.affineTransformation(transmat,offset)  );
    hypro::HPolytope<TypeParam> united = anotherHPolytope.unite(anotherHPolytope2);


    auto ikincidegismis=this->myStar1.affineTransformation(transmat,offset);
    auto sonucikinci=ikincidegismis.unite(this->myStar1);
    hypro::Plotter<TypeParam> &plotter = hypro::Plotter<TypeParam>::getInstance();

    plotter.setFilename("Unitewhat");
    plotter.addObject(anotherHPolytope.vertices());
    plotter.addObject(anotherHPolytope2.vertices());
    plotter.addObject(ikincidegismis.vertices());
    plotter.addObject(sonucikinci.vertices());
    plotter.addObject(united.vertices());


    // write output.
    plotter.plot2d();
    

}
/*
TYPED_TEST(StarsetTest, LinearandDimension){
    hypro::matrix_t<TypeParam> transmat=hypro::matrix_t<TypeParam>(2,2);
    transmat<<1,2,1,2;
    
    hypro::Starset<TypeParam> myStar3=this->myStar1.linearTransformation(transmat);
    
    hypro::matrix_t<TypeParam> transformedgen=hypro::matrix_t<TypeParam>(2,2);
    transformedgen<<1,2,1,2;
    EXPECT_EQ(myStar3.generator(),transformedgen);
    EXPECT_EQ(myStar3.dimension(),2);
}

TYPED_TEST(StarsetTest, Affine){

    hypro::matrix_t<TypeParam> transmat=hypro::matrix_t<TypeParam>(2,2);
    transmat<<cos(45*3.14159/180),-sin(45*3.14159/180),sin(45*3.14159/180),cos(45*3.14159/180);
    hypro::vector_t<TypeParam> offset=hypro::vector_t<TypeParam>(2);
    offset<<1,0;
    hypro::Plotter<TypeParam> &plotter = hypro::Plotter<TypeParam>::getInstance();
    hypro::Starset<TypeParam> myStar555=this->myStar2.affineTransformation(transmat,offset);

    plotter.setFilename("Starset_example2for_thesis");
    //for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    //for (auto &set : node.getFlowpipe()) {
     plotter.addObject(myStar555.vertices());
    //}
    //}
    // write output.
    plotter.plot2d();
    hypro::HPolytope<TypeParam> anotherHPolytope = hypro::HPolytope<TypeParam>( this->planes1 );

    hypro::Starset<TypeParam> myStar3=hypro::Starset<TypeParam>(anotherHPolytope);
    hypro::matrix_t<TypeParam> transformedgen=hypro::matrix_t<TypeParam>(2,2);
    transformedgen<<2,2,2,2;

    hypro::Starset<TypeParam> myStar55=myStar3.affineTransformation(transformedgen,offset);
    hypro::HPolytope<TypeParam> anotherHPolytope2=anotherHPolytope.affineTransformation(transformedgen,offset);

    //EXPECT_EQ(myStar3.generator(),transformedgen);
    //EXPECT_EQ(myStar3.center(),offset+transmat*this->myStar1.center());
}
TYPED_TEST(StarsetTest, HalfspaceIntersection_s){
    hypro::Halfspace<TypeParam> halff= hypro::Halfspace<TypeParam>({1,1},2);
    //hypro::Starset<TypeParam> myStar3=this->myStar1.intersectHalfspace(halff);
    hypro::Halfspace<TypeParam> halff1= hypro::Halfspace<TypeParam>({1,1},-2);
    hypro::Halfspace<TypeParam> halff2= hypro::Halfspace<TypeParam>({1,-1},2);
    hypro::Halfspace<TypeParam> halff3= hypro::Halfspace<TypeParam>({-1,1},2);
    

    hypro::matrix_t<TypeParam> transmat=hypro::matrix_t<TypeParam>(2,2);
    transmat<<1,2,1,2;
    hypro::vector_t<TypeParam> offset=hypro::vector_t<TypeParam>(2);
    offset<<1,1;

    hypro::HPolytope<TypeParam> anotherHPolytope = hypro::HPolytope<TypeParam>( this->planes1 );
    hypro::Starset<TypeParam> myStar3=hypro::Starset<TypeParam>(anotherHPolytope);
    
    hypro::matrix_t<TypeParam> transformedgen=hypro::matrix_t<TypeParam>(2,2);
    transformedgen<<2,2,2,2;

    myStar3=myStar3.affineTransformation(transformedgen,offset);
     anotherHPolytope=anotherHPolytope.affineTransformation(transformedgen,offset);
    

    hypro::Starset<TypeParam> myStar55=myStar3.intersectHalfspace(halff);
    hypro::HPolytope<TypeParam> anotherHPolytope2=anotherHPolytope.intersectHalfspace(halff);

    myStar55=myStar3.intersectHalfspace(halff1);
    anotherHPolytope2=anotherHPolytope.intersectHalfspace(halff1);

    myStar55=myStar3.intersectHalfspace(halff2);
    anotherHPolytope2=anotherHPolytope.intersectHalfspace(halff2);

    myStar55=myStar3.intersectHalfspace(halff3);
    anotherHPolytope2=anotherHPolytope.intersectHalfspace(halff3);
    //EXPECT_EQ(myStar3.shape(),shapecheck);
    //EXPECT_EQ(myStar3.limits(),limitcheck);
    
    //hypro::Starset<TypeParam> myStar5=this->myStar1.intersectHalfspaces(matt,vecc);
    //EXPECT_EQ(myStar4.shape(),myStar5.shape());
}
TYPED_TEST(StarsetTest, MinkowskiSum){
    hypro::Starset<TypeParam> myStar3=this->myStar1.minkowskiSum(this->myStar2);
}

TYPED_TEST(StarsetTest, Containspoint){
    hypro::Point<TypeParam> p1( { 3, 3 } );
    EXPECT_EQ(this->myStar1.contains(p1),true);
}

TYPED_TEST(StarsetTest, Vertices){
}

TYPED_TEST(StarsetTest, Empty){
    EXPECT_EQ(this->myStar1.empty(),false);
}


TYPED_TEST(StarsetTest, ContainsStar){

}


TYPED_TEST(StarsetTest, Union){
    hypro::Starset<TypeParam> myStar3=this->myStar1.unite(this->myStar2);

}
*/