/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "antlr4-flowstar/FlowstarParser.h"

namespace hypro {
    namespace parser {

        void openFile(const std::string &filename, ANTLRInputStream &input) {
            std::fstream ifs(filename);

            if (ifs.good()) {
                input = ANTLRInputStream(ifs);
            } else {
                std::cerr << "InputStream was bad." << std::endl;
                if (ifs.fail()) {
                    std::cerr << "Failbit was set" << std::endl;
                }
                if (ifs.eof()) {
                    std::cerr << "EOFbit was set" << std::endl;
                }
                if (ifs.bad()) {
                    std::cerr << "Badbit was set" << std::endl;
                }
            }
            if (!ifs.is_open()) {
                std::cout << "ifs hasn't opened anything" << std::endl;
            }
        }

        std::string
        replaceConstantsWithValues(TokenStreamRewriter &rewriter, std::map<std::string, std::string> constants) {
            for (std::size_t i = 0; i < rewriter.getTokenStream()->size(); i++) {
                auto it = constants.find(rewriter.getTokenStream()->get(i)->getText());
                if (it != constants.end()) {
                    rewriter.replace(i, i, constants.at(it->first));
                }
            }
            return rewriter.getText();
        }

        tree::ParseTree *createFlowstarParseTree(const std::string &filename) {
            //Create an ANTLRInputStream
            ANTLRInputStream input;
            openFile(filename, input);

            //Create Error Listener
            ErrorListener *errListener = new ErrorListener();

            //Create a Lexer and feed it with the input
            HybridAutomatonLexer lexer(&input);
            lexer.removeErrorListeners();
            lexer.addErrorListener(errListener);

            //Create an empty TokenStream obj
            CommonTokenStream tokens(&lexer);

            //Fill the TokenStream (and output it for demonstration)
            tokens.fill();

            //Create a parser with error listener
            HybridAutomatonParser parser(&tokens);
            parser.removeErrorListeners();
            parser.addErrorListener(errListener);
            tree::ParseTree *tree = parser.start();

            std::cout << "Tree adress: " << tree << std::endl;

            //Create TokenStreamRewriter, needed for constants if defined
            //Replace constants with their values, then parse again
            if (parser.getConstants().size() > 0) {
                TokenStreamRewriter rewriter(&tokens);
                std::string modified = replaceConstantsWithValues(rewriter, parser.getConstants());
                ANTLRInputStream inputMod(modified);
                HybridAutomatonLexer lexerMod(&inputMod);
                lexerMod.removeErrorListeners();
                lexerMod.addErrorListener(errListener);

                //Create an empty TokenStream obj
                CommonTokenStream tokensMod(&lexerMod);

                //Fill the TokenStream
                tokensMod.fill();

                //Create a parser with error listener
                HybridAutomatonParser parserMod(&tokensMod);
                parserMod.removeErrorListeners();
                parserMod.addErrorListener(errListener);
                tree::ParseTree *tree = parserMod.start();

                //delete errListener;

                return tree;

            } else {

                //delete errListener;

                return tree;
            }
        }
    } // namespace parser
} // namespace hypro
