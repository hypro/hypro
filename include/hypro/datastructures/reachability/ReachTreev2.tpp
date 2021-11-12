

/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

template <typename Representation>
void ReachTreeNode<Representation>::setFixedPoint( bool hasFixedPoint, ReachTreeNode<Representation>* reason ) {
	mHasFixedPoint = hasFixedPoint ? TRIBOOL::TRUE : TRIBOOL::FALSE;
	mFixedPointReason = reason;
	// recursively mark nodes
	if ( this->getParent() != nullptr ) {
		if ( std::all_of( std::begin( this->getParent()->getChildren() ), std::end( this->getParent()->getChildren() ), []( const auto* child ) { return ( child->hasFixedPoint() == TRIBOOL::TRUE ); } ) ) {
			COUNT( "recursive fixed point" );
			this->getParent()->setFixedPoint( true, reason );
		}
	}
}

}  // namespace hypro