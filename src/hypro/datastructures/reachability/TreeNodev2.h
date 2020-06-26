#pragma once

#include <boost/range/adaptor/transformed.hpp>
#include <memory>
#include <vector>

namespace hypro {

template <class DerivedNode>
class TreeNode {
	DerivedNode* mParent{};
	std::vector<std::unique_ptr<DerivedNode>> mChildren{};
	int mDepth{ 0 };

  public:
	TreeNode() = default;
	TreeNode( DerivedNode* parent )
		: mParent( parent )
		, mDepth( parent->getDepth() + 1 ) {}

	int getDepth() { return mDepth; }

	template <class... Args>
	DerivedNode& addChild( Args&&... args ) {
		return *mChildren.emplace_back( std::make_unique<DerivedNode>( args... ) );
	}

	auto getChildren() {
		return boost::adaptors::transform( mChildren, []( auto& uPtr ) -> DerivedNode& {
			return *uPtr;
		} );
	}

	auto getChildren() const {
		return boost::adaptors::transform( mChildren, []( auto const& uPtr ) -> DerivedNode const& {
			return *uPtr;
		} );
	}
};

}  // namespace hypro