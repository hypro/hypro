#pragma once

#include <boost/range/adaptor/transformed.hpp>
#include <memory>
#include <vector>

namespace hypro {

template <class DerivedNode>
class TreeNode {
  protected:
	DerivedNode* mParent = nullptr;
	std::vector<std::unique_ptr<DerivedNode>> mChildren{};
	size_t mDepth{ 0 };

  public:
	TreeNode() = default;
	TreeNode( DerivedNode* parent )
		: mParent( parent )
		, mDepth( parent->getDepth() + 1 ) {}

	// special member functions
	// making sure the noone tries to use the copy ctor. Necessary because the mChildren copy ctor is not deleted and only breaks once instantiated.
	TreeNode( TreeNode const& ) = delete;
	TreeNode& operator=( TreeNode const& ) = delete;

	TreeNode( TreeNode&& ) = default;
	TreeNode& operator=( TreeNode&& ) = default;

	~TreeNode() = default;

	size_t getDepth() { return mDepth; }

	template <class... Args>
	DerivedNode& addChild( Args&&... args ) {
		return *mChildren.emplace_back( std::make_unique<DerivedNode>( args... ) );
	}

	auto getChildren() {
		return boost::adaptors::transform( mChildren, []( auto& uPtr ) -> DerivedNode* {
			return uPtr.get();
		} );
	}

	auto getChildren() const {
		return boost::adaptors::transform( mChildren, []( auto const& uPtr ) -> DerivedNode const& {
			return *uPtr.get();
		} );
	}

	auto getParent() const -> DerivedNode* {
		return mParent;
	}

	void setParent( DerivedNode* parent ) {
		mParent = parent;
	}
};

}  // namespace hypro