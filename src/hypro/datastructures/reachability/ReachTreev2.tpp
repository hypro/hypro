

namespace hypro {

template <class Representation>
ReachTreeNode<Representation>& ReachTreeNode<Representation>::addChild( Representation initialSet,
																		carl::Interval<SegmentInd> timings,
																		const Transition<Number>* transition ) {
	return Base::addChild( this, transition, transition->getTarget(), std::move( initialSet ), timings );
}

template <class Representation>
auto ReachTreeNode<Representation>::getPath() const -> Path<Number> {
	Path<Number> path{ this->mDepth };

	size_t currentPos = this->mDepth;  // one past end
	auto const* node = this;

	while ( node->mParent != nullptr ) {
		currentPos -= 1;
		path.elements[currentPos] = std::pair( node->mTimings, node->mTransition );
		node = node->mParent;
	}

	path.rootLocation = node->getLocation();

	assert( currentPos == 0 );

	return path;
}

}  // namespace hypro