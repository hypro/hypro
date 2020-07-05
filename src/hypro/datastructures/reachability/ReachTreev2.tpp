

namespace hypro {

template <class Representation>
ReachTreeNode<Representation>& ReachTreeNode<Representation>::addChild( std::vector<Representation>* flowpipe,
														Representation initialSet,
														carl::Interval<SegmentInd> timings,
														const Transition<Number>* transition ) {
	mTransitions.push_back( transition );
	return Base::addChild( this, transition->getTarget(), flowpipe, std::move( initialSet ), timings );
}

}  // namespace hypro