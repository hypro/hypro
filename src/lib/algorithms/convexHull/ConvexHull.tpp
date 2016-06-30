#include "ConvexHull.h"

namespace hypro {
	
	template<typename Number>
	ConvexHull<Number>::ConvexHull(const std::vector<Point<Number>> points): mPoints(points) {}
	
	template<typename Number>
	ConvexHull<Number>::ConvexHull(const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone):
		mPoints(points),
		mCone(cone) 
		{}
	
	template<typename Number>
	std::vector<Point<Number>> ConvexHull<Number>::getPoints() const {
		return mPoints;
	}
	
	template<typename Number>
	std::vector<vector_t<Number>> ConvexHull<Number>::getCone() const {
		return mCone;
	}
	
	template<typename Number>
	std::vector<Halfspace<Number>> ConvexHull<Number>::getConeHsv() const {
		return mConeHsv;
	}
	
	template<typename Number>
	std::vector<Halfspace<Number>> ConvexHull<Number>::getDualHsv() const {
		return mDualHsv;
	}
	
	template<typename Number>
	std::vector<Halfspace<Number>> ConvexHull<Number>::getHsv() const {
		return mHsv;
	}
	
	template<typename Number>
	bool ConvexHull<Number>::findOffset() {
		if(mPoints.size()<2) {return false;}
		mOffset = vector_t<Number>::Zero(mPoints[0].rawCoordinates().size());
		vector_t<Number> zero = vector_t<Number>::Zero(mPoints[0].rawCoordinates().size());
		for(const auto& point: mPoints) {
			mOffset+=point.rawCoordinates();
		}
		mOffset = mOffset/mPoints.size();
		unsigned index = 0;
		for(auto& point: mPoints) {
			point.setCoordinates(point.rawCoordinates() - mOffset);
			if(point.rawCoordinates()==zero) {mPoints.erase(mPoints.begin()+index);};
			++index;
		}
		return true;
	}
	
	template<typename Number>
	void ConvexHull<Number>::toDual() {
		for(const auto& p:mPoints) {
			mDualHsv.push_back(Halfspace<Number>(p.rawCoordinates(),Number(1)));
		}
	}
	
	template<typename Number>
	void ConvexHull<Number>::toPrimal(const std::vector<Point<Number>> points) {
		for(const auto& p:points) {
			mHsv.push_back(Halfspace<Number>(p.rawCoordinates(),Number(1)));
		}
	}
	
	template<typename Number>
	void ConvexHull<Number>::convexHullVertices() {//!!modify the points
		findOffset();
		toDual();
		VertexEnumeration<Number> ev = VertexEnumeration<Number>(mDualHsv);
		ev.enumerateVertices();
		toPrimal(ev.getPoints());
		translateHsv();
	}
	
	template<typename Number>
	void ConvexHull<Number>::conicHull() {
		std::vector<Point<Number>> points;
		for(const auto& cone:mCone) {
			points.push_back(Point<Number>(cone));
		}
		Point<Number> zero = Point<Number>::Zero(mCone[0].size());
		points.push_back(zero);
		ConvexHull<Number> ch = ConvexHull<Number>(points);
		ch.convexHullVertices();
		for(const auto& hs:ch.getHsv()) {
			if(hs.offset()==0) {mConeHsv.push_back(hs);}
		}
		for(const auto& hs:ch.mConeHsv) {
			cout << hs;
		}
	}
	
	template<typename Number>
	void ConvexHull<Number>::polyhedriclHull() {
		std::vector<vector_t<Number>> newCone;
		for(const auto& p:mPoints) {
			vector_t<Number> aux = vector_t<Number>(p.rawCoordinates().size()+1);
			for(unsigned index=0;index<p.rawCoordinates().size();++index) {
				aux[index]=p.rawCoordinates()[index];
			}
			aux[p.rawCoordinates().size()]=1;
			newCone.push_back(aux);
		}
		for(const auto& c:mCone) {
			vector_t<Number> aux = vector_t<Number>(c.size()+1);
			for(unsigned index=0;index<c.size();++index) {
				aux[index]=c[index];
			}
			aux[c.size()]=0;
			newCone.push_back(aux);
		}
		cout <<"\n";
		for(const auto& c:newCone) {
			cout <<c<<"\n";
		}
		std::vector<Point<Number>> empty;
		ConvexHull<Number> ch = ConvexHull<Number>(empty, newCone);
		ch.conicHull();
		std::vector<Halfspace<Number>> hsv = ch.getConeHsv();
		for(auto& hs:hsv) {
			hs.setOffset(hs.offset()-hs.normal()[hs.normal().size()-1]);//projection fonction
			vector_t<Number> aux=vector_t<Number>(hs.normal().size()-1);
			for(unsigned index=0;index<hs.normal().size()-1;++index) {
				aux[index] = hs.normal()[index];
			}
			hs.setNormal(aux);
			mHsv.push_back(hs);
		}
	}

	template<typename Number>
	void ConvexHull<Number>::translateHsv() {
		for(auto& hs:mHsv) {
			for(unsigned index = 0;index<hs.normal().size();++index) {
				hs.setOffset(hs.offset() + hs.normal()[index]*mOffset[index]);
			}
		}
	}
	
}
