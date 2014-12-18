/**
 * A container for vertices.
 * @file   VertexContainer.h
 *
 * @author Sebastian Junges
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2011-06-08
 * @version 2014-05-28
 */

#pragma once

#include <set>
#include <list>
#include "Vertex.h"


namespace hypro {
	
	template<typename Number>
	class VertexContainer {
            
	private:
		/***********************************************************************
		 * Member
		 **********************************************************************/
		vSet<Number> mVertices;
		
	public:
		/***********************************************************************
		 * Constructors & Destructors
		 **********************************************************************/
                VertexContainer(){}
                VertexContainer(const vSet<Number>& vertices) : mVertices(vertices) {}
		VertexContainer(const VertexContainer& orig) { mVertices = orig.mVertices; }
		~VertexContainer(){}
		
		/***********************************************************************
		 * Getters & Setters
		 **********************************************************************/
		
                unsigned dimension() const
                {
                    assert( mVertices.size() > 0 );
                    return (*mVertices.begin()).dimension();
                }
                
                std::vector<carl::Variable> variables() const
                {
                    assert( mVertices.size() > 0 );
                    return (*mVertices.begin()).variables();
                }
                
		unsigned size() const
		{
                    return mVertices.size();
		}
                
                bool empty() const
                {
                    return mVertices.empty();
                }
                
                vSet<Number> vertices() const
                {
                    return mVertices;
                }
		
		vList<Number> getSmallerVertices(const Point<Number>& p)
                {
                        vList<Number> verticesInBoundary;
                        for(auto vertexIt = mVertices.begin(); vertexIt != mVertices.end(); ++vertexIt)
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
			vSetIt<Number> it = mVertices.find(Vertex<Number>(p,false));
			if (it == mVertices.end()) return std::pair<bool,bool>(false, false);
			else return std::pair<bool, bool>(true, it->getColor());
		}
		
		/**
		 *
		 * @return
		 */
		inline bool originIsVertex() const {
                    assert(mVertices.size() > 0);
                    Vertex<Number> origin = Vertex<Number>(mVertices.begin()->point().newEmpty(), true);
                    return (*(mVertices.begin()) == origin);
		}
		
		/***********************************************************************
		 * Operators & Functions
		 **********************************************************************/
		
		VertexContainer<Number>& operator=(const VertexContainer<Number>& rhs) {
			if(this == &rhs) return (*this);
			mVertices.clear();
			mVertices = rhs.mVertices;
                        return *this;
		}
		
		inline vSetIt<Number> find(const Point<Number>& p, bool colour = false) const {
			return find(Vertex<Number>(p,colour));
		}
		
		inline vSetIt<Number> find(const Vertex<Number>& v) const {
			vSetIt<Number> it = mVertices.find(v);
			if (it->color() != v.color()) it = mVertices.end();
			return it;
		}
		
		inline void move(const Point<Number>& p) {
			vSet<Number> tmp;
			vSetIt<Number> tmpIt = tmp.begin();
			for(vSetIt<Number> it = mVertices.begin(); it != mVertices.end(); ++it) {
				Vertex<Number> v = Vertex<Number>(*it);
				v.move(p);
				tmp.insert(tmpIt, v);
				tmpIt++;
			}
			mVertices = tmp;
		}
		
		inline void linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) {
			vSet<Number> tmp;
			vSetIt<Number> tmpIt = tmp.begin();
			for(vSetIt<Number> it = mVertices.begin(); it != mVertices.end(); ++it) {
				Vertex<Number> v = Vertex<Number>(*it);
				v.linearTransformation(A, b);
				tmp.insert(tmpIt, v);
				tmpIt++;
			}
			mVertices = tmp;
		}

		/**
		 *
		 * @return
		 */
		inline vSetIt<Number> begin() const {
			return mVertices.begin();
		}
		
		/**
		 *
		 * @return
		 */
		inline vSetIt<Number> end() const {
			return mVertices.end();
		}
		
		/**
		 *
		 * @param v
		 * @return A bidirectional iterator to the inserted Vertex.
		 * Not safe.
		 */
		inline std::pair<vSetIt<Number>, bool> insert(const Vertex<Number>& v) {
                    return mVertices.insert(v);
		}
		
		/**
		 *
		 * @param begin
		 * @param end
		 */
		template <typename ForwardIterator>
		inline void insert(ForwardIterator begin, ForwardIterator end) {
			mVertices.insert(begin, end);
		}
		
		/**
		 *
		 * @param p
		 * @param c
		 * @return
		 */
		inline std::pair<vSetIt<Number>, bool> insert(const Point<Number>& p, const bool c=false) {
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
			return mVertices.insert(pos,v);
		}
		
		inline vSetIt<Number> insertAtBack(const Vertex<Number>& v) {
			return mVertices.insert(--mVertices.end(), v);
		}
		
		/**
		 *
		 * @param p
		 * @param c
		 * @param pos
		 * @return
		 */
		template <typename BiIterator>
		inline vSetIt<Number> insert(const Point<Number> p, bool c, const BiIterator pos) {
			return insert(Vertex<Number>(p,c),pos);
		}
		
		/**
		 *
		 * @param pos
		 */
		template <typename BiIterator>
		inline void erase(BiIterator pos) {
			mVertices.erase(pos);
		}
		
		/**
		 *
		 * @param p Vertex that is erased.
		 */
		inline void erase(const Point<Number>& p) {
			Vertex<Number> v = Vertex<Number>(p,false);
			mVertices.erase(v);
			
		}
		
		/**
		 * clears the underlying container.
		 */
		inline void clear() {
			mVertices.clear();
		}
		
		inline bool set(const Point<Number>& p, bool c) {
			typename std::set<Vertex<Number>>::iterator it = mVertices.find(Vertex<Number>(p,false));
			if (it==mVertices.end()) return false;
			mVertices.erase(it);
			insert(p,c,it);
			return true;
		}

		/**
		 *
		 * @param c1
		 * @param c2
		 * @return true, if they are equal.
		 */
		friend bool operator==(const VertexContainer<Number> & c1, const VertexContainer<Number> & c2)
		{
			return c1.mVertices == c2.mVertices;
		}

		/**
		 *
		 * @param c1
		 * @param c2
		 * @return true, if they are not equal.
		 */
		friend bool operator!=(const VertexContainer<Number> & c1, const VertexContainer<Number> & c2)
		{
			return c1.mVertices != c2.mVertices;
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
