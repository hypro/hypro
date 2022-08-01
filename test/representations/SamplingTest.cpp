
#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/representations/sampling/sampling.h>

template <typename Number>
class SamplingTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
        using I = carl::Interval<Number>;
        box = hypro::Box<Number>(std::vector<I>{I(-3, 2), I(1, 6)});

		hypro::Halfspace<Number> hspace1{{-1, 0}, 2};
        hypro::Halfspace<Number> hspace2{{+1, 0}, 1};
        hypro::Halfspace<Number> hspace3{{0, -1}, 1};
        hypro::Halfspace<Number> hspace4{{0, +1}, 1};
        hPolytope = hypro::HPolytope<Number>({hspace1, hspace2, hspace3, hspace4});

        hypro::vector_t<Number> center = hypro::vector_t<Number>(2);
        center << 0, 0;
        hypro::matrix_t<Number> basis = hypro::matrix_t<Number>(2, 2);
        basis << -2, 0, 0, 1;

        zonotope = hypro::Zonotope<Number>(center, basis);

        starset = hypro::StarsetT<Number, hypro::Converter<Number>, hypro::StarsetEqvPolytopeCaching>(center, basis, hPolytope);
	}

	virtual void TearDown() {}

    hypro::Box<Number> box;
    hypro::HPolytope<Number> hPolytope;
    hypro::Zonotope<Number> zonotope;
    hypro::StarsetT<Number, hypro::Converter<Number>, hypro::StarsetEqvPolytopeCaching> starset;

    const std::size_t num_samples = 1000;
};

TYPED_TEST( SamplingTest, BoxUniform ) {
    std::set<hypro::Point<TypeParam>> samples = uniform_sampling(this->box, this->num_samples);

    for(auto& sample : samples) {
        EXPECT_TRUE(this->box.contains(sample));
    }
}

TYPED_TEST( SamplingTest, HPolytopeUniform ) {
    // std::cout << "The H-Polytope: ";
    // std::cout << this->hPolytope << std::endl;

    std::set<hypro::Point<TypeParam>> samples = uniform_sampling(this->hPolytope, this->num_samples);
    // std::cout << "Samples: ";
    // std::cout << samples << std::endl;

    for(auto& sample : samples) {
        EXPECT_TRUE(this->hPolytope.contains(sample));
    }
}

TYPED_TEST( SamplingTest, ZonotopeUniform ) {
    std::set<hypro::Point<TypeParam>> samples = hypro::uniform_sampling(this->zonotope, this->num_samples);

    for(auto& sample : samples) {
        EXPECT_TRUE(this->zonotope.contains(sample));
    }
}
	
TYPED_TEST( SamplingTest, StarsetUniform ) {
    std::set<hypro::Point<TypeParam>> samples = hypro::uniform_sampling(this->starset, this->num_samples);

    for(auto& sample : samples) {
        EXPECT_TRUE(this->starset.contains(sample));
    }
}

TYPED_TEST( SamplingTest, StarsetUniformCached ) {
    std::set<hypro::Point<TypeParam>> samples = hypro::uniform_sampling(this->starset, this->num_samples);

    for(auto& sample : samples) {
        EXPECT_TRUE(this->starset.containsCached(sample));
    }
}

TYPED_TEST( SamplingTest, StarsetConstrainedUniform ) {
    std::set<hypro::Point<TypeParam>> samples = hypro::uniform_constrained_sampling(this->starset, this->hPolytope, this->num_samples);

    for(auto& sample : samples) {
        EXPECT_TRUE(this->starset.contains(sample));
        EXPECT_FALSE(this->hPolytope.contains(sample));
    }
}
