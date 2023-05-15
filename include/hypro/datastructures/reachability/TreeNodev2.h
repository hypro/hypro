/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <boost/range/adaptor/transformed.hpp>
#include <memory>
#include <vector>

namespace hypro {

    template<class DerivedNode>
    class TreeNode {
    protected:
        DerivedNode *mParent = nullptr;
        std::vector<std::unique_ptr<DerivedNode>> mChildren{};
        size_t mDepth{0};

    public:
        TreeNode() = default;

        TreeNode(DerivedNode *parent)
                : mParent(parent), mDepth(parent->getDepth() + 1) {}

        // special member functions
        // making sure the noone tries to use the copy ctor. Necessary because the mChildren copy ctor is not deleted and only breaks once instantiated.
        TreeNode(TreeNode const &) = delete;

        TreeNode &operator=(TreeNode const &) = delete;

        TreeNode(TreeNode &&) = default;

        TreeNode &operator=(TreeNode &&) = default;

        ~TreeNode() = default;

        size_t getDepth() const { return mDepth; }

        template<class... Args>
        DerivedNode &addChild(Args &&... args) {
            return *mChildren.emplace_back(std::make_unique<DerivedNode>(args...));
        }

        auto getChildren() {
            return boost::adaptors::transform(mChildren, [](auto &uPtr) -> DerivedNode * {
                return uPtr.get();
            });
        }

        auto getChildren() const {
            return boost::adaptors::transform(mChildren, [](auto const &uPtr) -> DerivedNode const & {
                return *uPtr.get();
            });
        }

        /**
         * @brief Collect all sibling nodes, i.e., all child nodes from this node's parent without the node itself.
         * @return All sibling nodes
         */
        auto getSiblings() const {
            std::vector<DerivedNode const *> res;
            if (this->getParent() == nullptr) {
                return res;
            }
            for (auto childPtr: this->getParent()->getChildren()) {
                if (childPtr == this) {
                    continue;
                }
                res.push_back(childPtr);
            }
            return res;
        }

        void eraseChild(DerivedNode *child) {
            for (auto childIt = mChildren.begin(); childIt != mChildren.end(); ++childIt) {
                if (childIt->get() == child) {
                    mChildren.erase(childIt);
                    return;
                }
            }
        }

        void eraseChildren() {
            mChildren.clear();
        }

        auto getParent() const -> DerivedNode * {
            return mParent;
        }

        void setParent(DerivedNode *parent) {
            mParent = parent;
        }

        bool isLeaf() const { return mChildren.empty(); }
    };

}  // namespace hypro
