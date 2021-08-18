#include "../../src/hypro/algorithms/convexHull/vertexEnumeration.h"
#include "../../src/hypro/config.h"
#include "../defines.h"
#include "gtest/gtest.h"

using namespace hypro;

class VertexEnumerationTest : public ::testing::Test {
  protected:
	matrix_t<mpq_class> a;
	vector_t<mpq_class> b;
	VertexEnumeration<mpq_class> vMatVec;
	VertexEnumeration<mpq_class> vHsp;

	virtual void SetUp() {
		std::vector<Halfspace<mpq_class>> hsVec;
		for ( unsigned i = 0; i < a.rows(); ++i ) {
			hsVec.emplace_back( vector_t<mpq_class>( a.row( i ) ), b( i ) );
		}

		vMatVec = VertexEnumeration<mpq_class>( a, b );
		vHsp = VertexEnumeration<mpq_class>( hsVec );
	}

	virtual void TearDown() {}

  public:
	VertexEnumerationTest() {
		// ConstraintSystem reproducing the example given at the end of the Avis and Fukuda paper.
		a = matrix_t<mpq_class>( 5, 2 );
		a << 1, 3, 5, 1, 3, 2, -1, -3, -2, 1;

		b = vector_t<mpq_class>( 5 );
		b << 4, 5, 2, 1, 2;
	}

	~VertexEnumerationTest() {}

	/*
	void test (){
	hypro::vector_t<mpq_class> v1 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v2 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v3 = hypro::vector_t<mpq_class>(2);
	v1 << 1,0;
	v2 << 0,1;
	v3 << 1,1;
	mpq_class n2 = 4;
	mpq_class n4 = 4;
	hypro::Halfspace<mpq_class> h1 = hypro::Halfspace<mpq_class>(v1,n2);
	hypro::Halfspace<mpq_class> h2 = hypro::Halfspace<mpq_class>(v2,n2);
	hypro::Halfspace<mpq_class> h3 = hypro::Halfspace<mpq_class>(v3,n4);
	std::vector<hypro::Halfspace<mpq_class>> v;
	v.push_back(h1);
	v.push_back(h2);
	v.push_back(h3);
	hypro::Dictionary<mpq_class> d = hypro::Dictionary<mpq_class>(v);
	d.printDictionary();
	std::size_t a = std::size_t(2);
	std::size_t b = std::size_t(0);
	std::size_t& i = a;
	std::size_t& j = b;
std::cout<<"\n test \n";
	d.pivot(i,j);
	d.printDictionary();
std::cout<<"\n test \n";
	d.selectCrissCrossPivot(i,j);
std::cout << "\n";
std::cout << i;
std::cout << "\n";
std::cout << j;
std::cout << "\n";
std::cout.flush();
	d.pivot(i,j);
	d.printDictionary();
	d.selectCrissCrossPivot(i,j);
std::cout << "\n";
std::cout << i;
std::cout << "\n";
std::cout << j;
std::cout << "\n";
std::cout.flush();
	d.pivot(i,j);
	d.printDictionary();

	hypro::VertexEnumeration<mpq_class> ev = hypro::VertexEnumeration<mpq_class>(v);
	ev.enumerateVertices();






	hypro::Dictionary<mpq_class> d = hypro::Dictionary<mpq_class>(v);
std::cout<<"\n test1 \n";
	d.printDictionary();
	hypro::VertexEnumeration<mpq_class> ev = hypro::VertexEnumeration<mpq_class>(v);

	std::vector<unsigned> basisAux = d.findZeros();
	//d.setOnes(basisAux);
	//d.pivot(i,j);
	d.printDictionary();
std::cout<<"\n test2 \n";	ev.hypro::VertexEnumeration<mpq_class>::findFirstVertex(v);
std::cout<<d.selectDualBlandPivot(i,j,basisAux);
std::cout<<"\ni="<<i<<";j="<<j<<";";d.pivot(i,j);d.printDictionary();

	//cout<<"\n test3 \n";
	//cout<<"\n"<< d.reverseDual(i,j,basisAux) <<"\n";

	i=0;j=0; std::cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	i=1;j=0; std::cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
std::cout<<"\n--------------\n";
std::cout << d.selectBlandPivot(i,j);
std::cout<<"\nselection  i="<<i<<";j="<<j<<"\n";
	d.pivot(i,j);
	d.printDictionary();
std::cout<<"\n--------------\n";
	d.pivot(i,j);
	i=0;j=1; std::cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	d.pivot(i,j);
	i=1;j=1; std::cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	d.pivot(i,j);
	//ev.enumerateDictionaries();
std::cout<<"\n test4 \n";


	//ev.enumerateVertices();


	hypro::vector_t<mpq_class> v1 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v2 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v3 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v4 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v5 = hypro::vector_t<mpq_class>(2);
	hypro::vector_t<mpq_class> v6 = hypro::vector_t<mpq_class>(2);
	v1 << 0,1;
	v2 << 0,-1;
	v3 << 1,0;
	v4 << -1,0;
	v5 << -1,1;
	v6 << -1,-1;
	mpq_class n2 = 2;
	mpq_class nm2 = -2;
	mpq_class nm1 = -1;
	mpq_class n3 = 3;
	mpq_class n0 = 0;
	hypro::Halfspace<mpq_class> h1 = hypro::Halfspace<mpq_class>(v1,n2);
	hypro::Halfspace<mpq_class> h2 = hypro::Halfspace<mpq_class>(v2,n2);
	hypro::Halfspace<mpq_class> h3 = hypro::Halfspace<mpq_class>(v3,n3);
	hypro::Halfspace<mpq_class> h4 = hypro::Halfspace<mpq_class>(v4,nm1);
	hypro::Halfspace<mpq_class> h5 = hypro::Halfspace<mpq_class>(v5,n0);
	hypro::Halfspace<mpq_class> h6 = hypro::Halfspace<mpq_class>(v6,n0);
	std::vector<hypro::Halfspace<mpq_class>> v;
	v.push_back(h5);
	v.push_back(h6);
	v.push_back(h1);
	v.push_back(h2);
	v.push_back(h4);
	v.push_back(h3);
	hypro::Dictionary<mpq_class> d = hypro::Dictionary<mpq_class>(v);
	}
	*/
};

