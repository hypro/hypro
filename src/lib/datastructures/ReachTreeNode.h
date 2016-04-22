/* 
 * File:   ReachTreeNode.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 10:52 AM
 */
#pragma once

#include "../representations/GeometricObject.h"
#include "hybridAutomata/Transition.h"
#include "ReachTreeNodeSimple.h"

namespace hypro
{
    template <typename Representation>
    using flowpipe_t = std::vector<Representation>;
    
    template <typename Number>
    using guard_map = std::map< std::pair< Transition< Number >*, representation_name >, std::vector< unsigned > >;
    
    template <typename Number, typename Representation>
    class ReachTreeNode : ReachTreeNodeSimple<Number, Representation>
    {
        private:
            Location<Number>* mLoc;
            Number mTimeStep;
            representation_name mRep;
            Representation mFirst;
            Representation mLast;
            bool mFinished;
            // Data structure saving for each transition of mLoc the indices of the 
            // segments satisfying the corresponding guard
            guard_map<Number> mGuardSatisfiedIndices;
            // Data structure saving a rough overapproximation of the current flowpipe
            // for fixpoint recognition
            flowpipe_t<Representation> mOverapprox;
            ReachTreeNode* mParent;
        public:
        /**
	 * @brief Constructor 
	 *
	 * @param TO-DO
	 */
	ReachTreeNode( std::vector< unsigned > _id, Location<Number>* _loc, Representation _first_segment, Number _time_step, unsigned _depth, representation_name _rep, ReachTreeNode* _parent );
        
        Location<Number>* getLocation();
        
        Number getTimeStep();
        
        representation_name getRep();
        
        Representation getFirstSegment();
        
        Representation getLastSegment();
        
        bool getFinished();
        
        guard_map<Number> getGuardSatisfiedIndices();
        
        flowpipe_t<Representation> getOverapprox();
        
        ReachTreeNode getParent();
        
        void setTimeStep( Number _time_step );
        
        void setRepresentation( representation_name _rep );
        
        void setFirstSegment( Representation _first );
        
        void setLastSegment( Representation _last );  
        
        void setFinished( bool _finished );
        
        void setOverapproximation( flowpipe_t<Representation>& overapprox );
        
        void addGuardSatisfyingSegment( Transition<Number>* _trans, representation_name _rep, unsigned _index );
            
    };
}    

