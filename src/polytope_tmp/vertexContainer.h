/** 
 * @file   vertexContainer.h
 * Created on June 8, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 */
#ifndef VERTEXCONTAINER_H
#define	VERTEXCONTAINER_H

#include <set>
#include <list>
#include "vertex.h"


namespace reachLin {
    
    typedef std::set<Vertex>::const_iterator vSetCIt;
    typedef std::set<Vertex>::iterator VertexContainerIt;
class VertexContainer {
public:
    VertexContainer(unsigned dimension=DEFAULT_DIM);
    VertexContainer(const VertexContainer& orig);
    virtual ~VertexContainer();
    
    std::list<Vertex> getSmallerVertices(const Point& p);
    
    VertexContainer& operator=(const VertexContainer& rhs) {
        if(this == &rhs) return (*this);
        vertices.clear();
        mDimension=rhs.mDimension;
        //if(mDimension != rhs.mDimension) std::cout << "error dimensions of vertexcontainer";
        
        vertices = rhs.vertices;
    } 
    
    /**
     * 
     * @return 
     */
    inline bool originIsVertex() const {
        return (*(vertices.begin()) == Point(mDimension));
    }
    
    
    
    
    
    inline vSetIt find(const Point& p) const {
        return vertices.find(Vertex(p,false));
    }
    
    inline vSetIt find(const Vertex& v) const {
        std::set<Vertex>::iterator it = vertices.find(v);
        if (it->getColor() != v.getColor())  it = vertices.end();
        return it;
    }
    
    inline void move(const Point& p) {
        vSet tmp;
        vSetIt tmpIt = tmp.begin();
        for(vSetIt it = vertices.begin(); it != vertices.end(); ++it) {
            Vertex v = Vertex(*it);
            v.move(p);
            tmp.insert(tmpIt, v);
            tmpIt++;
        }
        vertices = tmp;
    }
    
    /**
     * 
     * @param p
     * @return 
     */
    inline std::pair<bool, bool> isVertex(const Point& p) const {
        std::set<Vertex>::const_iterator it = vertices.find(Vertex(p,false));
        if (it == vertices.end()) return std::pair<bool,bool>(false, false);
        else return std::pair<bool, bool>(true, it->getColor());
    }
    
    /**
     * 
     * @return 
     */
    inline vSetCIt begin() const {
        return vertices.begin();
    }
    
    /**
     * 
     * @return 
     */
    inline vSetCIt end() const {
        return vertices.end();
    }
    
    /**
     * 
     * @param v
     * @return A bidirectional iterator to the inserted Vertex.
     * Not safe. 
     */
    inline vSetCIt insert(const Vertex& v) {
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
    inline vSetIt insert(const Point& p,const bool c=false) {
         
        return insert(Vertex(p,c));
    }
    
    /**
     * 
     * @param v
     * @param pos
     * @return 
     */
    template <typename BiIterator>
    inline vSetIt insert(const Vertex& v, const BiIterator pos) {
        return vertices.insert(pos,v);
    }
    
    inline vSetIt insertAtBack(const Vertex& v) {
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
    inline vSetIt insert(Point p, bool c, const BiIterator pos) {
        return insert(Vertex(p,c),pos);
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
    inline void erase(const Point& p) {
        Vertex v = Vertex(p,false);
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
    
    inline bool set(const Point& p, bool c) {
        std::set<Vertex>::iterator it = vertices.find(Vertex(p,false));
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
    const bool& operator[] (const Point& p) const {
        return isVertex(p).second;
    }

    
    
    friend std::ostream& operator<<(std::ostream& ostr, const VertexContainer& cont) {
        for(vSetIt it = cont.vertices.begin(); it != cont.vertices.end(); ++it ) {
            ostr << *it << std::endl;
        }       
        return ostr;
    }
private:
    std::set<Vertex> vertices;
    unsigned mDimension;

};

}

#endif	/* VERTEXCONTAINER_H */

