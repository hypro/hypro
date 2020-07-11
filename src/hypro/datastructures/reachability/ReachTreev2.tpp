

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

	size_t currentPos = this->mDepth - 1;
	auto const* node = this;

	while ( node->mParent != nullptr ) {
		path.elements[currentPos] = std::pair( mTimings, node->mTransition );
		currentPos -= 1;
	}

	assert( currentPos == 0 );

	return path;
}

}  // namespace hypro