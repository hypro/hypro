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
            
	private:
		/***********************************************************************
		 * Member
		 **********************************************************************/
		std::set<Vertex<Number>> vertices;
		
	public:
		/***********************************************************************
		 * Constructors & Destructors
		 **********************************************************************/
                VertexContainer(){}
		VertexContainer(const VertexContainer& orig) { vertices = orig.vertices; }
		~VertexContainer(){}
		
		/***********************************************************************
		 * Getters & Setters
		 **********************************************************************/
		
                unsigned dimension() const
                {
                    assert( vertices.size() > 0 );
                    return (*vertices.begin()).dimension();
                }
                
		unsigned size() const
		{
			return vertices.size();
		}
		
		std::list<Vertex<Number>> getSmallerVertices(const Point<Number>& p)
                {
                        std::list<Vertex<Number>> verticesInBoundary;
                        for(auto vertexIt = vertices.begin(); vertexIt != vertices.end(); ++vertexIt)
                        {
                                if((*vertexIt).isInBoundary(p)) verticesInBoundary.push_back(*vertexIt);
                        }
                        return verticesInBoundary;
                }
		
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
			return (*(vertices.begin()) == Point<Number>());
		}
		
		/***********************************************************************
		 * Operators & Functions
		 **********************************************************************/
		
		VertexContainer<Number>& operator=(const VertexContainer<Number>& rhs) {
			if(this == &rhs) return (*this);
			vertices.clear();
			vertices = rhs.vertices;
		}
		
		inline vSetIt<Number> find(const Point<Number>& p, bool colour = false) const {
			return vertices.find(Vertex<Number>(p,colour));
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
		inline std::pair<vSetCIt<Number>, bool> insert(const Vertex<Number>& v) {
                    std::cout << "insert: ";
                    std::cout << "contained(" << ( vertices.find(v) != vertices.end() ) << "), :";
			return vertices.insert(v);
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
			for(auto it = cont.begin(); it != cont.end(); ++it ) {
				ostr << (*it) << "\n";
			}
			return ostr;
		}
	
		
	};
}