TEST_F( VertexEnumerationTest, Constructor ) {
	// Note, the constructor from matrix and vector as well as from hPlane-Vector are already in the set-up method.
	VertexEnumeration<mpq_class> vDef;
	VertexEnumeration<mpq_class> vCop( vMatVec );

	// result conparison
	EXPECT_EQ( vMatVec.getHsv(), vHsp.getHsv() );
	EXPECT_EQ( vMatVec.getDictionaries(), vHsp.getDictionaries() );
	EXPECT_EQ( vMatVec.getHsv(), vCop.getHsv() );
	EXPECT_EQ( vMatVec.getDictionaries(), vCop.getDictionaries() );

	SUCCEED();
}

TEST_F( VertexEnumerationTest, Access ) {
	EXPECT_EQ( vMatVec.getHsv(), vHsp.getHsv() );
	EXPECT_EQ( vMatVec.getDictionaries(), vHsp.getDictionaries() );

	EXPECT_EQ( vMatVec.getHsv().size(), unsigned( a.rows() ) );
}

TEST_F( VertexEnumerationTest, SimpleEnumeration ) {
	vMatVec.enumerateVertices();
	vHsp.enumerateVertices();

	EXPECT_EQ( vMatVec.getPoints(), vHsp.getPoints() );
}

TEST_F( VertexEnumerationTest, DegenerateEnumeration ) {
	// first simple test is a pyramid with quadratic foundation in a 3D space.
	matrix_t<mpq_class> m = matrix_t<mpq_class>( 5, 3 );
	vector_t<mpq_class> c = vector_t<mpq_class>( m.rows() );

	m << 1, 1, 0, 0, 1, 1, -1, 1, 0, 0, 1, -1, 0, -1, 0;
	c << 1, 1, 1, 1, 0;
	VertexEnumeration<mpq_class> deg( m, c );
	deg.enumerateVertices();

	std::vector<Point<mpq_class>> vertices = deg.getPoints();
	EXPECT_EQ( vertices.size(), unsigned( 5 ) );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { 0, 1, 0 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { 1, 0, 1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { 1, 0, -1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -1, 0, 1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -1, 0, -1 } ) ) != vertices.end() );
}

TEST_F( VertexEnumerationTest, TransformationToPositive ) {
	// first simple test is a pyramid with quadratic foundation in a 3D space.
	matrix_t<mpq_class> m = matrix_t<mpq_class>( 6, 3 );
	vector_t<mpq_class> c = vector_t<mpq_class>( m.rows() );

	m << 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1;
	c << -1, 2, -1, 2, -1, 2;
	VertexEnumeration<mpq_class> deg( m, c );
	deg.enumerateVertices();

	std::vector<Point<mpq_class>> vertices = deg.getPoints();
	EXPECT_EQ( vertices.size(), unsigned( 8 ) );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -1, -1, -1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -1, -1, -2 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -1, -2, -1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -1, -2, -2 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -2, -1, -1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -2, -1, -2 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -2, -2, -1 } ) ) != vertices.end() );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<mpq_class>( { -2, -2, -2 } ) ) != vertices.end() );
}
