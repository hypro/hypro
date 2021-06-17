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
    hypro::Starset<TypeParam> mystar= hypro::Starset<TypeParam>();
    hypro::vector_t<TypeParam> zero=hypro::vector_t<TypeParam>(0);
  
    EXPECT_EQ(mystar.limits(),zero );
    EXPECT_EQ(0,0);
    hypro::vector_t<TypeParam> center=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits=hypro::vector_t<TypeParam>(4);
    hypro::matrix_t<TypeParam> Generator=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix=hypro::matrix_t<TypeParam>(4,2);
    center<<3,3;
    Limits<<1,1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> mystar1= hypro::Starset<TypeParam>(center,ShapeMatrix,Limits,Generator);
    hypro::vector_t<TypeParam> center1=hypro::vector_t<TypeParam>(2);
    hypro::vector_t<TypeParam> Limits1=hypro::vector_t<TypeParam>(3);
    hypro::matrix_t<TypeParam> Generator1=hypro::matrix_t<TypeParam>(2,2);
    hypro::matrix_t<TypeParam> ShapeMatrix1=hypro::matrix_t<TypeParam>(4,2);
    center<<3,3;
    Limits<<1,1,1;
    Generator<<1,0,0,1;
    ShapeMatrix<<1,0,-1,0,0,1,0,-1;
    hypro::Starset<TypeParam> mystar2= hypro::Starset<TypeParam>(center1,ShapeMatrix1,Limits1,Generator1);
    EXPECT_NE(mystar.limits(),mystar2.limits() );
}