/* 
 * File:   ReachTreeNode.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 10:52 AM
 */

#include "../representations/GeometricObject.h"

namespace hypro
{
    template <typename Representation>
    using flowpipe_t = std::vector<Representation>;
    
    template <typename Number, typename Representation>
    class ReachTreeNode
    {
        private:
            Location<Number>* mLoc;
            Number mTimeStep;
            unsigned mDepth;
            representation_name mRep;
            Representation mFirst;
            Representation mLast;
            // Data structure saving for each transition of mLoc the indices of the 
            // segments satisfying the corresponding guard
            std::map< Transition<Number>*, std::vector< unsigned > > mGuardSatisfiedIndices;
            // Data structure saving a rough overapproximation of the current flowpipe
            // for fixpoint recognition
            flowpipe_t mOverapprox;
            std::vector< ReachTreeNode* > mChildren;
            ReachTreeNode* mParent;
            // TO-DO: add unique ID for each node
        public:
        /**
	 * @brief Constructor 
	 *
	 * @param TO-DO
	 */
	ReachTreeNode( Location<Number>* _loc, Number _time_step, unsigned _depth, representation_name _rep, ReachTreeNode* _parent );
        
        Location<Number>* getLocation();
        
        Number getTimeStep();
        
        unsigned getDepth();
        
        representation_name getRep();
        
        Representation getFirstSegment();
        
        Representation getLastSegment();
        
        std::map< Transition<Number>*, std::vector< unsigned > > getGuardSatisfiedIndices();
        
        flowpipe_t getOverapprox();
        
        std::vector< ReachTreeNode* > getChildren();
        
        ReachTreeNode getParent();
        
        void setTimeStep( Number _time_step );
        
        void setRepresentation( representation_name _rep );
        
        void setFirstSegment( Representation _first );
        
        void setLastSegment( Representation _last );
        
        void setGuardSatisfyingSegments( std::map< unsigned, std::pair< Number, Number > > _guard_satisfied_first_last );
        
        void setOverapproximation( flowpipe_t& overapprox );
        
        void addChild( ReachTreeNode* node_appended_on, ReachTreeNode* node_to_be_added );
            
    };
}    

