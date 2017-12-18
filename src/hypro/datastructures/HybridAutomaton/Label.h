/*
 * Class that describes a label of an hybrid automaton.
 * @file   Label.h
 * @author Tobias Vogel <tobias.vogel@rwth-aachen.de>
 *
 * @since 	2017-12-03
 */

#pragma once

namespace hypro {

template<typename Number>
class Label {
  private:
    std::string mName;

  public:
    Label() = default;

    Label(const std::string name) { mName = name; };

    ~Label() {};

    std::string getName() const { return mName; }

    void setName(const std::string &name) { mName = name; }

    friend bool operator==(const Label<Number> lhs, const Label<Number> rhs) {
      return lhs.getName() == rhs.getName();
    }

    friend bool operator!=(const Label<Number> lhs, const Label<Number> rhs) {
      return !(lhs == rhs);
    }

    friend bool operator<(const Label<Number> lhs, const Label<Number> rhs) {
      return lhs != rhs;
    }
};

}