/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "ReachTreePlotter.h"

namespace hypro::plotting {

    template<typename Node>
    void ReachTreePlotter<Node>::plot(const std::vector<Node *> &highlights) {
        // graph and context variables
        Agraph_t *graph;
        GVC_t *gvc = gvContext();

        // setup
        graph = agopen(std::string("reachTree").data(), Agstrictdirected, 0);
        gvLayout(gvc, graph, "dot");

        // set default node properties
        agattr(graph, AGNODE, std::string("fillcolor").data(), std::string("lightgrey").data());
        agattr(graph, AGNODE, std::string("style").data(), std::string("filled").data());
        // agattr(graph, AGNODE, std::string("label").data(), std::string("test").data());

        // insert nodes
        std::size_t count{0};
        for (const Node &root: mRoots) {
            for (const Node &node: preorder(root)) {
                std::string name = "n_" + std::to_string(count++) + ": ";
                if (node.getParent() == nullptr) {
                    if (node.getChildren().empty()) {
                        name += "root";
                    } else {
                        assert(!node.getChildren().empty());
                        assert(node.getChildren().front().getTransition() != nullptr);
                        assert(node.getChildren().front().getTransition()->getSource() != nullptr);
                        std::string tmp = node.getLocation()->getName();
                        name += node.getChildren().front().getTransition()->getSource()->getName();
                    }
                } else {
                    // name += node.getTransition()->getTarget()->getName();
                    name += node.getLocation()->getName();
                }

                auto nptr = agnode(graph, name.data(), 1);
                mNodePointers[&node] = nptr;
                // color node green, if it ends in a fixed point
                if (node.hasFixedPoint() == TRIBOOL::TRUE) {
                    agsafeset(nptr, std::string("fillcolor").data(), std::string("green").data(), std::string().data());
                }
                // color node, if it needs highlighting
                if (std::find(std::begin(highlights), std::end(highlights), &node) != std::end(highlights)) {
                    agsafeset(nptr, std::string("fillcolor").data(), std::string("yellow").data(),
                              std::string().data());
                }
                if (node.getParent() != nullptr) {
                    assert(mNodePointers.find(node.getParent()) != mNodePointers.end());
                    agedge(graph, mNodePointers[node.getParent()], nptr, std::string("").data(), 1);
                }
            }
        }

        // determine filename
        std::size_t cnt = 0;
        std::string filename = mSettings.filename;
        if (!mSettings.overwriteFiles) {
            while (file_exists(filename + ".png") || file_exists(filename + ".dot")) {
                std::stringstream ss;
                ss << mSettings.filename << "-" << cnt;
                filename = ss.str();
                ++cnt;
            }
        }

        // drawing
        gvLayoutJobs(gvc, graph);
        gvRenderFilename(gvc, graph, "png", (filename + ".png").c_str());
        gvRenderFilename(gvc, graph, "dot", (filename + ".dot").c_str());

        // cleanup
        gvFreeLayout(gvc, graph);
        agclose(graph);
        gvFreeContext(gvc);
    }

    template<typename Node>
    void ReachTreePlotter<Node>::plotPath(const Node *node, const std::vector<Node *> &highlights) {
        // graph and context variables
        Agraph_t *graph;
        GVC_t *gvc;

        // setup
        gvc = gvContext();
        graph = agopen("reachPath", Agstrictdirected, 0);
        gvLayout(gvc, graph, "dot");

        // set default node properties
        agattr(graph, AGNODE, std::string("fillcolor").data(), std::string("lightgrey").data());
        agattr(graph, AGNODE, std::string("style").data(), std::string("filled").data());
        // agattr(graph, AGNODE, std::string("label").data(), std::string("test").data());
        agattr(graph, AGNODE, std::string("shape").data(), std::string("record").data());

        // collect nodes in order
        std::vector<std::pair<Node const *, std::vector<Node const *>>> pathNodes;
        auto current = node;
        while (current != nullptr) {
            pathNodes.push_back(std::make_pair(current, current->getSiblings()));
            current = current->getParent();
        }

        // insert nodes
        std::size_t count{0};
        for (auto rIt = std::rbegin(pathNodes); rIt != std::rend(pathNodes); ++rIt) {
            auto node = rIt->first;
            auto siblings = rIt->second;
            // write main node
            auto nodeString = createName(node, count++);
            auto nptr = agnode(graph, nodeString.data(), 1);
            agsafeset(nptr, std::string("label").data(), nodeString.data(), std::string().data());
            mNodePointers[node] = nptr;
            // write siblings
            for (const auto *sibling: siblings) {
                auto siblingString = createName(node, count++);
                auto nptr = agnode(graph, siblingString.data(), 1);
                agsafeset(nptr, std::string("label").data(), siblingString.data(), std::string().data());
                agsafeset(nptr, std::string("fillcolor").data(), std::string("gray").data(), std::string().data());
                mNodePointers[sibling] = nptr;
            }
            // color node green, if it ends in a fixed point
            if (node->hasFixedPoint() == TRIBOOL::TRUE) {
                agsafeset(nptr, std::string("fillcolor").data(), std::string("green").data(), std::string().data());
            }
            // color node, if it needs highlighting
            if (std::find(std::begin(highlights), std::end(highlights), node) != std::end(highlights)) {
                agsafeset(nptr, std::string("fillcolor").data(), std::string("yellow").data(), std::string().data());
            }
            if (node->getParent() != nullptr) {
                assert(mNodePointers.find(node->getParent()) != mNodePointers.end());
                agedge(graph, mNodePointers[node->getParent()], nptr, "", 1);
                for (const auto s: siblings) {
                    agedge(graph, mNodePointers[node->getParent()], mNodePointers[s], "", 1);
                }
            }
        }

        // determine filename
        std::size_t cnt = 0;
        std::string filename = mSettings.filename;
        if (!mSettings.overwriteFiles) {
            while (file_exists(filename + ".png") || file_exists(filename + ".dot")) {
                std::stringstream ss;
                ss << mSettings.filename << "-" << cnt;
                filename = ss.str();
                ++cnt;
            }
        }

        // drawing
        gvLayoutJobs(gvc, graph);
        gvRenderFilename(gvc, graph, "png", (filename + ".png").c_str());
        gvRenderFilename(gvc, graph, "dot", (filename + ".dot").c_str());
        gvFreeLayout(gvc, graph);

        // cleanup
        agclose(graph);
        gvFreeContext(gvc);
    }

}  // namespace hypro::plotting
