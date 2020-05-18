#pragma once

#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "ErrorListener.h"

namespace hypro {
namespace parser{
    tree::ParseTree* createFlowstarParseTree(const std::string& filename);
}
}