/**
 * Testfile reproducing the example given at the end of the Avis and Fukuda paper.
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../src/lib/algorithms/convexHull/Dictionary.h"
#include "../../src/lib/algorithms/convexHull/vertexEnumeration.h"
#include "../../src/lib/algorithms/convexHull/ConvexHull.h"

#include "../../src/lib/config.h"

template<typename Number>
class VertexEnumerationTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		hypro::matrix_t<Number> a = hypro::matrix_t<Number>(5,2);
		a << 1,3,5,1,3,2,-1,-3,-2,1;

		hypro::vector_t<Number> b = hypro::vector_t<Number>(5);
		b << 4,5,2,1,2;

	}

	virtual void TearDown()
	{	
	cout<<"\n test \n";
	std::size_t a = std::size_t(1);
	std::size_t b = std::size_t(0);
	std::size_t& i = a;
	std::size_t& j = b;
	hypro::vector_t<Number> v1 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v2 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v3 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v4 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v5 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v6 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v7 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v8 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v9 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v10 = hypro::vector_t<Number>(2);
v1 << Number("0") , Number("1000000000") /Number("126666837") ;
v2 << Number("0") , Number("1000000007") /Number("126145104") ;
v3 << Number("62582634845368369") /Number("1603317339625000000") , Number("12563674389179812881") /Number("1603317339625000000") ;
v4 << Number("31419623978746011") /Number("798268015375000000") , Number("6281333328741285239") /Number("798268015375000000") ;
v5 << Number("94360732434603989") /Number("798268015375000000") , Number("6281333328741285239") /Number("798268015375000000") ;
v6 << Number("943607394911037274008589") /Number("7982680156547665375000000") , Number("62813333284725480899008589") /Number("7982680156547665375000000") ;
v7 << Number("943607394911037274008589") /Number("7982680156547665375000000") , Number("62183922199946313350991411") /Number("7982680156547665375000000") ;
v8 << Number("62582634845368369") /Number("1603317339625000000") , Number("12437257485810474619") /Number("1603317339625000000") ;
v9 << Number("188999538214706631") /Number("1603317339625000000") , Number("12437257485810474619") /Number("1603317339625000000") ;
v10 << Number("1889995522900738536227331") /Number("16033173386750764625000000") , Number("124372574867978475088772669") /Number("16033173386750764625000000") ;
	Number n4 = 4;
	Number n2 = 0.5;
	Number n1 = 1;
	Number nm2 = -2;
	Number n0 = 0;
	hypro::Halfspace<Number> h1 = hypro::Halfspace<Number>(v1,n4);
	hypro::Halfspace<Number> h2 = hypro::Halfspace<Number>(v2,nm2);
	hypro::Halfspace<Number> h3 = hypro::Halfspace<Number>(v3,n0);
	hypro::Halfspace<Number> h4 = hypro::Halfspace<Number>(v4,n2);
	hypro::Halfspace<Number> h5 = hypro::Halfspace<Number>(v5,n2);
	hypro::Halfspace<Number> h6 = hypro::Halfspace<Number>(v6,n0);
	hypro::Halfspace<Number> h7 = hypro::Halfspace<Number>(v7,n0);
	hypro::Halfspace<Number> h8 = hypro::Halfspace<Number>(v8,n4);
	hypro::Halfspace<Number> h9 = hypro::Halfspace<Number>(v9,n0);
	std::vector<hypro::Halfspace<Number>> v;
	std::vector<hypro::Point<Number>> p;
	std::vector<hypro::vector_t<Number>> cone;
	std::vector<hypro::vector_t<Number>> linealty;
	hypro::Point<Number> p1 = hypro::Point<Number>(v1);
	hypro::Point<Number> p2 = hypro::Point<Number>(v2);
	hypro::Point<Number> p3 = hypro::Point<Number>(v3);
	hypro::Point<Number> p4 = hypro::Point<Number>(v4);
	hypro::Point<Number> p5 = hypro::Point<Number>(v5);
	hypro::Point<Number> p6 = hypro::Point<Number>(v6);
	hypro::Point<Number> p7 = hypro::Point<Number>(v7);
	hypro::Point<Number> p8 = hypro::Point<Number>(v8);
	hypro::Point<Number> p9 = hypro::Point<Number>(v9);
	hypro::Point<Number> p10 = hypro::Point<Number>(v10);
	//cone.push_back(v4);
	//cone.push_back(v5);
	//cone.push_back(v3);
	//linealty.push_back(v5);
	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	p.push_back(p5);
	p.push_back(p6);
	p.push_back(p7);
	p.push_back(p8);
	p.push_back(p9);
	p.push_back(p10);
	//v.push_back(h1);
	//v.push_back(h2);
	/*v.push_back(h3);
	v.push_back(h4);
	v.push_back(h5);*/
	v.push_back(h6);
	v.push_back(h7);
	v.push_back(h8);
	//v.push_back(h9);
	hypro::Dictionary<Number> d = hypro::Dictionary<Number>(v);
	d.printDictionary();
	cout<<"\n beginning \n";
	hypro::ConvexHull<Number> ch = hypro::ConvexHull<Number>(p);
	
	//hypro::VertexEnumeration<Number> ev = hypro::VertexEnumeration<Number>(v);
	//hypro::Dictionary<Number> d2 = ev.getDictionaries()[0];d2.printDictionary();
	cout<<"\n test0 \n";
	ch.convexHullVertices();
	
	//ev.enumerateVertices();
	//ev.findLinealtySpace();
	cout<<"\n test1 \n";
	//ch.conicHull();
	//ev.addLinealtyConstrains();
	cout<<"\n test2\n";
	//ch.polyhedriclHull();
	/*for(const auto& hsv:ch.getConeHsv()) {
		cout<<hsv<<"\n";
	}*/
	cout<<"\n test3 \n";
	for(const auto& hsv:ch.getHsv()) {
		cout<<hsv<<"\n";
	}
	for(const auto& hsv:ch.getHsv()) {
		int count =0;
		for(const auto& po:p) {
			if(hsv.contains(po.rawCoordinates())){++count;}
		}
		cout << count <<"\n";
	}
	cout<<"\n test4 \n";
	//ev.enumerateVerticesEachDictionary();
	
	
	cout<<"\n test5 \n";
	//ev.toGeneralCoordinates();
	cout<<"\n test6 \n";
	//for(unsigned i=0;i<ev.getPoints().size();++i) {cout<< ev.getPoints()[i]<<"\n";}
	cout<<"\n test7 \n";
	//for(unsigned i=0;i<ev.getCones().size();++i) {cout<< hypro::Point<Number>(ev.getCones()[i])<<"\n";}
	cout<<"\n test8 \n";
	/*for(const auto& l:ev.getLinealtySpace()) {
		cout<<l<<"\n";
	}*/
	/*std::vector<std::size_t> availableIndices = std::vector<std::size_t>(1);
	availableIndices[0]=1;
	d.setValue(1,2,1);
	d.printDictionary();
	cout << "\n reversedual? " <<d.reverseDual(0,1,availableIndices)<<"\n";*/
	/*std::vector<std::size_t> dispo;dispo.push_back(0);
	dispo.push_back(1);
	d2.setValue(1,3,Number(1));d2.setValue(0,3,Number(1));
	i=0;j=1;
	d2.pivot(i,j);d2.printDictionary();
	i=0;j=0;
	d2.pivot(i,j);d2.printDictionary();d2.pivot(i,j);
	cout << "\n reverse dual bland: "<<d2.reverseDual(i,j,dispo);cout << "  i="<<i<<"  j="<<j<<"\n";
	i=0;j=1;
	d2.pivot(i,j);d2.printDictionary();d2.pivot(i,j);
	cout << "\n reverse dual bland: "<<d2.reverseDual(i,j,dispo);cout << "  i="<<i<<"  j="<<j<<"\n";
	i=0;j=2;
	d2.pivot(i,j);d2.printDictionary();d2.pivot(i,j);
	cout << "\n reverse dual bland: "<<d2.reverseDual(i,j,dispo);cout << "  i="<<i<<"  j="<<j<<"\n";
	i=1;j=0;
	d2.pivot(i,j);d2.printDictionary();d2.pivot(i,j);
	cout << "\n reverse dual bland: "<<d2.reverseDual(i,j,dispo);cout << "  i="<<i<<"  j="<<j<<"\n";
	i=1;j=1;
	d2.pivot(i,j);d2.printDictionary();d2.pivot(i,j);
	cout << "\n reverse dual bland: "<<d2.reverseDual(i,j,dispo);cout << "  i="<<i<<"  j="<<j<<"\n";
	i=1;j=2;
	d2.pivot(i,j);d2.printDictionary();d2.pivot(i,j);
	cout << "\n reverse dual bland: "<<d2.reverseDual(i,j,dispo);cout << "  i="<<i<<"  j="<<j<<"\n";
	d2.pivot(i,j);*/
	//cout << "\n select dual bland: "<<d2.selectDualBlandPivot(i,j,dispo);
	//cout << "  i="<<i<<"  j="<<j<<"\n";
	//d2.printDictionary();
	cout<<"\n last test \n";
	
	
	}

