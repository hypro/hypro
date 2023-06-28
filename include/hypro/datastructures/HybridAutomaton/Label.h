/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Class that describes a label of an hybrid automaton.
 * @file   Label.h
 * @author Tobias Vogel <tobias.vogel@rwth-aachen.de>
 *
 * @since 	2017-12-03
 */

#pragma once

#include <functional>
#include <iosfwd>
#include <string>

namespace hypro {

    class Label {
    private:
        std::string mName = "";

    public:
        Label() = delete;

        Label(const Label &in) = default;

        Label(Label &&in) = default;

        explicit Label(const std::string &name)
                : mName(name) {};

        ~Label() {};

        Label &operator=(const Label &in) = default;

        Label &operator=(Label &&in) = default;

        const std::string &getName() const {
            assert(mName != "");
            return mName;
        }

        void setName(const std::string &name) { mName = name; }

        friend bool operator==(const Label &lhs, const Label &rhs) {
            return lhs.getName() == rhs.getName();
        }

        friend bool operator!=(const Label &lhs, const Label &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const Label &lhs, const Label &rhs) {
            return lhs.getName() < rhs.getName();
        }

        friend std::ostream &operator<<(std::ostream &ostr, const Label &l) {
            ostr << l.getName();
            return ostr;
        }
    };

}  // namespace hypro

namespace std {
/**
 * @brief Specialization of std::hash for labels
 * @tparam
 */
    template<>
    struct hash<hypro::Label> {
        /// Functor for std::hash
        std::size_t operator()(const hypro::Label &l) const {
            return std::hash<std::string>{}(l.getName());
        }
    };
}  // namespace std
