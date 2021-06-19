#include "../../hypro/datastructures/Point.h"
#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"


template <typename Number>
class StarsetTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
        
        }
};
TYPED_TEST(StarsetTest, Constructor){
    hypro::Starset<TypeParam> myStar= hypro::Starset<TypeParam>();
    hypro::vector_t<TypeParam> zero=hypro::vector_t<TypeParam>(0);
  
    EXPECT_EQ(myStar.limits(),zero );
    EXPECT_EQ(0,0);
    hypro::vector_t<TypeParam> center=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> Generator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> myStar1= hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    hypro::vector_t<TypeParam> center1=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits1=hypro::vector_t<TypeParam>(3);
    hypro::matrix_t<TypeParam> Generator1=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix1=hypro::matrix_t<TypeParam>(4,2);
    center<<3,3;
    Limits<<1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> myStar2= hypro::Starset<TypeParam>(center1,ShapeMatrix1,Limits1,Generator1);
    EXPECT_NE(myStar.limits(),myStar2.limits() );
}

TYPED_TEST(StarsetTest, LinearandDimension){
    hypro::vector_t<TypeParam> center=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> Generator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    // hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> myStar1= hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    hypro::matrix_t<TypeParam> transmat=hypro::matrix_t<TypeParam>(2,2);
    transmat<<1,2,1,2;
    
    hypro::Starset<TypeParam> myStar2=myStar1.linearTransformation(transmat);
    
    hypro::matrix_t<TypeParam> transformedgen=hypro::matrix_t<TypeParam>(2,2);
    transformedgen<<1,2,1,2;
    EXPECT_EQ(myStar2.generator(),transformedgen);
    EXPECT_EQ(myStar2.dimension(),2);
}

TYPED_TEST(StarsetTest, Affine){
    hypro::vector_t<TypeParam> center=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> Generator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    // hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> myStar1= hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    hypro::matrix_t<TypeParam> transmat=hypro::matrix_t<TypeParam>(2,2);
    transmat<<1,2,1,2;
    hypro::vector_t<TypeParam> offset=hypro::vector_t<TypeParam>(2);
    offset<<1,1;
    hypro::Starset<TypeParam> myStar2=myStar1.affineTransformation(transmat, offset);
    hypro::matrix_t<TypeParam> transformedgen=hypro::matrix_t<TypeParam>(2,2);
    transformedgen<<1,2,1,2;
    EXPECT_EQ(myStar2.generator(),transformedgen);
    EXPECT_EQ(myStar2.center(),offset+center);
}
TYPED_TEST(StarsetTest, HalfspaceIntersection){
    hypro::Halfspace<TypeParam> halff= hypro::Halfspace<TypeParam>({1,1},3);     hypro::vector_t<TypeParam> center=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> Generator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    // hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> myStar1= hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    hypro::Starset<TypeParam> myStar2=myStar1.intersectHalfspace(halff);
    hypro::matrix_t<TypeParam> shapecheck=hypro::matrix_t<TypeParam>(5,2);
    hypro::vector_t<TypeParam> limitcheck=hypro::matrix_t<TypeParam>(5,2);
    shapecheck<<1,0,-1,0,0,1,0,-1,1,1;
    limitcheck<<1,1,1,1,-3;
    EXPECT_EQ(myStar2.shape(),shapecheck);
    EXPECT_EQ(myStar2.limits(),limitcheck);
}