public:
	void test (){
	hypro::vector_t<Number> v1 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v2 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v3 = hypro::vector_t<Number>(2);
	v1 << 1,0;
	v2 << 0,1;
	v3 << 1,1;
	Number n2 = 4;
	Number n4 = 4;
	hypro::Halfspace<Number> h1 = hypro::Halfspace<Number>(v1,n2);
	hypro::Halfspace<Number> h2 = hypro::Halfspace<Number>(v2,n2);
	hypro::Halfspace<Number> h3 = hypro::Halfspace<Number>(v3,n4);
	std::vector<hypro::Halfspace<Number>> v;
	v.push_back(h1);
	v.push_back(h2);
	v.push_back(h3);
	hypro::Dictionary<Number> d = hypro::Dictionary<Number>(v);
	d.printDictionary();
	std::size_t a = std::size_t(2);
	std::size_t b = std::size_t(0);
	std::size_t& i = a;
	std::size_t& j = b;
	cout<<"\n test \n";
	d.pivot(i,j);
	d.printDictionary();	
	cout<<"\n test \n";
	d.selectCrissCrossPivot(i,j);
	cout << "\n";
	cout << i;
	cout << "\n";
	cout << j;
	cout << "\n";
	cout.flush();
	d.pivot(i,j);
	d.printDictionary();
	d.selectCrissCrossPivot(i,j);
	cout << "\n";
	cout << i;
	cout << "\n";
	cout << j;
	cout << "\n";
	cout.flush();
	d.pivot(i,j);
	d.printDictionary();	
	
	hypro::VertexEnumeration<Number> ev = hypro::VertexEnumeration<Number>(v);
	ev.enumerateVertices();
	
	
	
	
	
	
	/*hypro::Dictionary<Number> d = hypro::Dictionary<Number>(v);
	cout<<"\n test1 \n";
	d.printDictionary();
	hypro::VertexEnumeration<Number> ev = hypro::VertexEnumeration<Number>(v);

	std::vector<unsigned> basisAux = d.findZeros();
	//d.setOnes(basisAux);
	//d.pivot(i,j);
	d.printDictionary();
	cout<<"\n test2 \n";	ev.hypro::VertexEnumeration<Number>::findFirstVertex(v);
	cout<<d.selectDualBlandPivot(i,j,basisAux);
	cout<<"\ni="<<i<<";j="<<j<<";";d.pivot(i,j);d.printDictionary();
	*/
	cout<<"\n test3 \n";
	//cout<<"\n"<< d.reverseDual(i,j,basisAux) <<"\n";
	
	/*i=0;j=0; cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	i=1;j=0; cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	cout<<"\n--------------\n";
	cout << d.selectBlandPivot(i,j);
	cout<<"\nselection  i="<<i<<";j="<<j<<"\n";
	d.pivot(i,j);
	d.printDictionary();
	cout<<"\n--------------\n";
	d.pivot(i,j);
	i=0;j=1; cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	d.pivot(i,j);
	i=1;j=1; cout<<"\ni="<<i<<";j="<<j<<"; rev="<<d.reverse(i,j);
	d.pivot(i,j);
	d.printDictionary();
	d.pivot(i,j);
	//ev.enumerateDictionaries();	
	cout<<"\n test4 \n";


	//ev.enumerateVertices();*/
	
	
	
	
	
	/*
	hypro::vector_t<Number> v1 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v2 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v3 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v4 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v5 = hypro::vector_t<Number>(2);
	hypro::vector_t<Number> v6 = hypro::vector_t<Number>(2);
	v1 << 0,1;
	v2 << 0,-1;
	v3 << 1,0;
	v4 << -1,0;
	v5 << -1,1;
	v6 << -1,-1;
	Number n2 = 2;
	Number nm2 = -2;
	Number nm1 = -1;
	Number n3 = 3;
	Number n0 = 0;
	hypro::Halfspace<Number> h1 = hypro::Halfspace<Number>(v1,n2);
	hypro::Halfspace<Number> h2 = hypro::Halfspace<Number>(v2,n2);
	hypro::Halfspace<Number> h3 = hypro::Halfspace<Number>(v3,n3);
	hypro::Halfspace<Number> h4 = hypro::Halfspace<Number>(v4,nm1);
	hypro::Halfspace<Number> h5 = hypro::Halfspace<Number>(v5,n0);
	hypro::Halfspace<Number> h6 = hypro::Halfspace<Number>(v6,n0);
	std::vector<hypro::Halfspace<Number>> v;
	v.push_back(h5);
	v.push_back(h6);
	v.push_back(h1);
	v.push_back(h2);
	v.push_back(h4);
	v.push_back(h3);
	hypro::Dictionary<Number> d = hypro::Dictionary<Number>(v);*/
	
	
	
	
	
	
	
	
	}
	};

TYPED_TEST(VertexEnumerationTest, DictionaryAccess)
{
	SUCCEED();
}


