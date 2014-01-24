/**
 * A container for vertices.
 * @file   VertexContainer.h
 *
 * @author Sebastian Junges
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2011-06-08
 * @version 2013-01-17
 */

#pragma once

#include <set>
#include <list>
#include "Vertex.h"


namespace hypro {
	
	template<typename Number>
	using vSetCIt = typename std::set<Vertex<Number>>::const_iterator;
	template<typename Number>
	using VertexContainerIt = typename std::set<Vertex<Number>>::iterator;
	
	template<typename Number>
	class VertexContainer {
		/***********************************************************************
		 * Member
		 **********************************************************************/
	private:
		std::set<Vertex<Number>> vertices;
		unsigned mDimension;
		
	public:
		/***********************************************************************
		 * Constructors & Destructors
		 **********************************************************************/
		VertexContainer(unsigned dimension=DEFAULT_DIM);
		VertexContainer(const VertexContainer& orig);
		~VertexContainer()
		{}
		
		/***********************************************************************
		 * Getters & Setters
		 **********************************************************************/
		
		unsigned dimension() const
		{
			return mDimension;
		}
		
		std::list<Vertex<Number>> getSmallerVertices(const Point<Number>& p);
		
		/**
		 *
		 * @param p
		 * @return
		 */
		inline std::pair<bool, bool> isVertex(const Point<Number>& p) const {
			typename std::set<Vertex<Number>>::const_iterator it = vertices.find(Vertex<Number>(p,false));
			if (it == vertices.end()) return std::pair<bool,bool>(false, false);
			else return std::pair<bool, bool>(true, it->getColor());
		}
		
		/**
		 *
		 * @return
		 */
		inline bool originIsVertex() const {
			return (*(vertices.begin()) == Point<Number>(mDimension));
		}
		
		/***********************************************************************
		 * Operators & Functions
		 **********************************************************************/
		
		VertexContainer<Number>& operator=(const VertexContainer<Number>& rhs) {
			if(this == &rhs) return (*this);
			vertices.clear();
			mDimension=rhs.mDimension;
			vertices = rhs.vertices;
		}
		
		inline vSetIt<Number> find(const Point<Number>& p) const {
			return vertices.find(Vertex<Number>(p,false));
		}
		
		inline vSetIt<Number> find(const Vertex<Number>& v) const {
			typename std::set<Vertex<Number>>::iterator it = vertices.find(v);
			if (it->getColor() != v.getColor())  it = vertices.end();
			return it;
		}
		
		inline void move(const Point<Number>& p) {
			vSet<Number> tmp;
			vSetIt<Number> tmpIt = tmp.begin();
			for(vSetIt<Number> it = vertices.begin(); it != vertices.end(); ++it) {
				Vertex<Number> v = Vertex<Number>(*it);
				v.move(p);
				tmp.insert(tmpIt, v);
				tmpIt++;
			}
			vertices = tmp;
		}
		
		/**
		 *
		 * @return
		 */
		inline vSetCIt<Number> begin() const {
			return vertices.begin();
		}
		
		/**
		 *
		 * @return
		 */
		inline vSetCIt<Number> end() const {
			return vertices.end();
		}
		
		/**
		 *
		 * @param v
		 * @return A bidirectional iterator to the inserted Vertex.
		 * Not safe.
		 */
		inline vSetCIt<Number> insert(const Vertex<Number>& v) {
			return vertices.insert(v).first;
		}
		
		/**
		 *
		 * @param begin
		 * @param end
		 */
		template <typename ForwardIterator>
		inline void insert(ForwardIterator begin, ForwardIterator end) {
			vertices.insert(begin, end);
		}
		
		/**
		 *
		 * @param p
		 * @param c
		 * @return
		 */
		inline vSetIt<Number> insert(const Point<Number>& p,const bool c=false) {
			
			return insert(Vertex<Number>(p,c));
		}
		
		/**
		 *
		 * @param v
		 * @param pos
		 * @return
		 */
		template <typename BiIterator>
		inline vSetIt<Number> insert(const Vertex<Number>& v, const BiIterator pos) {
			return vertices.insert(pos,v);
		}
		
		inline vSetIt<Number> insertAtBack(const Vertex<Number>& v) {
			return vertices.insert(--vertices.end(), v);
		}
		
		/**
		 *
		 * @param p
		 * @param c
		 * @param pos
		 * @return
		 */
		template <typename BiIterator>
		inline vSetIt<Number> insert(Point<Number> p, bool c, const BiIterator pos) {
			return insert(Vertex<Number>(p,c),pos);
		}
		
		/**
		 *
		 * @param pos
		 */
		template <typename BiIterator>
		inline void erase(BiIterator pos) {
			vertices.erase(pos);
		}
		
		/**
		 *
		 * @param p Vertex that is erased.
		 */
		inline void erase(const Point<Number>& p) {
			Vertex<Number> v = Vertex<Number>(p,false);
			vertices.erase(v);
			
		}
		
		/**
		 * clears the underlying container.
		 */
		inline void clear() {
			vertices.clear();
		}
		
		/**
		 *
		 * @return the size
		 */
		inline unsigned size() {
			return vertices.size();
		}
		
		inline bool set(const Point<Number>& p, bool c) {
			typename std::set<Vertex<Number>>::iterator it = vertices.find(Vertex<Number>(p,false));
			if (it==vertices.end()) return false;
			vertices.erase(it);
			insert(p,c,it);
			return true;
		}
		
		/**
		 *
		 * @param p
		 * @return
		 */
		const bool& operator[] (const Point<Number>& p) const {
			return isVertex(p).second;
		}
		
		
		
		friend std::ostream& operator<<(std::ostream& ostr, const VertexContainer<Number>& cont) {
			for(vSetIt<Number> it = cont.vertices.begin(); it != cont.vertices.end(); ++it ) {
				ostr << *it << std::endl;
			}
			return ostr;
		}
	
		
	};
}
#include "VertexContainer.tpp"