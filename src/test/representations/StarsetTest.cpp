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
TYPED_TEST(StarsetTest, HalfspaceIntersection_s){
    hypro::Halfspace<TypeParam> halff= hypro::Halfspace<TypeParam>({1,1},3);    
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
    hypro::Starset<TypeParam> myStar2=myStar1.intersectHalfspace(halff);
    hypro::matrix_t<TypeParam> shapecheck=hypro::matrix_t<TypeParam>(5,2);
    hypro::vector_t<TypeParam> limitcheck=hypro::matrix_t<TypeParam>(5,2);
    shapecheck<<1,0,-1,0,0,1,0,-1,1,1;
    limitcheck<<1,1,1,1,-3;
    EXPECT_EQ(myStar2.shape(),shapecheck);
    EXPECT_EQ(myStar2.limits(),limitcheck);
    hypro::Starset<TypeParam> myStar3=myStar2.intersectHalfspace(halff);
    hypro::matrix_t<TypeParam> matt=hypro::matrix_t<TypeParam>(2,2);
    matt<<1,1,1,1;
    hypro::vector_t<TypeParam> vecc=hypro::vector_t<TypeParam>(4);
    vecc<<3,3;
    hypro::Starset<TypeParam> myStar4=myStar1.intersectHalfspaces(matt,vecc);
    EXPECT_EQ(myStar3.shape(),myStar4.shape());
}
TYPED_TEST(StarsetTest, MinkowskiSum){
    hypro::vector_t<TypeParam> center=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> Generator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> myStar1= hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    
    hypro::vector_t<TypeParam> ncenter=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> nLimits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> nGenerator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> nShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    ncenter<<2,2;
    nLimits<<1,1,1,1;
    nGenerator<<1,1,0,-1;
    nShapeMatrix<<1,1,-1,1,1,1,1,-1;
    hypro::Starset<TypeParam> myStar2= hypro::Starset<TypeParam>(ncenter,nShapeMatrix,nLimits,nGenerator);
    
    hypro::Starset<TypeParam> myStar3=myStar1.minkowskiSum(myStar2);
    std::cout<<"Generator" <<myStar3.generator()<<std::endl;

    std::cout<<"center" <<myStar3.center()<<std::endl;

    std::cout<<"limits" <<myStar3.limits()<<std::endl;

    std::cout<<"Shape" <<myStar3.shape()<<std::endl;
    //EXPECT_EQ(myStar2.shape(),shapecheck);
    //EXPECT_EQ(myStar2.limits(),limitcheck);
}