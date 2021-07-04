#include "../../hypro/datastructures/Point.h"
#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"


template <typename Number>
class StarsetTest : public ::testing::Test {
  protected:
    
	virtual void SetUp() {
        // star set
        
    hypro::vector_t<Number> center=hypro::vector_t<Number>(2);
    hypro::vector_t<Number> Limits=hypro::vector_t<Number>(4);
    hypro::matrix_t<Number> Generator=hypro::matrix_t<Number>(2,2);
    hypro::matrix_t<Number> ShapeMatrix=hypro::matrix_t<Number>(4,2);
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    myStar1= hypro::Starset<Number>(center,ShapeMatrix,Limits,Generator);

    hypro::vector_t<Number> center1=hypro::vector_t<Number>(2);
    hypro::vector_t<Number> Limits1=hypro::vector_t<Number>(4);
    hypro::matrix_t<Number> Generator1=hypro::matrix_t<Number>(2,2);
    hypro::matrix_t<Number> ShapeMatrix1=hypro::matrix_t<Number>(4,2);
    center1<<4,4;
    Limits1<<2,1,2,1;
    Generator1<<1,1,0,1;
    ShapeMatrix1<<2,0,0-1,0,0,1,0,-1;
    myStar2= hypro::Starset<Number>(center1,ShapeMatrix1,Limits1,Generator1);
    myStar=hypro::Starset<Number>();
	}

	virtual void TearDown() {}

    hypro::Starset<Number> myStar;
    hypro::Starset<Number> myStar2;
    hypro::Starset<Number> myStar1;

};


TYPED_TEST(StarsetTest, Constructor){
    EXPECT_NE(this->myStar.limits(),this->myStar2.limits() );
}

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
    transmat<<1,2,1,2;
    hypro::vector_t<TypeParam> offset=hypro::vector_t<TypeParam>(2);
    offset<<1,1;
    hypro::Starset<TypeParam> myStar3=this->myStar1.affineTransformation(transmat, offset);
    hypro::matrix_t<TypeParam> transformedgen=hypro::matrix_t<TypeParam>(2,2);
    transformedgen<<1,2,1,2;
    EXPECT_EQ(myStar3.generator(),transformedgen);
    EXPECT_EQ(myStar3.center(),offset+transmat*this->myStar1.center());
}
TYPED_TEST(StarsetTest, HalfspaceIntersection_s){
    hypro::Halfspace<TypeParam> halff= hypro::Halfspace<TypeParam>({1,1},3);
    hypro::Starset<TypeParam> myStar3=this->myStar1.intersectHalfspace(halff);
    hypro::matrix_t<TypeParam> shapecheck=hypro::matrix_t<TypeParam>(5,2);
    hypro::vector_t<TypeParam> limitcheck=hypro::matrix_t<TypeParam>(5,2);
    shapecheck<<1,0,-1,0,0,1,0,-1,1,1;
    limitcheck<<1,1,1,1,-3;
    EXPECT_EQ(myStar3.shape(),shapecheck);
    EXPECT_EQ(myStar3.limits(),limitcheck);
    hypro::Starset<TypeParam> myStar4=myStar3.intersectHalfspace(halff);
    hypro::matrix_t<TypeParam> matt=hypro::matrix_t<TypeParam>(2,2);
    matt<<1,1,1,1;
    hypro::vector_t<TypeParam> vecc=hypro::vector_t<TypeParam>(4);
    vecc<<3,3;
    hypro::Starset<TypeParam> myStar5=this->myStar1.intersectHalfspaces(matt,vecc);
    EXPECT_EQ(myStar4.shape(),myStar5.shape());
}
TYPED_TEST(StarsetTest, MinkowskiSum){
    hypro::Starset<TypeParam> myStar3=this->myStar1.minkowskiSum(this->myStar2);
   
}

TYPED_TEST(StarsetTest, Containspoint){
    hypro::Point<TypeParam> p1( { 3, 3 } );
    EXPECT_EQ(this->myStar1.contains(p1),true);
}